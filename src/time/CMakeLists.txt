aux_source_directory(. SRC)

function(AppleSiliconLib)
    message(DEBUG "Time Use Apple Silicon CPU Platform")

    include_directories(${PROJECT_SOURCE_DIR}/lib/boost/arm64/include)
    find_library(my-boost-thread boost_thread ${PROJECT_SOURCE_DIR}/lib/boost/arm64/lib)
    find_library(my-boost-timer boost_timer ${PROJECT_SOURCE_DIR}/lib/boost/arm64/lib)

endfunction()

function(AppleX64Lib)
    message(DEBUG "Time Apple X86_64 CPU Platform")

    include_directories(${PROJECT_SOURCE_DIR}/lib/boost/x86_64/include)
    find_library(my-boost-thread boost_thread ${PROJECT_SOURCE_DIR}/lib/boost/x86_64/lib)
    find_library(my-boost-timer boost_timer ${PROJECT_SOURCE_DIR}/lib/boost/x86_64/lib)
endfunction()

if (APPLE)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES arm64)
        AppleSiliconLib()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
        AppleX64Lib()
    endif ()
endif ()

add_library(time ${SRC})
target_link_libraries(time ${my-boost-thread})
target_link_libraries(time ${my-boost-timer})