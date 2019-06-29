file(GLOB SRCS *.cpp)

add_executable(
  testSphere
  ${SRCS}
)

message("test" ${binary_dir})


link_directories(
  ${binary_dir}/googlemock/gtest/lib
)

target_link_libraries(
  testSphere
  libgtest
  libgmock
)

add_test(
  NAME testSphere
  COMMAND testSphere
)
