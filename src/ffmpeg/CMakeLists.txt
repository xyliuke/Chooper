function(AppleSiliconLib)
    message('arm64 ffmpeg')
    include_directories(${PROJECT_SOURCE_DIR}/lib/ffmpeg/arm64/include)
    find_library(my_ffmpeg_avcodec avcodec ${PROJECT_SOURCE_DIR}/lib/ffmpeg/arm64/lib)
    find_library(my_ffmpeg_avformat avformat ${PROJECT_SOURCE_DIR}/lib/ffmpeg/arm64/lib)

endfunction()

function(AppleX64Lib)
endfunction()

if (APPLE)
    if (CMAKE_SYSTEM_PROCESSOR MATCHES arm64)
        AppleSiliconLib()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
        AppleX64Lib()
    endif ()
endif ()

aux_source_directory(. SRC)
add_library(ffmpeg_util ${SRC})
target_link_libraries(ffmpeg_util ${my_ffmpeg_avcodec} ${my_ffmpeg_avformat})