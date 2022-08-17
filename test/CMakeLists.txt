# find_package(Catch2 3 REQUIRED)

Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

include_directories(${PROJECT_SOURCE_DIR}/src)
aux_source_directory(. SRC)
add_executable(tests ${SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE file_util)