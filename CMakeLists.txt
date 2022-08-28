cmake_minimum_required(VERSION 3.10)
project(Usopp)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src/file)
add_subdirectory(src/gl)
add_subdirectory(src/window)
add_subdirectory(src/image)
add_subdirectory(src/player)
add_subdirectory(test)

include_directories(./src/)

add_executable(Usopp main.cpp)
target_link_libraries(Usopp file_util)
target_link_libraries(Usopp gl_util)
target_link_libraries(Usopp window)
target_link_libraries(Usopp image)