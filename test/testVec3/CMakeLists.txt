file(GLOB SRCS *.cpp)

add_executable(
  testVec3
  ${SRCS}
)

message("test" ${binary_dir})


link_directories(
  ${binary_dir}/googlemock/gtest/lib
)

target_link_libraries(
  testVec3
  libgtest
  libgmock
)

add_test(
  NAME testVec3
  COMMAND testVec3
)
