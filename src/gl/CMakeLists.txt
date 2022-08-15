function(AppleSiliconLib)
    MESSAGE(DEBUG "Apple Silicon CPU Platform")

    #GLFW
    INCLUDE_DIRECTORIES(../lib/GLFW/include)
    LINK_DIRECTORIES(../lib/GLFW/lib-arm64)

    #GLEW
    INCLUDE_DIRECTORIES(../lib/glew/include)
    LINK_DIRECTORIES(../lib/glew/lib-arm64)
endfunction()

function(AppleX64Lib)
    MESSAGE(DEBUG "Apple X86_64 CPU Platform")

    #GLFW
    INCLUDE_DIRECTORIES(../lib/GLFW/include)
    LINK_DIRECTORIES(../lib/GLFW/lib-x86_64)

    #GLEW
    INCLUDE_DIRECTORIES(../lib/glew/include)
    LINK_DIRECTORIES(../lib/glew/lib-x86_64)
endfunction()

if (APPLE)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES arm64)
        AppleSiliconLib()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
        AppleX64Lib()
    endif ()
endif ()

aux_source_directory(. SRC)
add_library(gl_util ${SRC})