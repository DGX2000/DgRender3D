find_package(SFML 2 REQUIRED COMPONENTS system graphics window audio)
set(sfml_libs sfml-system sfml-graphics sfml-window sfml-audio)

file(GLOB source_files CONFIGURE_DEPENDS "*.cpp")

add_executable(dgrender3d_demo ${source_files})

target_include_directories(dgrender3d_demo PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(dgrender3d_demo PRIVATE dgrender3d ${sfml_libs} -lGL -lGLEW)
