#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <string>
#include <stdexcept>
#include <optional>
#include <functional>

namespace OpenGLRenderer {

enum class ErrorSeverity {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

enum class ErrorSource {
    FILE_IO,
    OPENGL_INIT,
    SHADER_COMPILATION,
    BUFFER_ALLOCATION,
    WINDOW_CREATION,
    UNKNOWN
};

class RendererException : public std::runtime_error {
public:
    RendererException(const std::string& message, ErrorSource source, ErrorSeverity severity);
    ErrorSource getSource() const noexcept;
    ErrorSeverity getSeverity() const noexcept;
    const char* what() const noexcept override;

private:
    ErrorSource m_source;
    ErrorSeverity m_severity;
    mutable std::string m_message;
};

struct ErrorContext {
    std::string description;
    ErrorSource source;
    ErrorSeverity severity;
    std::string file;
    int line;
    std::optional<std::string> recoverySuggestion;
};

class ErrorHandler {
public:
    static ErrorHandler& getInstance();

    void setLogCallback(std::function<void(const ErrorContext&)> callback);
    void clearLogCallback();

    void logError(const ErrorContext& context);
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);

    bool checkOpenGLError(const char* file, int line);
    bool checkShaderCompilation(unsigned int shader, const std::string& shaderPath);
    bool checkShaderProgram(unsigned int program);
    bool checkFramebufferStatus();

    void reportFileError(const std::string& filename, const std::string& operation);
    void reportWindowCreationError(int errorCode, const std::string& description);
    void reportInitializationError(ErrorSource source, const std::string& details);

    std::string getLastError() const;
    ErrorSeverity getLastSeverity() const;
    void clearLastError();

private:
    ErrorHandler() = default;
    ~ErrorHandler() = default;
    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;

    static std::string severityToString(ErrorSeverity severity);
    static std::string sourceToString(ErrorSource source);
    static std::string formatOpenGLMessage(unsigned int glError);

    std::function<void(const ErrorContext*)> m_logCallback;
    std::string m_lastError;
    ErrorSeverity m_lastSeverity{ErrorSeverity::INFO};
    bool m_callbackIsContext{false};
};

#define CHECK_OPENGL_ERROR() \
    OpenGLRenderer::ErrorHandler::getInstance().checkOpenGLError(__FILE__, __LINE__)

#define THROW_RENDERER_ERROR(msg, source, severity) \
    throw OpenGLRenderer::RendererException(msg, source, severity)

class InitializationGuard {
public:
    InitializationGuard();
    ~InitializationGuard();

    bool isInitialized() const noexcept;
    const char* getInitError() const noexcept;

private:
    bool m_initialized;
    std::string m_errorMessage;
};

class FileOperationResult {
public:
    FileOperationResult() = default;
    FileOperationResult(bool success, const std::string& errorMsg = "");

    bool success() const noexcept;
    const std::string& errorMessage() const noexcept;
    explicit operator bool() const noexcept;

private:
    bool m_success;
    std::string m_errorMessage;
};

template<typename T>
class SafeResource {
public:
    SafeResource() : m_resource(nullptr), m_valid(false) {}
    SafeResource(T* resource) : m_resource(resource), m_valid(resource != nullptr) {}
    ~SafeResource() { reset(); }

    SafeResource(const SafeResource&) = delete;
    SafeResource& operator=(const SafeResource&) = delete;

    SafeResource(SafeResource&& other) noexcept : m_resource(other.m_resource), m_valid(other.m_valid) {
        other.m_resource = nullptr;
        other.m_valid = false;
    }

    SafeResource& operator=(SafeResource&& other) noexcept {
        if (this != &other) {
            reset();
            m_resource = other.m_resource;
            m_valid = other.m_valid;
            other.m_resource = nullptr;
            other.m_valid = false;
        }
        return *this;
    }

    T* get() const noexcept { return m_resource; }
    T* release() { m_valid = false; T* tmp = m_resource; m_resource = nullptr; return tmp; }
    void reset() { if (m_resource) { delete m_resource; } m_resource = nullptr; m_valid = false; }
    bool isValid() const noexcept { return m_valid; }
    explicit operator bool() const noexcept { return m_valid; }

private:
    T* m_resource;
    bool m_valid;
};

}

#endif