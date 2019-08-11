cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(MyPhotorealism)

set( CMAKE_BUILD_TYPE Release )

IF (!APPLE)
  set(CMAKE_CXX_COMPILER g++)
ELSE()
  set(CMAKE_MACOSX_RPATH 1) # This is needed in macOS
ENDIF()


set( CMAKE_CXX_FLAGS "-std=c++17 -O3 -mtune=native -march=native" )
find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

enable_testing()

add_executable(
  main
  main.cc
)

add_executable(
  pinhole_main
  pinhole_main.cc
)

add_executable(
  pinhole_sphere_main
  pinhole_sphere_main.cc
)

add_executable(
  aggregate_main
  aggregate_main.cc
)

add_executable(
  shadow_main
  shadow_main.cc
)

add_executable(
  path_tracing
  path_tracing.cc
)

add_executable(
  path_tracing_diffuse
  path_tracing_diffuse.cc
)

add_executable(
  path_tracing_mirror
  path_tracing_mirror.cc
)

add_executable(
  cornell_box 
  cornell_box.cc
)

add_subdirectory(test)
