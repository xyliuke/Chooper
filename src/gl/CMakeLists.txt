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
include_directories(../)
aux_source_directory(. SRC)
add_library(gl_util ${SRC})