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