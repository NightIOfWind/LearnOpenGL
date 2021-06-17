
cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
include(CTest)
enable_testing()

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(demo main.cpp glad.c Shader.cpp stb_image.h src/SOIL.h)

target_link_libraries(${PROJECT_NAME} libglfw.dylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
