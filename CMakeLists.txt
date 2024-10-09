cmake_minimum_required(VERSION 3.26)
project(phys-lab-3)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)

# Fetch GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# Fetch ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        v1.90.4
)
FetchContent_GetProperties(imgui)

# Fetch ImPlot
FetchContent_Declare(
        implot
        GIT_REPOSITORY https://github.com/epezent/implot.git
        GIT_TAG        v0.16
)
FetchContent_MakeAvailable(implot)

if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
    file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h)
    if(NOT TARGET imgui)
        add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
        target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
    endif()
endif()

# Fetch nlohmann/json
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Setup ImGui with GLFW and OpenGL3
target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
target_sources(imgui INTERFACE
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
add_subdirectory(lib)
add_executable(phys-lab-3
        src/main.cpp
        src/window.h
        src/window.cpp
        src/utilityFuncs.hpp
        src/measureList.h
        src/measureList.cpp
        src/textManager.h
        src/textManager.cpp
        lib/implot/implot.h
        lib/implot/implot.cpp
        lib/implot/implot_internal.h
        lib/implot/implot_items.cpp)
target_link_libraries(phys-lab-3 PUBLIC nlohmann_json::nlohmann_json imgui OpenGL::GL glfw)