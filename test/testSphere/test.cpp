#include "gtest/gtest.h"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hit.hpp"
#include "Sphere.hpp"

TEST(SphereTest, HitJudge1) {
  Sphere s(Vec3(0.0,0.0,0.0), 1.0);
  Ray ray(Vec3(0.0,0.0,-3.0), Vec3(0.0,0.0,1.0));
  Hit res;

  EXPECT_TRUE(s.intersect(ray, res));
  EXPECT_DOUBLE_EQ(0.0, res.hitPos.x);
  EXPECT_DOUBLE_EQ(0.0, res.hitPos.y);
  EXPECT_DOUBLE_EQ(-1.0, res.hitPos.z);
}

auto main() -> int {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
