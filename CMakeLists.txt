cmake_minimum_required(VERSION 3.24)
project(EmberEngine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(EMBER_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE
)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.8
    GIT_SHALLOW    TRUE
)
FetchContent_Declare(
    tinygltf
    GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
    GIT_TAG        v2.9.3
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(glfw glm)

FetchContent_GetProperties(tinygltf)
if(NOT tinygltf_POPULATED)
    FetchContent_Populate(tinygltf)
endif()

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
endif()

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw)
target_compile_definitions(imgui PUBLIC GLFW_INCLUDE_NONE)

add_library(glad STATIC
    third_party/glad/src/glad.c
)
target_include_directories(glad PUBLIC third_party/glad/include)
set_target_properties(glad PROPERTIES C_STANDARD 99)

add_executable(ember
    src/main.cpp
    src/Engine/Application.cpp
    src/Engine/Window.cpp
    src/Engine/Renderer.cpp
    src/Engine/Shader.cpp
    src/Engine/Mesh.cpp
    src/Engine/Camera.cpp
    src/Engine/File.cpp
    src/Engine/Texture.cpp
    src/Engine/Scene.cpp
    src/Engine/Ui.cpp
    src/Engine/GltfMesh.cpp
)

target_include_directories(ember PRIVATE src third_party/stb ${tinygltf_SOURCE_DIR})
target_link_libraries(ember PRIVATE glfw glad glm::glm imgui)

if(WIN32)
    target_compile_definitions(ember PRIVATE EMBER_PLATFORM_WINDOWS)
else()
    target_compile_definitions(ember PRIVATE EMBER_PLATFORM_LINUX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(ember PRIVATE OpenGL::GL)
endif()

target_compile_definitions(ember PRIVATE
    GLFW_INCLUDE_NONE
    EMBER_ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets"
)

if(MSVC)
    target_compile_options(ember PRIVATE /W4 /permissive-)
    if(EMBER_WARNINGS_AS_ERRORS)
        target_compile_options(ember PRIVATE /WX)
    endif()
else()
    target_compile_options(ember PRIVATE -Wall -Wextra -Wpedantic)
    if(EMBER_WARNINGS_AS_ERRORS)
        target_compile_options(ember PRIVATE -Werror)
    endif()
endif()

add_custom_command(TARGET ember POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ember>/assets
    COMMENT "Copying assets next to the executable"
)
