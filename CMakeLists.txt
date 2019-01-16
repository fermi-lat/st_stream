cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
project(ST_Stream
  VERSION 0.0.0
  LANGUAGES CXX
  )

add_library(st_stream STATIC
  src/Stream.cxx
  src/StreamFormatter.cxx
  src/st_stream.cxx
)
add_library(ST::stream ALIAS st_stream)

target_include_directories(st_stream
  PUBLIC
    $<INSTALL_INTERFACE:st_stream/>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(test_st_stream src/test/test_st_stream)
target_link_libraries(test_st_stream PRIVATE ST::stream)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/st_stream)

install(DIRECTORY st_stream/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/st_stream)

install(TARGETS st_stream
  EXPORT st_streamTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

install(EXPORT st_streamTargets
  NAMESPACE    ST::
  DESTINATION  ${INSTALL_CONFIGDIR}
  )

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/st_streamConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/st_streamConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/st_streamConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/st_streamConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/st_streamConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT st_streamTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/st_streamTargets.cmake
  NAMESPACE ST::
)

#Register package in user's package registry
export(PACKAGE st_stream)
