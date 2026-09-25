#include "ErrorHandler.hpp"
#include <iostream>
#include <cstring>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

namespace OpenGLRenderer {

RendererException::RendererException(const std::string& message, ErrorSource source, ErrorSeverity severity)
    : std::runtime_error(message), m_source(source), m_severity(severity), m_message(message) {
    m_message += " [Source: " + sourceToString(source) + ", Severity: " + severityToString(severity) + "]";
}

ErrorSource RendererException::getSource() const noexcept {
    return m_source;
}

ErrorSeverity RendererException::getSeverity() const noexcept {
    return m_severity;
}

const char* RendererException::what() const noexcept {
    return m_message.c_str();
}

ErrorHandler& ErrorHandler::getInstance() {
    static ErrorHandler instance;
    return instance;
}

void ErrorHandler::setLogCallback(std::function<void(const ErrorContext&)> callback) {
    m_logCallback = [callback](const ErrorContext* ctx) {
        if (ctx) callback(*ctx);
    };
    m_callbackIsContext = true;
}

void ErrorHandler::clearLogCallback() {
    m_logCallback = nullptr;
    m_callbackIsContext = false;
}

void ErrorHandler::logError(const ErrorContext& context) {
    m_lastError = context.description;
    m_lastSeverity = context.severity;

    std::string prefix = "[" + severityToString(context.severity) + "] ";
    std::string fullMessage = prefix + context.description + " (" + sourceToString(context.source) + ")";

    if (context.line > 0) {
        fullMessage += " at " + context.file + ":" + std::to_string(context.line);
    }

    if (context.recoverySuggestion.has_value()) {
        fullMessage += " | Suggestion: " + context.recoverySuggestion.value();
    }

    if (context.severity == ErrorSeverity::CRITICAL || context.severity == ErrorSeverity::ERROR) {
        std::cerr << "ERROR: " << fullMessage << std::endl;
    } else if (context.severity == ErrorSeverity::WARNING) {
        std::cout << "WARNING: " << fullMessage << std::endl;
    } else {
        std::cout << "INFO: " << fullMessage << std::endl;
    }

    if (m_logCallback) {
        m_logCallback(&context);
    }
}

void ErrorHandler::logInfo(const std::string& message) {
    ErrorContext ctx;
    ctx.description = message;
    ctx.source = ErrorSource::UNKNOWN;
    ctx.severity = ErrorSeverity::INFO;
    ctx.line = 0;
    logError(ctx);
}

void ErrorHandler::logWarning(const std::string& message) {
    ErrorContext ctx;
    ctx.description = message;
    ctx.source = ErrorSource::UNKNOWN;
    ctx.severity = ErrorSeverity::WARNING;
    ctx.line = 0;
    logError(ctx);
}

bool ErrorHandler::checkOpenGLError(const char* file, int line) {
    bool hasError = false;
    unsigned int errorCode;
    std::string errorMessages;

    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        hasError = true;
        if (!errorMessages.empty()) {
            errorMessages += "; ";
        }
        errorMessages += formatOpenGLMessage(errorCode);
    }

    if (hasError) {
        ErrorContext ctx;
        ctx.description = "OpenGL Error: " + errorMessages;
        ctx.source = ErrorSource::OPENGL_INIT;
        ctx.severity = ErrorSeverity::ERROR;
        ctx.file = file;
        ctx.line = line;
        ctx.recoverySuggestion = "Check OpenGL context creation and shader compilation";
        logError(ctx);
    }

    return hasError;
}

bool ErrorHandler::checkShaderCompilation(unsigned int shader, const std::string& shaderPath) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        ErrorContext ctx;
        ctx.description = "Shader compilation failed: " + std::string(infoLog);
        ctx.source = ErrorSource::SHADER_COMPILATION;
        ctx.severity = ErrorSeverity::CRITICAL;
        ctx.file = shaderPath;
        ctx.line = 0;
        ctx.recoverySuggestion = "Check GLSL syntax and version compatibility";
        logError(ctx);
        return false;
    }

    return true;
}

bool ErrorHandler::checkShaderProgram(unsigned int program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);

        ErrorContext ctx;
        ctx.description = "Shader program linking failed: " + std::string(infoLog);
        ctx.source = ErrorSource::SHADER_COMPILATION;
        ctx.severity = ErrorSeverity::CRITICAL;
        ctx.line = 0;
        ctx.recoverySuggestion = "Verify all shaders compiled successfully before linking";
        logError(ctx);
        return false;
    }

    return true;
}

bool ErrorHandler::checkFramebufferStatus() {
    unsigned int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::string errorDesc;
        switch (status) {
            case GL_FRAMEBUFFER_UNDEFINED: errorDesc = "Framebuffer undefined"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: errorDesc = "Incomplete attachment"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: errorDesc = "Missing attachment"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: errorDesc = "Incomplete draw buffer"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: errorDesc = "Incomplete read buffer"; break;
            case GL_FRAMEBUFFER_UNSUPPORTED: errorDesc = "Framebuffer unsupported"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: errorDesc = "Incomplete multisample"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: errorDesc = "Incomplete layer targets"; break;
            default: errorDesc = "Unknown framebuffer error"; break;
        }

        ErrorContext ctx;
        ctx.description = "Framebuffer incomplete: " + errorDesc;
        ctx.source = ErrorSource::OPENGL_INIT;
        ctx.severity = ErrorSeverity::CRITICAL;
        ctx.line = 0;
        ctx.recoverySuggestion = "Check framebuffer attachments and dimensions";
        logError(ctx);
        return false;
    }
    return true;
}

void ErrorHandler::reportFileError(const std::string& filename, const std::string& operation) {
    ErrorContext ctx;
    ctx.description = "File operation '" + operation + "' failed for: " + filename;
    ctx.source = ErrorSource::FILE_IO;
    ctx.severity = ErrorSeverity::CRITICAL;
    ctx.line = 0;
    ctx.recoverySuggestion = "Verify file exists and application has read permissions";
    logError(ctx);
}

void ErrorHandler::reportWindowCreationError(int errorCode, const std::string& description) {
    ErrorContext ctx;
    ctx.description = "Window creation failed (code " + std::to_string(errorCode) + "): " + description;
    ctx.source = ErrorSource::WINDOW_CREATION;
    ctx.severity = ErrorSeverity::CRITICAL;
    ctx.line = 0;
    ctx.recoverySuggestion = "Ensure GLFW is properly initialized and graphics driver supports OpenGL";
    logError(ctx);
}

void ErrorHandler::reportInitializationError(ErrorSource source, const std::string& details) {
    ErrorContext ctx;
    ctx.description = "Initialization failed: " + details;
    ctx.source = source;
    ctx.severity = ErrorSeverity::CRITICAL;
    ctx.line = 0;
    ctx.recoverySuggestion = "Check system requirements and library versions";
    logError(ctx);
}

std::string ErrorHandler::getLastError() const {
    return m_lastError;
}

ErrorSeverity ErrorHandler::getLastSeverity() const {
    return m_lastSeverity;
}

void ErrorHandler::clearLastError() {
    m_lastError.clear();
    m_lastSeverity = ErrorSeverity::INFO;
}

std::string ErrorHandler::severityToString(ErrorSeverity severity) {
    switch (severity) {
        case ErrorSeverity::INFO: return "INFO";
        case ErrorSeverity::WARNING: return "WARNING";
        case ErrorSeverity::ERROR: return "ERROR";
        case ErrorSeverity::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

std::string ErrorHandler::sourceToString(ErrorSource source) {
    switch (source) {
        case ErrorSource::FILE_IO: return "FILE_IO";
        case ErrorSource::OPENGL_INIT: return "OPENGL_INIT";
        case ErrorSource::SHADER_COMPILATION: return "SHADER_COMPILATION";
        case ErrorSource::BUFFER_ALLOCATION: return "BUFFER_ALLOCATION";
        case ErrorSource::WINDOW_CREATION: return "WINDOW_CREATION";
        case ErrorSource::UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}

std::string ErrorHandler::formatOpenGLMessage(unsigned int glError) {
    switch (glError) {
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_CONTEXT_LOST: return "GL_CONTEXT_LOST";
        case GL_TABLE_TOO_LARGE: return "GL_TABLE_TOO_LARGE";
        default: return "Unknown error (0x" + 
               ((glError < 16) ? "0" : "") + 
               std::to_string(glError) + ")";
    }
}

InitializationGuard::InitializationGuard() : m_initialized(false), m_errorMessage() {
    if (!glfwInit()) {
        m_errorMessage = "Failed to initialize GLFW";
        ErrorHandler::getInstance().reportInitializationError(
            ErrorSource::WINDOW_CREATION, m_errorMessage);
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

    m_initialized = true;
}

InitializationGuard::~InitializationGuard() {
    if (m_initialized) {
        glfwTerminate();
    }
}

bool InitializationGuard::isInitialized() const noexcept {
    return m_initialized;
}

const char* InitializationGuard::getInitError() const noexcept {
    return m_errorMessage.c_str();
}

FileOperationResult::FileOperationResult(bool success, const std::string& errorMsg)
    : m_success(success), m_errorMessage(errorMsg) {}

bool FileOperationResult::success() const noexcept {
    return m_success;
}

const std::string& FileOperationResult::errorMessage() const noexcept {
    return m_errorMessage;
}

FileOperationResult::operator bool() const noexcept {
    return m_success;
}

}