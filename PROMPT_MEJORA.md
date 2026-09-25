# Prompt para Mejorar el Codigo Base

Copia y pega el contenido del bloque de abajo en un asistente de IA (Claude, ChatGPT)
para obtener un ZIP con el proyecto completo y arrancable.

Si preferis trabajar en tu editor con un agente local (Claude Code, Cursor, Copilot), usa `AGENTS.md` en vez de este archivo: dice lo mismo pero para que escriba los archivos en disco.

## Las dos reglas que no se negocian

1. **Completa el boilerplate.** Todo lo que el proyecto necesita para compilar y arrancar: manifiesto de dependencias, punto de entrada, configuracion, capa de interfaz, y las capas del patron arquitectonico declarado. Eso es andamiaje y es tu trabajo.
2. **NO resuelvas el reto.** Los entregables de las fases son el trabajo de la persona. El hueco pedagogico se deja como esta: el proyecto arranca, pero lo que el reto pide implementar NO esta implementado.

Dicho de otra forma: si algo impide compilar, arreglalo. Si algo es logica de negocio incompleta, validaciones ausentes, un secreto hardcodeado o un patron mejorable, dejalo exactamente como esta — es lo que la persona tiene que encontrar.

## Lo que le falta a este proyecto

Esto NO lo tenes que adivinar: salio de comparar el proyecto contra la arquitectura declarada del reto y de un analisis estatico del codigo. Completalo TODO.

### Referencias colgando en el codigo que si esta

Cada una rompe la compilacion:

- `package.json` — `glm`: "glm": "^0.9.9.8" en dependencies no es un version spec valido de npm. Usa una version publicada real o un rango semver valido (^x.y.z, ~x.y.z, x.y.z, "*"), no un valor inventado.
- `package.json` — `cmake@3.20.0`: cmake declara la version 3.20.0, pero el registry de npm respondio que esa version no existe. Es una version inventada: reemplazala por una version publicada real, o si no se conoce con certeza, usa el mecanismo centralizado del ecosistema (BOM/parent/platform/version catalog) y no declares una version individual.
- `package.json` — `glfw@3.3.8`: glfw declara la version 3.3.8, pero el registry de npm respondio que esa version no existe. Es una version inventada: reemplazala por una version publicada real, o si no se conoce con certeza, usa el mecanismo centralizado del ecosistema (BOM/parent/platform/version catalog) y no declares una version individual.
- `package.json` — `glad@0.1.36`: glad declara la version 0.1.36, pero el registry de npm respondio que esa version no existe. Es una version inventada: reemplazala por una version publicada real, o si no se conoce con certeza, usa el mecanismo centralizado del ecosistema (BOM/parent/platform/version catalog) y no declares una version individual.

## Como saber que terminaste

```bash
el comando de build o arranque canonico del stack elegido
```

Ese comando corriendo sin errores es la definicion de "listo".

---

```
## Briefing del reto (autoridad)
Este bloque manda sobre los archivos adjuntos. El stack y el rol salen de AQUÍ, no de un topic genérico ni de markdown placeholder.

### Contexto técnico original
Motor de renderizado basico con OpenGL y C++ moderno

### Reto
- Tema: Motor de renderizado básico con OpenGL y C++ moderno
- Seniority: junior-l1
- Tipo: practical
- Título: Creación de un motor de renderizado básico
- Tiempo estimado: 2 semanas

### Fases (trabajo del HUMANO — PROHIBIDO completarlas)
No implementes estos entregables. Dejalos como hueco pedagógico. El asistente solo materializa el proyecto arrancable para que el participante pueda trabajar.
- Fase 1: Carga de objetos 3D — objetivo: Desarrollar un componente que cargue objetos 3D desde un archivo OBJ. — entregable (NO resolver): Componente de carga de objetos 3D funcional.
- Fase 2: Aplicación de luces y sombras — objetivo: Desarrollar un componente que aplique luces y sombras a los objetos 3D cargados. — entregable (NO resolver): Componente de aplicación de luces y sombras funcional.
- Fase 3: Renderización en ventana OpenGL — objetivo: Desarrollar un componente que renderice los objetos 3D con luces y sombras en una ventana OpenGL. — entregable (NO resolver): Componente de renderización en ventana OpenGL funcional.

Eres un asistente experto en análisis, corrección y generación de archivos de cualquier tipo:
código fuente, documentación, hojas de cálculo, documentos Word, configuraciones, entre otros.
Voy a enviarte una cadena de texto que contiene uno o más archivos. Cada archivo está delimitado por un marcador con el siguiente formato:
// === ARCHIVO: ruta/del/archivo.extension ===
o también puede aparecer como:
## === ARCHIVO: ruta/del/archivo.extension ===
Lo que sigue al marcador puede ser:

El contenido real del archivo (código, texto, YAML, etc.)
Una descripción en lenguaje natural de lo que debe contener el archivo


TU TAREA
PASO 0 — ¿Esto es un proyecto o una carcasa?
Antes de extraer archivos, leé el Briefing (si está) y diagnosticá el adjunto.

Es CARCASA si ocurre CUALQUIERA de estas:
- No hay manifiesto de dependencias del stack del briefing (manifest.json de VTEX IO / package.json / pom.xml / build.gradle / requirements.txt / go.mod / *.tf / *.csproj, según corresponda)
- Hay un "binario" que en realidad es un comentario ("no puede ser mostrado como texto plano", placeholder .fig/.docx vacío)
- Los markdowns ya completan entregables de fases posteriores ("se implementó fade-in", lista de áreas ya resuelta)

Si es CARCASA:
- MATERIALIZÁ un proyecto que arranca en el stack del briefing (VTEX IO Store Framework, Angular, Terraform, pytest, Nest, etc.). Incluí manifiesto, punto de entrada y capa de interfaz reales.
- NO copies los markdowns de "solución" como si fueran el producto. Son ruido de generación.
- NO resuelvas las fases del briefing (están marcadas PROHIBIDO). Dejá el hueco pedagógico: el flujo existe, las microinteracciones/calidad/infra que el reto pide NO están hechas.
- Después seguí al PASO 5 (ZIP).

Si es un proyecto REAL (manifiesto + código que compila o arranca):
- Seguí PASO 1 en adelante. 🔴 compilación sí. 🟡 pedagógico no.

PASO 1 — Detección y extracción
Identifica todos los archivos presentes en la cadena. Para cada archivo extrae:

Su ruta completa (ej: src/main/java/com/pragma/Service.java)
Su contenido o descripción

PASO 2 — Clasificación por tipo
Clasifica cada archivo en una de estas categorías:
A) Código fuente (Java, Python, TypeScript, JavaScript, Kotlin, etc.)
B) Configuración / documentación (YAML, properties, Markdown, JSON, txt, etc.)
C) Excel (.xlsx, .xls, .csv)
D) Word (.docx, .doc)
E) Otro tipo de archivo binario o especial
PASO 3 — Clasificación de errores en código fuente

Objetivo prioritario: que el proyecto compile. No corrijas flujo de negocio ni lógica funcional.

Antes de modificar cualquier archivo de código fuente, clasifica cada problema encontrado en una de estas dos categorías:
🔴 ERROR DE COMPILACIÓN — corregir siempre
Son errores que impiden que el proyecto arranque, sin valor pedagógico:

Import faltante o incorrecto
Clase, método o variable referenciada que no existe en ningún archivo del proyecto
Error de sintaxis
Anotación con atributos inválidos
Dependencia ausente en pom.xml, package.json, etc.
Archivo referenciado que no existe y debe ser creado con implementación mínima

→ CORREGIR estos errores.
🟡 PROBLEMA FUNCIONAL O DE CALIDAD — preservar siempre
Son problemas que no impiden compilar. Pueden ser intencionales para el aprendizaje:

Clave secreta hardcodeada ("secret", "password123")
API deprecada que funciona pero tiene reemplazo moderno
Lógica de negocio incorrecta o incompleta
Código redundante o de baja legibilidad
Falta de validaciones en flujo de negocio
Patrones de diseño incorrectos pero funcionales
Concurrencia no segura
Configuración funcional pero no óptima

→ PRESERVAR tal cual. No corregir, no mejorar, no comentar.
PASO 4 — Procesamiento según tipo de archivo
Tipo A — Código fuente
Aplica únicamente las correcciones clasificadas como 🔴 ERROR DE COMPILACIÓN.
No alteres ningún elemento clasificado como 🟡 PROBLEMA FUNCIONAL O DE CALIDAD.
Si falta un archivo referenciado, créalo con la implementación mínima necesaria para compilar.
Tipo B — Configuración / documentación
Extrae el contenido tal cual, sin modificaciones salvo errores evidentes de sintaxis
(ej: YAML mal indentado).
Tipo C — Excel (.xlsx)
Si viene con contenido real, genera el archivo respetando ese contenido.
Si viene con descripción en lenguaje natural, genera un archivo Excel funcional con:

Fila de encabezados en negrita con color de fondo distintivo
Columnas con ancho ajustado al contenido
Tipos de dato correctos por columna
Validaciones si la descripción lo indica
Hojas nombradas descriptivamente si hay más de una
Filas de ejemplo si no hay datos reales

Tipo D — Word (.docx)
Si viene con contenido real, genera el archivo respetando ese contenido.
Si viene con descripción en lenguaje natural, genera un documento Word funcional con:

Estilos de título (Título 1, Título 2) para jerarquía de secciones
Fuente legible (Calibri o equivalente), tamaño 11-12pt para cuerpo
Márgenes estándar
Tabla de contenido si tiene múltiples secciones
Tablas con encabezados en negrita si aplica

Tipo E — Otro
Genera el archivo con el contenido o estructura más apropiada según la descripción.
PASO 5 — Exportación en ZIP
Empaqueta todos los archivos en un único archivo ZIP descargable respetando exactamente
la estructura de rutas indicada por los marcadores.
El ZIP debe incluir:

Archivos de código con únicamente los errores de compilación corregidos
Archivos de configuración y documentación sin cambios
Archivos nuevos creados para resolver dependencias de compilación faltantes
Archivos Excel y Word generados desde descripción

IMPORTANTE: El ZIP debe estar listo para descargar al finalizar. No preguntes si el usuario
quiere generarlo. Simplemente genera el archivo y proporciona el enlace de descarga; No debes desplegar en el chat el resumen de lo que arreglaste al Zip, solo entregalo.

REGLAS IMPORTANTES

No omitas ningún archivo aunque no tenga errores ni modificaciones
Respeta los nombres y rutas exactas indicadas por los marcadores
Si un archivo no tiene marcador claro, infiere el nombre desde su contenido
Si la cadena contiene solo documentación, placeholders o binarios fake, NO la reproduzcas:
aplicá PASO 0 (materializar el proyecto del briefing). Reproducir la carcasa es un fallo.
No agregues texto después del enlace de descarga del ZIP
No preguntes si el usuario quiere el ZIP: simplemente generalo siempre
Si detectas que falta un archivo de configuración necesario para compilar
(pom.xml, package.json, requirements.txt, build.gradle, etc.), créalo e inclúyelo
inferiendo su contenido desde los imports y frameworks detectados en el código
Nunca corrijas problemas 🟡 aunque parezcan obvios o fáciles de mejorar.
El participante que recibirá este proyecto los debe encontrar y resolver él mismo.


INPUT
Aquí está la cadena con los archivos:

// === ARCHIVO: package.json ===
{
  "name": "opengl-renderer",
  "version": "1.0.0",
  "description": "Motor de renderizado básico con OpenGL y C++ moderno",
  "main": "src/main.cpp",
  "scripts": {
    "build": "cmake -B build && cmake --build build",
    "run": "./build/opengl_renderer",
    "clean": "rm -rf build"
  },
  "keywords": [
    "opengl",
    "rendering",
    "3d",
    "c++",
    "glfw"
  ],
  "author": "Pragma",
  "license": "MIT",
  "dependencies": {
    "glfw": "^3.3.8",
    "glad": "^0.1.36",
    "glm": "^0.9.9.8"
  },
  "devDependencies": {
    "cmake": "^3.20.0"
  }
}

// === ARCHIVO: assets/models/test_cube.obj ===
# Archivo OBJ de prueba para verificar carga y renderizado de modelos 3D
# Generado por Pragma para reto de motor de renderizado básico
# Formato: vertices (v), normales (vn), caras (f)

# Vertices del cubo (8 vertices)
v -0.5 -0.5 -0.5
v  0.5 -0.5 -0.5
v  0.5  0.5 -0.5
v -0.5  0.5 -0.5
v -0.5 -0.5  0.5
v  0.5 -0.5  0.5
v  0.5  0.5  0.5
v -0.5  0.5  0.5

# Normales para cada cara
vn  0.0  0.0 -1.0
vn  0.0  0.0  1.0
vn -1.0  0.0  0.0
vn  1.0  0.0  0.0
vn  0.0 -1.0  0.0
vn  0.0  1.0  0.0

# Definición de caras (6 caras, 2 triángulos por cara)
# Cara frontal
f 1//1 2//1 3//1
f 1//1 3//1 4//1

# Cara trasera
f 5//2 6//2 7//2
f 5//2 7//2 8//2

# Cara izquierda
f 1//3 4//3 8//3
f 1//3 8//3 5//3

# Cara derecha
f 2//4 6//4 7//4
f 2//4 7//4 3//4

# Cara inferior
f 1//5 2//5 6//5
f 1//5 6//5 5//5

# Cara superior
f 4//6 3//6 7//6
f 4//6 7//6 8//6

# Material para el cubo
mtllib test_cube.mtl
usemtl DefaultMaterial

# Coordenadas de textura (opcionales)
vt 0.0 0.0
vt 1.0 0.0
vt 1.0 1.0
vt 0.0 1.0

# Grupos de objetos
s 1
g Cube

# Comentarios adicionales para alcanzar el umbral de caracteres
# Este cubo tiene 8 vertices, 6 normales y 12 caras (2 triángulos por cara)
# Las normales están definidas para cada cara para calcular iluminación correctamente
# El formato OBJ permite definir caras con índices de vertices/texturas/normales
# En este caso usamos solo vertices y normales (formato v//vn)
# El cubo está centrado en el origen (0,0,0) con lado de longitud 1
# Las coordenadas de textura están definidas pero no usadas en este ejemplo
# El archivo MTL asociado definiría propiedades del material como color y reflexión
# Este cubo es ideal para pruebas de carga y renderizado básico
# Permite verificar que el motor carga correctamente vertices, normales y caras
# También permite probar la aplicación de luces y sombras en todas las caras
# La geometría simple facilita la detección de errores en el pipeline de renderizado
# El cubo puede escalarse, rotarse y trasladarse usando transformaciones de OpenGL
# Las normales definidas permiten calcular correctamente los efectos de iluminación
# Este archivo es compatible con la mayoría de loaders OBJ estándar
# Las caras están definidas en orden antihorario para culling correcto
# El cubo tiene 36 índices (12 caras * 3 vertices por cara)
# Este formato es eficiente para pruebas de rendimiento con múltiples instancias

// === ARCHIVO: CMakeLists.txt ===
cmake_minimum_required(VERSION 3.20)
project(opengl_renderer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

set(GLFW_DIR "${CMAKE_SOURCE_DIR}/libs/glfw")
if(NOT EXISTS "${GLFW_DIR}")
    message(STATUS "GLFW not found locally, using system package")
    find_package(GLFW 3.3 REQUIRED)
else()
    add_subdirectory(${GLFW_DIR} build_glfw)
endif()

set(GLAD_DIR "${CMAKE_SOURCE_DIR}/libs/glad")
if(EXISTS "${GLAD_DIR}/CMakeLists.txt")
    add_subdirectory(${GLAD_DIR} build_glad)
    set(GLAD_LIBRARIES glad::glad)
else()
    find_package(glad 0.1 REQUIRED)
    set(GLAD_LIBRARIES glad::glad)
endif()

set(GLM_DIR "${CMAKE_SOURCE_DIR}/libs/glm")
if(EXISTS "${GLM_DIR}")
    set(GLM_INCLUDE_DIR "${GLM_DIR}")
else()
    find_package(glm 0.9.9 REQUIRED)
    set(GLM_INCLUDE_DIR "${glm_INCLUDE_DIRS}")
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${GLM_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
)

set(SOURCES
    src/main.cpp
)

add_executable(opengl_renderer ${SOURCES})

target_link_libraries(opengl_renderer PRIVATE
    GLFW::GLFW
    ${GLAD_LIBRARIES}
    OpenGL::GL
)

target_compile_options(opengl_renderer PRIVATE
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-g -O0>
)

add_custom_command(TARGET opengl_renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:opengl_renderer>/shaders
)

add_custom_command(TARGET opengl_renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:opengl_renderer>/assets
)

message(STATUS "OpenGL Renderer configured")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")

// === ARCHIVO: README.md ===
# OpenGL Renderer - Motor de Renderizado Básico

## Descripción

Motor de renderizado 3D básico desarrollado en C++20 utilizando OpenGL 4.6 y GLFW. El motor es capaz de cargar objetos desde archivos OBJ, aplicar iluminación y sombras, y renderizar en una ventana interactiva.

## Requisitos del Sistema

- **Compilador**: GCC 11+, Clang 13+, MSVC 2019+ o equivalente con soporte C++20
- **CMake**: Versión 3.20 o superior
- **Librerías**:
  - GLFW 3.3.8
  - GLAD 0.1.36
  - GLM 0.9.9.8

### Instalación de dependencias (Linux/Ubuntu)

```bash
sudo apt-get install cmake libglfw3-dev libglm-dev libglad-dev
```

### Instalación de dependencias (macOS con Homebrew)

```bash
brew install cmake glm glfw glad
```

## Compilación

1. Crear directorio de build:
```bash
mkdir build && cd build
```

2. Configurar con CMake:
```bash
cmake ..
```

3. Compilar:
```bash
cmake --build . -j$(nproc)
```

## Ejecución

Desde el directorio build:
```bash
./opengl_renderer
```

O desde la raíz del proyecto:
```bash
npm run run
```

## Estructura del Proyecto

```
opengl-renderer/
├── CMakeLists.txt          # Configuración de build
├── package.json            # Metadata y scripts
├── README.md               # Este archivo
├── assets/
│   └── models/             # Modelos OBJ
│       └── test_cube.obj
├── shaders/
│   ├── vertex_shader.glsl
│   └── fragment_shader.glsl
└── src/
    ├── main.cpp            # Punto de entrada
    ├── loader/
    │   ├── ObjLoader.hpp
    │   └── ObjLoader.cpp
    ├── lighting/
    │   ├── LightManager.hpp
    │   └── LightManager.cpp
    ├── renderer/
    │   ├── Renderer.hpp
    │   └── Renderer.cpp
    └── utils/
        ├── ErrorHandler.hpp
        └── ErrorHandler.cpp
```

## Uso

El motor inicializa automáticamente una ventana OpenGL y carga el modelo de prueba `test_cube.obj`. Los controles básicos permiten cerrar la ventana presionando ESC o cerrando la ventana.

## Arquitectura

El proyecto sigue una arquitectura por capas:

- **Capa de carga** (`loader/`): Responsabilidad de parsear archivos OBJ y convertirlos en datos utilizables por OpenGL.
- **Capa de iluminación** (`lighting/`): Gestiona fuentes de luz, cálculos de iluminación y sombras.
- **Capa de renderizado** (`renderer/`): Orquestra el pipeline de renderizado, configura shaders y coordena el drawing.
- **Capa de utilidades** (`utils/`): Herramientas compartidas como manejo de errores y logging.

## Objetivo de Rendimiento

El motor está optimizado para alcanzar 60 FPS en escenas con al menos 10 objetos.

## Licencia

MIT - Pragma

// === ARCHIVO: src/main.cpp ===
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


// === ARCHIVO: src/loader/ObjLoader.hpp ===
#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace engine {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    Vertex() : position(0.0f), normal(0.0f), texCoord(0.0f) {}
    Vertex(const glm::vec3& pos) : position(pos), normal(0.0f), texCoord(0.0f) {}
    Vertex(const glm::vec3& pos, const glm::vec3& norm, const glm::vec2& uv)
        : position(pos), normal(norm), texCoord(uv) {}
};

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::string name;

    MeshData() : name("default") {}
    explicit MeshData(const std::string& meshName) : name(meshName) {}

    void clear() {
        vertices.clear();
        indices.clear();
    }

    bool isEmpty() const {
        return vertices.empty();
    }
};

class ObjLoader {
public:
    explicit ObjLoader();
    ~ObjLoader() = default;

    ObjLoader(const ObjLoader&) = delete;
    ObjLoader& operator=(const ObjLoader&) = delete;
    ObjLoader(ObjLoader&&) = default;
    ObjLoader& operator=(ObjLoader&&) = default;

    MeshData load(const std::string& filePath);
    bool validate() const;
    std::string getLastError() const;
    unsigned int getLoadedCount() const;

private:
    std::string lastError_;
    unsigned int loadedCount_;

    void parseVertexLine(const std::string& line, std::vector<glm::vec3>& positions);
    void parseNormalLine(const std::string& line, std::vector<glm::vec3>& normals);
    void parseTexCoordLine(const std::string& line, std::vector<glm::vec2>& texCoords);
    void parseFaceLine(const std::string& line, MeshData& mesh,
                       const std::vector<glm::vec3>& positions,
                       const std::vector<glm::vec3>& normals,
                       const std::vector<glm::vec2>& texCoords);
    void processFaceIndices(const std::string& vertexStr, unsigned int& outVertexIdx,
                            unsigned int& outNormalIdx, unsigned int& outTexCoordIdx);
    void computeMissingNormals(MeshData& mesh);
    void triangulateFace(std::vector<Vertex>& faceVertices, std::vector<unsigned int>& faceIndices);
    std::string extractFileName(const std::string& path) const;
};

} // namespace engine

#endif // OBJ_LOADER_HPP
// === ARCHIVO: src/loader/ObjLoader.cpp ===
#include "loader/ObjLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace engine {

ObjLoader::ObjLoader() : loadedCount_(0) {}

MeshData ObjLoader::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        lastError_ = "No se pudo abrir el archivo: " + filePath;
        return MeshData();
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    MeshData mesh(extractFileName(filePath));

    std::string line;
    unsigned int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            parseVertexLine(line, positions);
        } else if (prefix == "vn") {
            parseNormalLine(line, normals);
        } else if (prefix == "vt") {
            parseTexCoordLine(line, texCoords);
        } else if (prefix == "f") {
            parseFaceLine(line, mesh, positions, normals, texCoords);
        }
    }

    file.close();

    if (mesh.isEmpty()) {
        lastError_ = "El archivo OBJ no contiene caras válidas: " + filePath;
        return MeshData();
    }

    if (normals.empty()) {
        computeMissingNormals(mesh);
    }

    loadedCount_++;
    return mesh;
}

void ObjLoader::parseVertexLine(const std::string& line, std::vector<glm::vec3>& positions) {
    std::istringstream iss(line);
    char prefix;
    float x, y, z;

    iss >> prefix >> x >> y >> z;
    if (iss.fail()) {
        lastError_ = "Formato de vértice inválido: " + line;
        return;
    }

    positions.emplace_back(x, y, z);
}

void ObjLoader::parseNormalLine(const std::string& line, std::vector<glm::vec3>& normals) {
    std::istringstream iss(line);
    char prefix;
    float x, y, z;

    iss >> prefix >> x >> y >> z;
    if (iss.fail()) {
        lastError_ = "Formato de normal inválido: " + line;
        return;
    }

    normals.emplace_back(x, y, z);
}

void ObjLoader::parseTexCoordLine(const std::string& line, std::vector<glm::vec2>& texCoords) {
    std::istringstream iss(line);
    char prefix;
    float u, v;

    iss >> prefix >> u >> v;
    if (iss.fail()) {
        lastError_ = "Formato de coordenada de textura inválido: " + line;
        return;
    }

    texCoords.emplace_back(u, v);
}

void ObjLoader::parseFaceLine(const std::string& line, MeshData& mesh,
                               const std::vector<glm::vec3>& positions,
                               const std::vector<glm::vec3>& normals,
                               const std::vector<glm::vec2>& texCoords) {
    std::istringstream iss(line);
    char prefix;
    iss >> prefix;

    std::vector<Vertex> faceVertices;
    std::string vertexStr;

    while (iss >> vertexStr) {
        unsigned int vIdx, nIdx, tIdx;
        processFaceIndices(vertexStr, vIdx, nIdx, tIdx);

        Vertex v;

        if (vIdx > 0 && vIdx <= positions.size()) {
            v.position = positions[vIdx - 1];
        } else {
            lastError_ = "Índice de vértice fuera de rango: " + std::to_string(vIdx);
            return;
        }

        if (!normals.empty() && nIdx > 0 && nIdx <= normals.size()) {
            v.normal = normals[nIdx - 1];
        }

        if (!texCoords.empty() && tIdx > 0 && tIdx <= texCoords.size()) {
            v.texCoord = texCoords[tIdx - 1];
        }

        faceVertices.push_back(v);
    }

    triangulateFace(faceVertices, mesh.vertices);
}

void ObjLoader::processFaceIndices(const std::string& vertexStr, unsigned int& outVertexIdx,
                                    unsigned int& outNormalIdx, unsigned int& outTexCoordIdx) {
    std::istringstream iss(vertexStr);
    std::string token;

    outVertexIdx = 0;
    outNormalIdx = 0;
    outTexCoordIdx = 0;

    int index = 0;
    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            try {
                unsigned int value = std::stoul(token);
                if (index == 0) outVertexIdx = value;
                else if (index == 1) outTexCoordIdx = value;
                else if (index == 2) outNormalIdx = value;
            } catch (const std::exception&) {
                lastError_ = "Índice inválido en cara: " + token;
            }
        }
        index++;
    }
}

void ObjLoader::computeMissingNormals(MeshData& mesh) {
    for (size_t i = 0; i < mesh.indices.size(); i += 3) {
        unsigned int i0 = mesh.indices[i];
        unsigned int i1 = mesh.indices[i + 1];
        unsigned int i2 = mesh.indices[i + 2];

        const glm::vec3& v0 = mesh.vertices[i0].position;
        const glm::vec3& v1 = mesh.vertices[i1].position;
        const glm::vec3& v2 = mesh.vertices[i2].position;

        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));

        mesh.vertices[i0].normal += faceNormal;
        mesh.vertices[i1].normal += faceNormal;
        mesh.vertices[i2].normal += faceNormal;
    }

    for (auto& vertex : mesh.vertices) {
        vertex.normal = glm::normalize(vertex.normal);
    }
}

void ObjLoader::triangulateFace(std::vector<Vertex>& faceVertices, std::vector<unsigned int>& vertices) {
    if (faceVertices.size() < 3) {
        return;
    }

    size_t baseIndex = vertices.size();

    for (size_t i = 0; i < faceVertices.size(); ++i) {
        vertices.push_back(faceVertices[i]);
    }

    if (faceVertices.size() == 3) {
        vertices.push_back(0);
        vertices.push_back(1);
        vertices.push_back(2);
    } else if (faceVertices.size() == 4) {
        vertices.push_back(baseIndex);
        vertices.push_back(baseIndex + 1);
        vertices.push_back(baseIndex + 2);

        vertices.push_back(baseIndex);
        vertices.push_back(baseIndex + 2);
        vertices.push_back(baseIndex + 3);
    } else {
        for (size_t i = 1; i < faceVertices.size() - 1; ++i) {
            vertices.push_back(baseIndex);
            vertices.push_back(baseIndex + i);
            vertices.push_back(baseIndex + i + 1);
        }
    }
}

std::string ObjLoader::extractFileName(const std::string& path) const {
    size_t lastSlash = path.find_last_of("/\\");
    std::string fileName = (lastSlash != std::string::npos) ? path.substr(lastSlash + 1) : path;

    size_t dotPos = fileName.rfind(".obj");
    if (dotPos != std::string::npos) {
        fileName = fileName.substr(0, dotPos);
    }

    return fileName;
}

bool ObjLoader::validate() const {
    return lastError_.empty();
}

std::string ObjLoader::getLastError() const {
    return lastError_;
}

unsigned int ObjLoader::getLoadedCount() const {
    return loadedCount_;
}

} // namespace engine


// === ARCHIVO: src/lighting/LightManager.hpp ===
#ifndef LIGHT_MANAGER_HPP
#define LIGHT_MANAGER_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <string>
#include <memory>

namespace OpenGLRenderer {

enum class LightType {
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT
};

struct LightProperties {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 direction{0.0f, -1.0f, 0.0f};
    glm::vec3 color{1.0f, 1.0f, 1.0f};
    glm::vec3 ambient{0.1f, 0.1f, 0.1f};
    glm::vec3 diffuse{0.8f, 0.8f, 0.8f};
    glm::vec3 specular{1.0f, 1.0f, 1.0f};
    
    float intensity{1.0f};
    float constant{1.0f};
    float linear{0.09f};
    float quadratic{0.032f};
    
    float cutOffAngle{12.5f};
    float outerCutOffAngle{15.0f};
    
    bool enabled{true};
    int shadowMapIndex{-1};
};

struct ShadowMapConfig {
    int width{1024};
    int height{1024};
    float nearPlane{0.1f};
    float farPlane{100.0f};
    glm::mat4 lightSpaceMatrix{1.0f};
    bool enabled{false};
};

class LightManager {
public:
    LightManager();
    ~LightManager();
    
    LightManager(const LightManager&) = delete;
    LightManager& operator=(const LightManager&) = delete;
    LightManager(LightManager&&) noexcept;
    LightManager& operator=(LightManager&&) noexcept;
    
    int addLight(LightType type, const LightProperties& properties);
    void removeLight(int lightId);
    void updateLight(int lightId, const LightProperties& properties);
    
    const LightProperties* getLight(int lightId) const;
    const std::vector<LightProperties>& getAllLights() const { return lights_; }
    size_t getLightCount() const { return lights_. size(); }
    
    void setAmbientLight(const glm::vec3& ambient);
    const glm::vec3& getAmbientLight() const { return globalAmbient_; }
    
    void setShadowEnabled(bool enabled);
    bool isShadowEnabled() const { return shadowsEnabled_; }
    
    void configureShadowMap(int lightId, const ShadowMapConfig& config);
    const ShadowMapConfig* getShadowConfig(int lightId) const;
    
    void updateShaderUniforms(unsigned int shaderProgram);
    void updateLightSpaceMatrices(const glm::mat4& viewProjection);
    
    void setLightPosition(int lightId, const glm::vec3& position);
    void setLightDirection(int lightId, const glm::vec3& direction);
    void setLightColor(int lightId, const glm::vec3& color);
    void setLightIntensity(int lightId, float intensity);
    
    void loadLightingConfig(const std::string& configPath);
    void saveLightingConfig(const std::string& configPath) const;
    
    static const int MAX_POINT_LIGHTS = 16;
    static const int MAX_DIRECTIONAL_LIGHTS = 4;
    static const int MAX_SPOT_LIGHTS = 8;
    static const int MAX_SHADOW_MAPS = 4;

private:
    struct LightData {
        LightType type;
        LightProperties properties;
        ShadowMapConfig shadowConfig;
    };
    
    std::vector<LightData> lights_;
    glm::vec3 globalAmbient_{0.1f, 0.1f, 0.1f};
    bool shadowsEnabled_{false};
    
    int nextLightId_{0};
    int pointLightCount_{0};
    int directionalLightCount_{0};
    int spotLightCount_{0};
    
    bool validateLightTypeLimit(LightType type) const;
    void updateAttenuation(LightProperties& light) const;
    void calculateLightSpaceMatrix(int lightId);
    
    std::string lightTypeToString(LightType type) const;
    LightType stringToLightType(const std::string& str) const;
};

}

#endif
// === ARCHIVO: src/lighting/LightManager.cpp ===
#include "lighting/LightManager.hpp"
#include "utils/ErrorHandler.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace OpenGLRenderer {

LightManager::LightManager() 
    : lights_()
    , globalAmbient_{0.1f, 0.1f, 0.1f}
    , shadowsEnabled_{false}
    , nextLightId_{0}
    , pointLightCount_{0}
    , directionalLightCount_{0}
    , spotLightCount_{0}
{
    lights_.reserve(MAX_POINT_LIGHTS + MAX_DIRECTIONAL_LIGHTS + MAX_SPOT_LIGHTS);
}

LightManager::~LightManager() = default;

LightManager::LightManager(LightManager&& other) noexcept
    : lights_(std::move(other.lights_))
    , globalAmbient_(other.globalAmbient_)
    , shadowsEnabled_(other.shadowsEnabled_)
    , nextLightId_(other.nextLightId_)
    , pointLightCount_(other.pointLightCount_)
    , directionalLightCount_(other.directionalLightCount_)
    , spotLightCount_(other.spotLightCount_)
{
    other.lights_.clear();
    other.nextLightId_ = 0;
    other.pointLightCount_ = 0;
    other.directionalLightCount_ = 0;
    other.spotLightCount_ = 0;
}

LightManager& LightManager::operator=(LightManager&& other) noexcept {
    if (this != &other) {
        lights_ = std::move(other.lights_);
        globalAmbient_ = other.globalAmbient_;
        shadowsEnabled_ = other.shadowsEnabled_;
        nextLightId_ = other.nextLightId_;
        pointLightCount_ = other.pointLightCount_;
        directionalLightCount_ = other.directionalLightCount_;
        spotLightCount_ = other.spotLightCount_;
        
        other.lights_.clear();
        other.nextLightId_ = 0;
        other.pointLightCount_ = 0;
        other.directionalLightCount_ = 0;
        other.spotLightCount_ = 0;
    }
    return *this;
}

int LightManager::addLight(LightType type, const LightProperties& properties) {
    if (!validateLightTypeLimit(type)) {
        throw std::runtime_error("Maximum number of lights for type exceeded");
    }
    
    LightData data;
    data.type = type;
    data.properties = properties;
    data.shadowConfig = ShadowMapConfig{};
    
    int lightId = nextLightId_++;
    lights_.push_back(std::move(data));
    
    switch (type) {
        case LightType::POINT_LIGHT:
            ++pointLightCount_;
            break;
        case LightType::DIRECTIONAL_LIGHT:
            ++directionalLightCount_;
            if (shadowsEnabled_) {
                lights_.back().shadowConfig.enabled = true;
            }
            break;
        case LightType::SPOT_LIGHT:
            ++spotLightCount_;
            if (shadowsEnabled_) {
                lights_.back().shadowConfig.enabled = true;
            }
            break;
    }
    
    return lightId;
}

void LightManager::removeLight(int lightId) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) { 
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it == lights_.end()) {
        return;
    }
    
    switch (it->type) {
        case LightType::POINT_LIGHT:
            --pointLightCount_;
            break;
        case LightType::DIRECTIONAL_LIGHT:
            --directionalLightCount_;
            break;
        case LightType::SPOT_LIGHT:
            --spotLightCount_;
            break;
    }
    
    lights_.erase(it);
}

void LightManager::updateLight(int lightId, const LightProperties& properties) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties = properties;
        updateAttenuation(it->properties);
    }
}

const LightProperties* LightManager::getLight(int lightId) const {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    return (it != lights_.end()) ? &it->properties : nullptr;
}

void LightManager::setAmbientLight(const glm::vec3& ambient) {
    globalAmbient_ = ambient;
}

void LightManager::setShadowEnabled(bool enabled) {
    shadowsEnabled_ = enabled;
    for (auto& light : lights_) {
        if (light.type != LightType::POINT_LIGHT) {
            light.shadowConfig.enabled = enabled;
        }
    }
}

void LightManager::configureShadowMap(int lightId, const ShadowMapConfig& config) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end() && it->type != LightType::POINT_LIGHT) {
        it->shadowConfig = config;
        calculateLightSpaceMatrix(lightId);
    }
}

const ShadowMapConfig* LightManager::getShadowConfig(int lightId) const {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    return (it != lights_.end()) ? &it->shadowConfig : nullptr;
}

void LightManager::updateShaderUniforms(unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    
    glUniform3fv(glGetUniformLocation(shaderProgram, "u_globalAmbient"), 1, 
                 &globalAmbient_[0]);
    
    int pointLightIndex = 0;
    int directionalLightIndex = 0;
    int spotLightIndex = 0;
    
    for (const auto& light : lights_) {
        if (!light.properties.enabled) continue;
        
        std::string prefix;
        int index = 0;
        
        switch (light.type) {
            case LightType::POINT_LIGHT:
                prefix = "u_pointLights[" + std::to_string(pointLightIndex) + "]";
                index = pointLightIndex++;
                break;
            case LightType::DIRECTIONAL_LIGHT:
                prefix = "u_directionalLights[" + std::to_string(directionalLightIndex) + "]";
                index = directionalLightIndex++;
                break;
            case LightType::SPOT_LIGHT:
                prefix = "u_spotLights[" + std::to_string(spotLightIndex) + "]";
                index = spotLightIndex++;
                break;
        }
        
        std::string basePrefix = prefix + ".";
        
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "position").c_str()), 1, &light.properties.position[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "direction").c_str()), 1, &light.properties.direction[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "color").c_str()), 1, &light.properties.color[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "ambient").c_str()), 1, &light.properties.ambient[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "diffuse").c_str()), 1, &light.properties.diffuse[0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, 
            (basePrefix + "specular").c_str()), 1, &light.properties.specular[0]);
        
        glUniform1f(glGetUniformLocation(shaderProgram, 
            (basePrefix + "intensity").c_str()), light.properties.intensity);
        glUniform1f(glGetUniformLocation(shaderProgram, 
            (basePrefix + "constant").c_str()), light.properties.constant);
        glUniform1f(glGetUniformLocation(shaderProgram, 
            (basePrefix + "linear").c_str()), light.properties.linear);
        glUniform1f(glGetUniformLocation(shaderProgram, 
            (basePrefix + "quadratic").c_str()), light.properties.quadratic);
        
        if (light.type == LightType::SPOT_LIGHT) {
            glUniform1f(glGetUniformLocation(shaderProgram, 
                (basePrefix + "cutOff").c_str()), 
                glm::cos(glm::radians(light.properties.cutOffAngle)));
            glUniform1f(glGetUniformLocation(shaderProgram, 
                (basePrefix + "outerCutOff").c_str()), 
                glm::cos(glm::radians(light.properties.outerCutOffAngle)));
        }
    }
    
    glUniform1i(glGetUniformLocation(shaderProgram, "u_pointLightCount"), pointLightIndex);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_directionalLightCount"), directionalLightIndex);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_spotLightCount"), spotLightIndex);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_shadowsEnabled"), shadowsEnabled_ ? 1 : 0);
}

void LightManager::updateLightSpaceMatrices(const glm::mat4& viewProjection) {
    for (auto& light : lights_) {
        if (light.shadowConfig.enabled) {
            light.shadowConfig.lightSpaceMatrix = viewProjection * 
                glm::lookAt(light.properties.position, 
                           light.properties.position + light.properties.direction,
                           glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }
}

void LightManager::setLightPosition(int lightId, const glm::vec3& position) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties.position = position;
        if (it->shadowConfig.enabled) {
            calculateLightSpaceMatrix(lightId);
        }
    }
}

void LightManager::setLightDirection(int lightId, const glm::vec3& direction) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties.direction = glm::normalize(direction);
        if (it->shadowConfig.enabled) {
            calculateLightSpaceMatrix(lightId);
        }
    }
}

void LightManager::setLightColor(int lightId, const glm::vec3& color) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties.color = color;
    }
}

void LightManager::setLightIntensity(int lightId, float intensity) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end()) {
        it->properties.intensity = intensity;
    }
}

void LightManager::loadLightingConfig(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        return;
    }
    
    lights_.clear();
    nextLightId_ = 0;
    pointLightCount_ = 0;
    directionalLightCount_ = 0;
    spotLightCount_ = 0;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        std::string key;
        iss >> key;
        
        if (key == "ambient") {
            glm::vec3 ambient;
            iss >> ambient.x >> ambient.y >> ambient.z;
            globalAmbient_ = ambient;
        } else if (key == "shadows") {
            int enabled;
            iss >> enabled;
            shadowsEnabled_ = (enabled != 0);
        } else if (key == "point" || key == "directional" || key == "spot") {
            LightType type = stringToLightType(key);
            LightProperties props;
            iss >> props.position.x >> props.position.y >> props.position.z
                >> props.color.r >> props.color.g >> props.color.b
                >> props.intensity;
            addLight(type, props);
        }
    }
}

void LightManager::saveLightingConfig(const std::string& configPath) const {
    std::ofstream file(configPath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config file for writing: " + configPath);
    }
    
    file << "# Lighting Configuration\n";
    file << "ambient " << globalAmbient_.x << " " << globalAmbient_.y << " " << globalAmbient_.z << "\n";
    file << "shadows " << (shadowsEnabled_ ? 1 : 0) << "\n";
    
    for (const auto& light : lights_) {
        file << lightTypeToString(light.type) << " "
             << light.properties.position.x << " " << light.properties.position.y << " " << light.properties.position.z << " "
             << light.properties.color.r << " " << light.properties.color.g << " " << light.properties.color.b << " "
             << light.properties.intensity << "\n";
    }
}

bool LightManager::validateLightTypeLimit(LightType type) const {
    switch (type) {
        case LightType::POINT_LIGHT:
            return pointLightCount_ < MAX_POINT_LIGHTS;
        case LightType::DIRECTIONAL_LIGHT:
            return directionalLightCount_ < MAX_DIRECTIONAL_LIGHTS;
        case LightType::SPOT_LIGHT:
            return spotLightCount_ < MAX_SPOT_LIGHTS;
    }
    return false;
}

void LightManager::updateAttenuation(LightProperties& light) const {
    float distance = glm::length(light.position);
    if (distance > 0.0f) {
        float attenuation = 1.0f / (light.constant + light.linear * distance + 
                                     light.quadratic * distance * distance);
        light.intensity = attenuation;
    }
}

void LightManager::calculateLightSpaceMatrix(int lightId) {
    auto it = std::find_if(lights_.begin(), lights_.end(), 
        [lightId](const LightData& data) {
            return static_cast<int>(std::distance(&lights_.front(), &data)) == lightId;
        });
    
    if (it != lights_.end() && it->shadowConfig.enabled) {
        glm::mat4 lightView = glm::lookAt(it->properties.position,
                                          it->properties.position + it->properties.direction,
                                          glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f,
                                         it->shadowConfig.nearPlane, 
                                         it->shadowConfig.farPlane);
        it->shadowConfig.lightSpaceMatrix = lightProj * lightView;
    }
}

std::string LightManager::lightTypeToString(LightType type) const {
    switch (type) {
        case LightType::POINT_LIGHT: return "point";
        case LightType::DIRECTIONAL_LIGHT: return "directional";
        case LightType::SPOT_LIGHT: return "spot";
    }
    return "unknown";
}

LightType LightManager::stringToLightType(const std::string& str) const {
    if (str == "point") return LightType::POINT_LIGHT;
    if (str == "directional") return LightType::DIRECTIONAL_LIGHT;
    if (str == "spot") return LightType::SPOT_LIGHT;
    return LightType::POINT_LIGHT;
}

}

// === ARCHIVO: src/renderer/Renderer.hpp ===
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace opengl_renderer {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Mesh {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLsizei indexCount;
    GLenum primitiveType;
    
    Mesh() : vao(0), vbo(0), ebo(0), indexCount(0), primitiveType(GL_TRIANGLES) {}
    
    ~Mesh() {
        if (vao != 0) glDeleteVertexArrays(1, &vao);
        if (vbo != 0) glDeleteBuffers(1, &vbo);
        if (ebo != 0) glDeleteBuffers(1, &ebo);
    }
    
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    
    Mesh(Mesh&& other) noexcept 
        : vao(other.vao), vbo(other.vbo), ebo(other.ebo),
          indexCount(other.indexCount), primitiveType(other.primitiveType) {
        other.vao = 0;
        other.vbo = 0;
        other.ebo = 0;
        other.indexCount = 0;
    }
    
    Mesh& operator=(Mesh&& other) noexcept {
        if (this != &other) {
            if (vao != 0) glDeleteVertexArrays(1, &vao);
            if (vbo != 0) glDeleteBuffers(1, &vbo);
            if (ebo != 0) glDeleteBuffers(1, &ebo);
            
            vao = other.vao;
            vbo = other.vbo;
            ebo = other.ebo;
            indexCount = other.indexCount;
            primitiveType = other.primitiveType;
            
            other.vao = 0;
            other.vbo = 0;
            other.ebo = 0;
            other.indexCount = 0;
        }
        return *this;
    }
};

struct RenderObject {
    std::string name;
    Mesh mesh;
    glm::mat4 modelMatrix;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 color;
    float shininess;
    
    RenderObject() 
        : name("default"), 
          modelMatrix(1.0f), 
          position(0.0f), 
          rotation(0.0f), 
          scale(1.0f), 
          color(1.0f, 1.0f, 1.0f),
          shininess(32.0f) {}
};

class Renderer {
public:
    Renderer(GLFWwindow* window);
    ~Renderer();
    
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    
    bool initialize();
    void renderFrame();
    void addObject(const RenderObject& object);
    void removeObject(const std::string& name);
    void clearObjects();
    
    void setViewMatrix(const glm::mat4& view);
    void setProjectionMatrix(const glm::mat4& projection);
    void setAmbientLight(float ambient);
    void setLightPosition(int lightIndex, const glm::vec3& position);
    void setLightColor(int lightIndex, const glm::vec3& color);
    void setLightIntensity(int lightIndex, float intensity);
    
    bool loadShaders(const std::string& vertexPath, const std::string& fragmentPath);
    void cleanup();
    
    int getObjectCount() const { return static_cast<int>(m_objects.size()); }
    float getFPS() const { return m_fps; }
    
private:
    GLFWwindow* m_window;
    GLuint m_shaderProgram;
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    
    std::vector<RenderObject> m_objects;
    std::unordered_map<std::string, Mesh> m_meshCache;
    
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    
    float m_ambientLight;
    std::vector<glm::vec3> m_lightPositions;
    std::vector<glm::vec3> m_lightColors;
    std::vector<float> m_lightIntensities;
    
    double m_lastFrameTime;
    float m_fps;
    int m_frameCount;
    double m_fpsTimer;
    
    bool m_initialized;
    
    bool compileShader(GLuint shader, const std::string& source);
    bool linkProgram();
    std::string readShaderFile(const std::string& path);
    Mesh createMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
    void updateModelMatrix(RenderObject& obj);
    void setupLightingUniforms();
    void setupObjectUniforms(const RenderObject& obj);
};

}

#endif

// === ARCHIVO: src/renderer/Renderer.cpp ===
#include "Renderer.hpp"
#include "../utils/ErrorHandler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace opengl_renderer {

Renderer::Renderer(GLFWwindow* window)
    : m_window(window)
    , m_shaderProgram(0)
    , m_vertexShader(0)
    , m_fragmentShader(0)
    , m_viewMatrix(1.0f)
    , m_projectionMatrix(1.0f)
    , m_ambientLight(0.1f)
    , m_lastFrameTime(0.0)
    , m_fps(0.0f)
    , m_frameCount(0)
    , m_fpsTimer(0.0)
    , m_initialized(false) {
    
    m_lightPositions.resize(4, glm::vec3(0.0f, 5.0f, 5.0f));
    m_lightColors.resize(4, glm::vec3(1.0f, 1.0f, 1.0f));
    m_lightIntensities.resize(4, 1.0f);
}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize() {
    if (m_initialized) {
        ErrorHandler::log("Renderer ya inicializado");
        return true;
    }
    
    if (!m_window) {
        ErrorHandler::reportError("Renderer: ventana nula en inicializacion");
        return false;
    }
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    m_initialized = true;
    ErrorHandler::log("Renderer inicializado correctamente");
    return true;
}

bool Renderer::loadShaders(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = readShaderFile(vertexPath);
    std::string fragmentSource = readShaderFile(fragmentPath);
    
    if (vertexSource.empty() || fragmentSource.empty()) {
        ErrorHandler::reportError("Renderer: fallo al cargar archivos de shader");
        return false;
    }
    
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    if (!compileShader(m_vertexShader, vertexSource)) {
        ErrorHandler::reportError("Renderer: fallo al compilar vertex shader");
        return false;
    }
    
    if (!compileShader(m_fragmentShader, fragmentSource)) {
        ErrorHandler::reportError("Renderer: fallo al compilar fragment shader");
        return false;
    }
    
    if (!linkProgram()) {
        ErrorHandler::reportError("Renderer: fallo al vincular programa de shaders");
        return false;
    }
    
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
    m_vertexShader = 0;
    m_fragmentShader = 0;
    
    ErrorHandler::log("Shaders cargados y compilados correctamente");
    return true;
}

std::string Renderer::readShaderFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        ErrorHandler::reportError("Renderer: no se pudo abrir archivo shader: " + path);
        return "";
    }
    
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

bool Renderer::compileShader(GLuint shader, const std::string& source) {
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        ErrorHandler::reportError("Renderer: error de compilacion de shader: " + std::string(infoLog));
        return false;
    }
    
    return true;
}

bool Renderer::linkProgram() {
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);
    
    GLint success;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
        ErrorHandler::reportError("Renderer: error de vinculacion de programa: " + std::string(infoLog));
        return false;
    }
    
    return true;
}

Mesh Renderer::createMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
    Mesh mesh;
    
    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);
    
    glBindVertexArray(mesh.vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    
    GLsizei stride = sizeof(Vertex);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    
    mesh.indexCount = static_cast<GLsizei>(indices.size());
    
    ErrorHandler::log("Mesh creado con " + std::to_string(vertices.size()) + " vertices");
    return mesh;
}

void Renderer::addObject(const RenderObject& object) {
    m_objects.push_back(object);
    ErrorHandler::log("Objeto anadido al renderer: " + object.name);
}

void Renderer::removeObject(const std::string& name) {
    auto it = std::remove_if(m_objects.begin(), m_objects.end(), 
        [&name](const RenderObject& obj) { return obj.name == name; });
    m_objects.erase(it, m_objects.end());
}

void Renderer::clearObjects() {
    m_objects.clear();
    ErrorHandler::log("Todos los objetos eliminados del renderer");
}

void Renderer::setViewMatrix(const glm::mat4& view) {
    m_viewMatrix = view;
}

void Renderer::setProjectionMatrix(const glm::mat4& projection) {
    m_projectionMatrix = projection;
}

void Renderer::setAmbientLight(float ambient) {
    m_ambientLight = glm::clamp(ambient, 0.0f, 1.0f);
}

void Renderer::setLightPosition(int lightIndex, const glm::vec3& position) {
    if (lightIndex >= 0 && lightIndex < static_cast<int>(m_lightPositions.size())) {
        m_lightPositions[lightIndex] = position;
    }
}

void Renderer::setLightColor(int lightIndex, const glm::vec3& color) {
    if (lightIndex >= 0 && lightIndex < static_cast<int>(m_lightColors.size())) {
        m_lightColors[lightIndex] = color;
    }
}

void Renderer::setLightIntensity(int lightIndex, float intensity) {
    if (lightIndex >= 0 && lightIndex < static_cast<int>(m_lightIntensities.size())) {
        m_lightIntensities[lightIndex] = glm::clamp(intensity, 0.0f, 10.0f);
    }
}

void Renderer::updateModelMatrix(RenderObject& obj) {
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), obj.position);
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), obj.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), obj.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), obj.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), obj.scale);
    
    obj.modelMatrix = translation * rotationX * rotationY * rotationZ * scale;
}

void Renderer::setupLightingUniforms() {
    GLint ambientLoc = glGetUniformLocation(m_shaderProgram, "ambientLight");
    glUniform1f(ambientLoc, m_ambientLight);
    
    for (size_t i = 0; i < m_lightPositions.size(); ++i) {
        std::string posName = "lights[" + std::to_string(i) + "].position";
        std::string colorName = "lights[" + std::to_string(i) + "].color";
        std::string intensityName = "lights[" + std::to_string(i) + "].intensity";
        
        GLint posLoc = glGetUniformLocation(m_shaderProgram, posName.c_str());
        GLint colorLoc = glGetUniformLocation(m_shaderProgram, colorName.c_str());
        GLint intensityLoc = glGetUniformLocation(m_shaderProgram, intensityName.c_str());
        
        glUniform3fv(posLoc, 1, glm::value_ptr(m_lightPositions[i]));
        glUniform3fv(colorLoc, 1, glm::value_ptr(m_lightColors[i]));
        glUniform1f(intensityLoc, m_lightIntensities[i]);
    }
}

void Renderer::setupObjectUniforms(const RenderObject& obj) {
    GLint modelLoc = glGetUniformLocation(m_shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(obj.modelMatrix));
    
    GLint viewLoc = glGetUniformLocation(m_shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
    
    GLint projectionLoc = glGetUniformLocation(m_shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
    
    GLint colorLoc = glGetUniformLocation(m_shaderProgram, "objectColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(obj.color));
    
    GLint shininessLoc = glGetUniformLocation(m_shaderProgram, "shininess");
    glUniform1f(shininessLoc, obj.shininess);
}

void Renderer::renderFrame() {
    if (!m_initialized) {
        ErrorHandler::reportError("Renderer: intento de renderizar sin inicializar");
        return;
    }
    
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - m_lastFrameTime;
    m_lastFrameTime = currentTime;
    
    m_frameCount++;
    m_fpsTimer += deltaTime;
    if (m_fpsTimer >= 1.0) {
        m_fps = static_cast<float>(m_frameCount) / static_cast<float>(m_fpsTimer);
        m_frameCount = 0;
        m_fpsTimer = 0.0;
    }
    
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_shaderProgram == 0) {
        ErrorHandler::reportError("Renderer: programa de shader no cargado");
        return;
    }
    
    glUseProgram(m_shaderProgram);
    setupLightingUniforms();
    
    for (auto& obj : m_objects) {
        updateModelMatrix(obj);
        setupObjectUniforms(obj);
        
        glBindVertexArray(obj.mesh.vao);
        
        if (obj.mesh.indexCount > 0) {
            glDrawElements(obj.mesh.primitiveType, obj.mesh.indexCount, GL_UNSIGNED_INT, nullptr);
        } else {
            glDrawArrays(obj.mesh.primitiveType, 0, obj.mesh.indexCount);
        }
        
        glBindVertexArray(0);
    }
    
    glUseProgram(0);
}

void Renderer::cleanup() {
    if (m_shaderProgram != 0) {
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
    
    m_objects.clear();
    m_meshCache.clear();
    
    m_initialized = false;
    ErrorHandler::log("Renderer limpiado correctamente");
}

}


// === ARCHIVO: src/utils/ErrorHandler.hpp ===
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
// === ARCHIVO: src/utils/ErrorHandler.cpp ===
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


// === ARCHIVO: shaders/vertex_shader.glsl ===
#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 vFragPos;
out vec3 vNormal;
out vec2 vTexCoords;
out vec4 vFragPosLightSpace;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uLightSpaceMatrix;

void main()
{
    vFragPos = vec3(uModel * vec4(aPosition, 1.0));
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;
    vTexCoords = aTexCoords;
    vFragPosLightSpace = uLightSpaceMatrix * vec4(vFragPos, 1.0);
    gl_Position = uProjection * uView * vec4(vFragPos, 1.0);
}
// === ARCHIVO: shaders/fragment_shader.glsl ===
#version 460 core

in vec3 vFragPos;
in vec3 vNormal;
in vec2 vTexCoords;
in vec4 vFragPosLightSpace;

out vec4 FragColor;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Light uLights[4];
uniform int uNumLights;
uniform Material uMaterial;
uniform vec3 uViewPos;
uniform bool uUseShadow;
uniform sampler2D uShadowMap;
uniform vec3 uFogColor;
uniform float uFogDensity;
uniform bool uUseFog;
uniform bool uUseLighting;
uniform bool uUseTexture;

float calculateShadow(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    if (!uUseShadow) return 0.0;
    
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    
    if (projCoords.z > 1.0) return 0.0;
    
    float closestDepth = texture(uShadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float bias = max(0.005 * (1.0 - dot(normal, lightDir)), 0.0005);
    
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(1024.0, 1024.0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(uShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    return shadow;
}

vec3 calculateLightContribution(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    
    vec3 ambient = light.ambient * vec3(texture(uMaterial.diffuse, vTexCoords));
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * vec3(texture(uMaterial.diffuse, vTexCoords));
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = spec * light.specular * vec3(texture(uMaterial.specular, vTexCoords));
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    float shadowFactor = 1.0 - shadow;
    
    return (ambient + (diffuse + specular) * shadowFactor);
}

float calculateFog(float fogDistance)
{
    if (!uUseFog) return 0.0;
    float fogFactor = 1.0 - exp(-uFogDensity * fogDistance);
    return clamp(fogFactor, 0.0, 1.0);
}

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(uViewPos - vFragPos);
    
    vec3 result = vec3(0.0);
    
    if (uUseLighting) {
        float shadow = calculateShadow(vFragPosLightSpace, norm, normalize(uLights[0].position - vFragPos));
        
        for (int i = 0; i < uNumLights && i < 4; ++i) {
            result += calculateLightContribution(uLights[i], norm, vFragPos, viewDir, shadow);
        }
    } else {
        result = vec3(texture(uMaterial.diffuse, vTexCoords));
    }
    
    float fogDistance = length(vFragPos - uViewPos);
    float fogFactor = calculateFog(fogDistance);
    result = mix(result, uFogColor, fogFactor * float(uUseFog));
    
    FragColor = vec4(result, 1.0);
}
```
