#include <gtest/gtest.h>

#include "massfractions.h"

using namespace Particles;

TEST(MassFractions, init_and_index) {
  MassFractions MF;
  MF.X  = 0.7;
  MF.Y  = 0.29;
  MF.Y3 = 1e-10;
  MF.Y4 = MF.Y - MF.Y3;
  MF.Z  = 0.01;
  MF.Z_7Li = 1e-13;
  MF.Z_7Be = 1e-13;
  MF.setFractions();

  EXPECT_EQ(0.7, MF[_p]);
  EXPECT_EQ(0.7, MF[(int) _p]);
  EXPECT_EQ(1e-13, MF[_7Li]);
}
