#include <gtest/gtest.h>

#include "reaction_energies.h"
#include "particles.h"

using namespace Particles;
using namespace ReactionEnergies;

TEST(Reaction_energies, Q_indexes) {
  EXPECT_EQ(Q_pp, Q[_p][_p]);
  EXPECT_EQ(Q_33, Q[_3He][_3He]);
  EXPECT_EQ(Q_34, Q[_3He][_4He]);
  EXPECT_EQ(Q_e7Be, Q[_e][_7Be]);
  EXPECT_EQ(Q_p7Li, Q[_p][_7Li]);
  EXPECT_EQ(0, Q[_3He][_7Li]);
  EXPECT_EQ(0, Q[_7Be][_e]);
}

TEST(Reaction_energies, Q_values) {
  double eps = 1e-4;
  EXPECT_NEAR(1.06705e-12, Q_pp, Q_pp*eps);
  EXPECT_NEAR(2.0603991e-12, Q_33, Q_33*eps);
  EXPECT_NEAR(2.547461e-13, Q_34, Q_34*eps);
  EXPECT_NEAR(8.01088e-15, Q_e7Be, Q_e7Be*eps);
  EXPECT_NEAR(2.779776e-12, Q_p7Li, Q_p7Li*eps);
}
