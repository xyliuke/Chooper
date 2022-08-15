cmake_minimum_required(VERSION 3.10)
project(Chooper)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

add_subdirectory(src/file)
add_subdirectory(src/gl)

add_executable(Chooper main.cpp)
target_link_libraries(Chooper file_util)
target_link_libraries(Chooper gl_util)