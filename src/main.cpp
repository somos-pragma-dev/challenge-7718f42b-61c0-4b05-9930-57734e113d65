#include <iostream>
#include <memory>
#include <chrono>
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "loader/ObjLoader.hpp"
#include "lighting/LightManager.hpp"
#include "renderer/Renderer.hpp"
#include "utils/ErrorHandler.hpp"

namespace {

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
constexpr const char* WINDOW_TITLE = "OpenGL Renderer - Pragma Engine";

constexpr float CAMERA_FOV = 45.0f;
constexpr float CAMERA_NEAR = 0.1f;
constexpr float CAMERA_FAR = 100.0f;

constexpr glm::vec3 CAMERA_POSITION = {0.0f, 2.0f, 5.0f};
constexpr glm::vec3 CAMERA_TARGET = {0.0f, 0.0f, 0.0f};
constexpr glm::vec3 CAMERA_UP = {0.0f, 1.0f, 0.0f};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "[INFO] Framebuffer resized to " << width << "x" << height << std::endl;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        std::cout << "[INFO] ESC pressed, requesting window close" << std::endl;
    }
}

class EngineContext {
public:
    EngineContext(int width, int height, const char* title)
        : window_(nullptr), width_(width), height_(height), title_(title) {
        initialize();
    }

    ~EngineContext() {
        shutdown();
    }

    EngineContext(const EngineContext&) = delete;
    EngineContext& operator=(const EngineContext&) = delete;

    GLFWwindow* getWindow() const { return window_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

private:
    void initialize() {
        std::cout << "[INIT] Starting Pragma OpenGL Engine..." << std::endl;
        
        if (!glfwInit()) {
            throw std::runtime_error(ErrorHandler::getCriticalError(
                "GLFW initialization failed", "EngineContext::initialize"));
        }
        std::cout << "[INIT] GLFW initialized successfully" << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
        if (!window_) {
            glfwTerminate();
            throw std::runtime_error(ErrorHandler::getCriticalError(
                "Failed to create GLFW window", "EngineContext::initialize"));
        }
        std::cout << "[INIT] Window created: " << width_ << "x" << height_ << std::endl;

        glfwMakeContextCurrent(window_);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            glfwDestroyWindow(window_);
            glfwTerminate();
            throw std::runtime_error(ErrorHandler::getCriticalError(
                "Failed to initialize GLAD", "EngineContext::initialize"));
        }
        std::cout << "[INIT] GLAD initialized successfully" << std::endl;
        std::cout << "[INFO] OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "[INFO] GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        std::cout << "[INFO] Renderer: " << glGetString(GL_RENDERER) << std::endl;

        glViewport(0, 0, width_, height_);
        glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        const GLubyte* extentions = glGetString(GL_EXTENSIONS);
        if (extentions && std::string(reinterpret_cast<const char*>(extentions)).find("GL_EXT_debug_output") != std::string::npos) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            std::cout << "[INFO] Debug output enabled" << std::endl;
        }

        glfwShowWindow(window_);
        std::cout << "[INIT] Engine context fully initialized" << std::endl;
    }

    void shutdown() {
        if (window_) {
            glfwDestroyWindow(window_);
            std::cout << "[SHUTDOWN] Window destroyed" << std::endl;
        }
        glfwTerminate();
        std::cout << "[SHUTDOWN] GLFW terminated" << std::endl;
    }

    GLFWwindow* window_;
    int width_;
    int height_;
    const char* title_;
};

class RenderLoop {
public:
    RenderLoop(GLFWwindow* window, std::unique_ptr<Renderer> renderer)
        : window_(window)
        , renderer_(std::move(renderer))
        , lastFrameTime_(0.0)
        , frameCount_(0)
        , fpsUpdateTime_(0.0)
        , currentFPS_(0) {}

    void run() {
        std::cout << "[RENDER] Starting render loop..." << std::endl;
        
        while (!glfwWindowShouldClose(window_)) {
            double currentFrameTime = glfwGetTime();
            double deltaTime = currentFrameTime - lastFrameTime_;
            lastFrameTime_ = currentFrameTime;

            processInput(window_);

            updateFPS(currentFrameTime);

            renderFrame(deltaTime);

            glfwSwapBuffers(window_);
            glfwPollEvents();
        }

        std::cout << "[RENDER] Render loop terminated. Final FPS: " << currentFPS_ << std::endl;
    }

private:
    void updateFPS(double currentTime) {
        frameCount_++;
        if (currentTime - fpsUpdateTime_ >= 1.0) {
            currentFPS_ = frameCount_;
            frameCount_ = 0;
            fpsUpdateTime_ = currentTime;
            std::cout << "[FPS] " << currentFPS_ << " FPS" << std::endl;

            if (currentFPS_ < 60) {
                std::cout << "[WARNING] FPS below target (60)" << std::endl;
            }
        }
    }

    void renderFrame(double deltaTime) {
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (renderer_) {
            renderer_->render(deltaTime);
        } else {
            std::cout << "[ERROR] Renderer not initialized" << std::endl;
        }
    }

    GLFWwindow* window_;
    std::unique_ptr<Renderer> renderer_;
    double lastFrameTime_;
    int frameCount_;
    double fpsUpdateTime_;
    int currentFPS_;
};

std::unique_ptr<Renderer> createRenderer(int width, int height) {
    std::cout << "[SETUP] Creating renderer components..." << std::endl;

    auto objLoader = std::make_unique<ObjLoader>();
    std::cout << "[SETUP] ObjLoader created" << std::endl;

    auto lightManager = std::make_unique<LightManager>();
    lightManager->addDirectionalLight(
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f
    );
    lightManager->addPointLight(
        glm::vec3(2.0f, 3.0f, 2.0f),
        glm::vec3(1.0f, 0.9f, 0.8f),
        1.5f
    );
    std::cout << "[SETUP] LightManager configured with 2 lights" << std::endl;

    auto renderer = std::make_unique<Renderer>(width, height, std::move(objLoader), std::move(lightManager));
    renderer->initialize();
    std::cout << "[SETUP] Renderer initialized successfully" << std::endl;

    return renderer;
}

glm::mat4 createViewMatrix() {
    return glm::lookAt(CAMERA_POSITION, CAMERA_TARGET, CAMERA_UP);
}

glm::mat4 createProjectionMatrix(int width, int height) {
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    return glm::perspective(glm::radians(CAMERA_FOV), aspectRatio, CAMERA_NEAR, CAMERA_FAR);
}

} // anonymous namespace

int main(int argc, char* argv[]) {
    std::cout << "=======================================" << std::endl;
    std::cout << "  Pragma OpenGL Renderer v1.0.0" << std::endl;
    std::cout << "=======================================" << std::endl;

    try {
        EngineContext engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        auto renderer = createRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
        
        renderer->setViewMatrix(createViewMatrix());
        renderer->setProjectionMatrix(createProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT));

        RenderLoop loop(engine.getWindow(), std::move(renderer));
        loop.run();

        std::cout << "[MAIN] Application terminated normally" << std::endl;
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[FATAL] Exception caught in main: " << e.what() << std::endl;
        ErrorHandler::logError("Fatal exception in main", e.what());
        return EXIT_FAILURE;

    } catch (...) {
        std::cerr << "[FATAL] Unknown exception caught in main" << std::endl;
        ErrorHandler::logError("Unknown fatal exception", "Unknown");
        return EXIT_FAILURE;
    }
}