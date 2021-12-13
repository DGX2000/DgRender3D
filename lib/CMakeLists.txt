find_package(SFML 2 REQUIRED COMPONENTS system graphics window)
set(sfml_libs sfml-system sfml-graphics sfml-window)

file(GLOB source_files CONFIGURE_DEPENDS "*.cpp")

add_library(dgrender3d ${source_files})
target_link_libraries(dgrender3d PRIVATE ${sfml_libs} -lGL -lGLEW)
