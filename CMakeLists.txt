add_library(
  st_stream STATIC
  src/st_stream.cxx
  src/Stream.cxx
  src/StreamFormatter.cxx
)

target_include_directories(
  st_stream PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>
)

add_executable(test_st_stream src/test/test_st_stream.cxx)
target_link_libraries(test_st_stream PRIVATE st_stream)
