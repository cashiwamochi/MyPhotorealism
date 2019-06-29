#include <iostream>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "gtest/gtest.h"

TEST(RayTest, Operator) {
  Ray r(Vec3(1.0,1.0,1.0), Vec3(0.0,0.0,1.0));

  EXPECT_DOUBLE_EQ(r.origin.x, 1.0); 
  EXPECT_DOUBLE_EQ(r.origin.y, 1.0); 
  EXPECT_DOUBLE_EQ(r.origin.z, 1.0); 

  EXPECT_DOUBLE_EQ(r.direction.x, 0.0); 
  EXPECT_DOUBLE_EQ(r.direction.y, 0.0); 
  EXPECT_DOUBLE_EQ(r.direction.z, 1.0); 

  EXPECT_DOUBLE_EQ(r(10).x, 1.0); 
  EXPECT_DOUBLE_EQ(r(10).y, 1.0); 
  EXPECT_DOUBLE_EQ(r(10).z, 11.0); 
}


auto main() -> int {
  ::testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}
