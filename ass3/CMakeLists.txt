cmake_minimum_required(VERSION 3.12)

project("COMP3421 Assignment 3")

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# If I was better at CMake I would make this nicer
if (NOT (EXISTS ${PROJECT_SOURCE_DIR}/lib))
    message(FATAL_ERROR "Dependencies not found. Please run fetch_deps.sh [-G Ninja] from the project root and reconfigure")
endif ()

find_package(glad REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib)
find_package(glfw3 REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib)
find_package(glm REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib)
find_package(stb REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib)
find_package(tinyobjloader REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib)
find_package(chicken3421 REQUIRED HINTS ${PROJECT_SOURCE_DIR}/lib)

set(COMMON_LIBS glad::glad glm::glm glfw stb tinyobjloader::tinyobjloader chicken3421)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(copy_resources)
copy_resources(${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)

set(ACTIVITY ass3)
add_executable(${ACTIVITY})
target_include_directories(${ACTIVITY} PUBLIC include)
target_sources(${ACTIVITY}
        ${target}
        PRIVATE
        include/ass3/texture_2d.hpp
        include/ass3/shapes.hpp
        include/ass3/euler_camera.hpp
        include/ass3/memes.hpp
        include/ass3/mesh.hpp
        include/ass3/model.hpp
        include/ass3/scene.hpp
        include/ass3/renderer.hpp
        include/ass3/cubemap.hpp
        include/ass3/framebuffer.hpp

        src/main.cpp
        src/texture_2d.cpp
        src/shapes.cpp
        src/euler_camera.cpp
        src/memes.cpp
        src/mesh.cpp
        src/model.cpp
        src/renderer.cpp
        src/scene.cpp
        src/cubemap.cpp
        src/framebuffer.cpp
        )
target_link_libraries(${ACTIVITY} PUBLIC ${COMMON_LIBS})
target_compile_options(
        ${ACTIVITY}
        PRIVATE
        -Wall -Wextra -pedantic -fvisibility=hidden -fdiagnostics-color=always -Wcast-align
        -Wconversion -Wdouble-promotion -Wshadow -Wsign-conversion -Wsign-promo -Wnull-dereference -Wodr
)