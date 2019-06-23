cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(MyPhotorealism)

set( CMAKE_BUILD_TYPE Debug )

IF (!APPLE)
  set(CMAKE_CXX_COMPILER g++)
ELSE()
  set(CMAKE_MACOSX_RPATH 1) # This is needed in macOS
ENDIF()

set( CMAKE_CXX_FLAGS "-std=c++17" )

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

add_executable(
  main
  main.cc
)

