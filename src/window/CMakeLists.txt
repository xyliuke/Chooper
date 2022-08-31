aux_source_directory(. SRC)
include_directories(../)

function(AppleSiliconLib)
    message(DEBUG "Apple Silicon CPU Platform")

    #GLFW
    find_library(my_glfw glfw3 ${PROJECT_SOURCE_DIR}/lib/GLFW/lib-arm64/)

    #GLEW
    find_library(my_glew GLEW ${PROJECT_SOURCE_DIR}/lib/glew/lib-arm64/)
endfunction()

include_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/glew/include)

function(AppleX64Lib)
    message(DEBUG "Apple X86_64 CPU Platform")

    #GLFW
    find_library(my_glfw glfw3 ${PROJECT_SOURCE_DIR}/lib/GLFW/lib-x86_64/)

    #GLEW
    find_library(my_glew GLEW ${PROJECT_SOURCE_DIR}/lib/glew/lib-x86_64/)
endfunction()

if (APPLE)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES arm64)
        AppleSiliconLib()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
        AppleX64Lib()
    endif ()
endif ()

add_library(window ${SRC})
target_link_libraries(window ${my_glew})
target_link_libraries(window ${my_glfw})

if (APPLE)
    target_link_libraries(window "-framework OpenGL")
    target_link_libraries(window "-framework CoreFoundation")
    target_link_libraries(window "-framework CoreGraphics")
    target_link_libraries(window "-framework IOKit")
    target_link_libraries(window "-framework AppKit")
    target_link_libraries(window "-framework ImageIO")
    target_link_libraries(window "-framework CoreFoundation")
endif ()