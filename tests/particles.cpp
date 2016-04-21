#include <gtest/gtest.h>

#include "particles.hpp"

using namespace Particles;

TEST(Particles, electron_is_zero) {
  EXPECT_EQ(0, (int) _e);
}

TEST(Particles, core_elements) {
  // const variable core_elements wont change
  // but placed two places to ensure brain melts
  // don't happen (this test faild at first...)
  EXPECT_EQ(0, core_elements[_e]);
  EXPECT_EQ(1, core_elements[_p]);
  EXPECT_EQ(3, core_elements[_3He]);
  EXPECT_EQ(4, core_elements[_4He]);
  EXPECT_EQ(7, core_elements[_7Li]);
  EXPECT_EQ(7, core_elements[_7Be]);
}

TEST(Particles, available_ionized_electrons) {
  EXPECT_EQ(0, available_ionized_electrons[_e]);
  EXPECT_EQ(1, available_ionized_electrons[_p]);
  EXPECT_EQ(2, available_ionized_electrons[_4He]);
  EXPECT_EQ(0, available_ionized_electrons[_7Li]);
}
