find_package(assimp REQUIRED assimp)

file(GLOB source_files CONFIGURE_DEPENDS "*.cpp")

add_library(dgrender3d ${source_files})
target_link_libraries(dgrender3d PRIVATE assimp -lGL -lGLEW)
