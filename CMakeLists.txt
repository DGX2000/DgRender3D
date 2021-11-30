cmake_minimum_required(VERSION 3.5)

project(DgRender3D LANGUAGES CXX VERSION 0.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(doc)
add_subdirectory(lib)
add_subdirectory(demo)
