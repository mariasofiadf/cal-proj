//
// Created by pedro on 08/04/21.
//

#include <gtest/gtest.h>
#include "../src/Position.h"

TEST(Position, distance) {
    Position p1(0,0);
    Position p2(2,0);
    Position p3(1,1);
    EXPECT_EQ(p1.distance(p2),2);
    EXPECT_EQ(p1.distance(p3), sqrt(2));
}