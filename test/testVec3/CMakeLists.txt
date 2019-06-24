file(GLOB SRCS *.cpp)

add_executable(
  testVec3
  ${SRCS}
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
