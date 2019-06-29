#include <iostream>
#include "Vec3.hpp"
#include "gtest/gtest.h"

TEST(Vec3Test, Operator1) {
  Vec3 v1(1.0, 2.0, 3.0);
  Vec3 v2(4.0, 5.0, 6.0);

  EXPECT_DOUBLE_EQ(Vec3(5, 7, 9).x,  (v1 + v2).x);
  EXPECT_DOUBLE_EQ(Vec3(5, 7, 9).y,  (v1 + v2).y);
  EXPECT_DOUBLE_EQ(Vec3(5, 7, 9).z,  (v1 + v2).z);

  EXPECT_DOUBLE_EQ(-3.0,  (v1 - v2).x);
  EXPECT_DOUBLE_EQ(-3.0,  (v1 - v2).y);
  EXPECT_DOUBLE_EQ(-3.0,  (v1 - v2).z);

  EXPECT_DOUBLE_EQ(4.0,   (v1 * v2).x);
  EXPECT_DOUBLE_EQ(10.0,  (v1 * v2).y);
  EXPECT_DOUBLE_EQ(18.0,  (v1 * v2).z);

  EXPECT_DOUBLE_EQ(0.25,  (v1 / v2).x);
  EXPECT_DOUBLE_EQ(0.4,   (v1 / v2).y);
  EXPECT_DOUBLE_EQ(0.5,   (v1 / v2).z);

  EXPECT_DOUBLE_EQ(3.0,  (v1 + 2.0).x);
  EXPECT_DOUBLE_EQ(4.0,  (v1 + 2.0).y);
  EXPECT_DOUBLE_EQ(5.0,  (v1 + 2.0).z);
  
  EXPECT_DOUBLE_EQ(-1.0, (v1 - 2.0).x);
  EXPECT_DOUBLE_EQ( 0.0, (v1 - 2.0).y);
  EXPECT_DOUBLE_EQ( 1.0, (v1 - 2.0).z);
  
  EXPECT_DOUBLE_EQ(2.0,  (v1 * 2.0).x);
  EXPECT_DOUBLE_EQ(4.0,  (v1 * 2.0).y);
  EXPECT_DOUBLE_EQ(6.0,  (v1 * 2.0).z);
  
  EXPECT_DOUBLE_EQ(0.5, (v1 / 2.0).x);
  EXPECT_DOUBLE_EQ(1.0, (v1 / 2.0).y);
  EXPECT_DOUBLE_EQ(1.5, (v1 / 2.0).z);
}

TEST(Vec3Test, Operator2) {
  Vec3 v1(2.0);
  Vec3 v2(5.0);

  EXPECT_DOUBLE_EQ(Vec3(7, 7, 7).x,  (v1 + v2).x);
  EXPECT_DOUBLE_EQ(Vec3(7, 7, 7).y,  (v1 + v2).y);
  EXPECT_DOUBLE_EQ(Vec3(7, 7, 7).z,  (v1 + v2).z);

  EXPECT_DOUBLE_EQ(-3.0,  (v1 - v2).x);
  EXPECT_DOUBLE_EQ(-3.0,  (v1 - v2).y);
  EXPECT_DOUBLE_EQ(-3.0,  (v1 - v2).z);

  EXPECT_DOUBLE_EQ(10.0,   (v1 * v2).x);
  EXPECT_DOUBLE_EQ(10.0,  (v1 * v2).y);
  EXPECT_DOUBLE_EQ(10.0,  (v1 * v2).z);

  EXPECT_DOUBLE_EQ(0.4,  (v1 / v2).x);
  EXPECT_DOUBLE_EQ(0.4,   (v1 / v2).y);
  EXPECT_DOUBLE_EQ(0.4,   (v1 / v2).z);

  EXPECT_DOUBLE_EQ(4.0,  (v1 + 2.0).x);
  EXPECT_DOUBLE_EQ(4.0,  (v1 + 2.0).y);
  EXPECT_DOUBLE_EQ(4.0,  (v1 + 2.0).z);
  
  EXPECT_DOUBLE_EQ(0.0, (v1 - 2.0).x);
  EXPECT_DOUBLE_EQ(0.0, (v1 - 2.0).y);
  EXPECT_DOUBLE_EQ(0.0, (v1 - 2.0).z);
  
  EXPECT_DOUBLE_EQ(4.0,  (v1 * 2.0).x);
  EXPECT_DOUBLE_EQ(4.0,  (v1 * 2.0).y);
  EXPECT_DOUBLE_EQ(4.0,  (v1 * 2.0).z);
  
  EXPECT_DOUBLE_EQ(1.0, (v1 / 2.0).x);
  EXPECT_DOUBLE_EQ(1.0, (v1 / 2.0).y);
  EXPECT_DOUBLE_EQ(1.0, (v1 / 2.0).z);
}

auto main() -> int {
  ::testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}
