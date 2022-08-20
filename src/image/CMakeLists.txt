aux_source_directory(. SRC)
include_directories(../)

add_library(image ${SRC})

if (APPLE)
    # target_link_libraries(image "-framework OpenGL")
    # target_link_libraries(image "-framework CoreFoundation")
    # target_link_libraries(image "-framework IOKit")
    # target_link_libraries(image "-framework AppKit")
    target_link_libraries(image "-framework CoreGraphics")
    target_link_libraries(image "-framework ImageIO")
    target_link_libraries(image "-framework CoreFoundation")
endif ()