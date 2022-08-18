cmake_minimum_required(VERSION 3.10)
project(Usopp)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src/file)
add_subdirectory(src/gl)
add_subdirectory(src/window)
add_subdirectory(test)

include_directories(./src/)

function(AppleSiliconLib)
    message(DEBUG "Apple Silicon CPU Platform")

    #GLFW
    include_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/lib-arm64)

    #GLEW
    include_directories(${PROJECT_SOURCE_DIR}/lib/glew/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/glew/lib-arm64)
endfunction()

function(AppleX64Lib)
    message(DEBUG "Apple X86_64 CPU Platform")

    #GLFW
    include_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/lib-x86_64)

    #GLEW
    include_directories(${PROJECT_SOURCE_DIR}/lib/glew/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/glew/lib-x86_64)
endfunction()

if (APPLE)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES arm64)
        AppleSiliconLib()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
        AppleX64Lib()
    endif ()
endif ()

add_executable(Usopp main.cpp)
target_link_libraries(Usopp file_util)
target_link_libraries(Usopp gl_util)
target_link_libraries(Usopp window)
target_link_libraries(Usopp GLEW)
target_link_libraries(Usopp glfw3)

# if (APPLE)
#     TARGET_LINK_LIBRARIES(Usopp "-framework OpenGL")
#     TARGET_LINK_LIBRARIES(Usopp "-framework CoreFoundation")
#     TARGET_LINK_LIBRARIES(Usopp "-framework CoreGraphics")
#     TARGET_LINK_LIBRARIES(Usopp "-framework IOKit")
#     TARGET_LINK_LIBRARIES(Usopp "-framework AppKit")
#     TARGET_LINK_LIBRARIES(Usopp "-framework ImageIO")
#     TARGET_LINK_LIBRARIES(Usopp "-framework CoreFoundation")
# endif ()