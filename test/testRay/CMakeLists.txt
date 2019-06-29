file(GLOB SRCS *.cpp)

add_executable(
  testRay
  ${SRCS}
)

# message("test" ${binary_dir})

link_directories(
  ${binary_dir}/googlemock/gtest/lib
)

target_link_libraries(
  testRay
  libgtest
  libgmock
)

add_test(
  NAME testRay
  COMMAND testRay
)
