aux_source_directory(. SRC)

function(AppleSiliconLib)
    message(DEBUG "Apple Silicon CPU Platform")

    #GLFW
    include_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/lib-arm64/GLEW)

    #GLEW
    include_directories(${PROJECT_SOURCE_DIR}/lib/glew/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/glew/lib-arm64/GLEW)
endfunction()

function(AppleX64Lib)
    message(DEBUG "Apple X86_64 CPU Platform")

    #GLFW
    include_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/lib-x86_64/glfw3)

    #GLEW
    include_directories(${PROJECT_SOURCE_DIR}/lib/glew/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/glew/lib-x86_64/glfw3)
endfunction()

if (APPLE)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES arm64)
        AppleSiliconLib()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
        AppleX64Lib()
    endif ()
endif ()

add_library(window ${SRC})

if (APPLE)
    target_link_libraries(window "-framework OpenGL")
    target_link_libraries(window "-framework CoreFoundation")
    target_link_libraries(window "-framework CoreGraphics")
    target_link_libraries(window "-framework IOKit")
    target_link_libraries(window "-framework AppKit")
    target_link_libraries(window "-framework ImageIO")
    target_link_libraries(window "-framework CoreFoundation")
endif ()