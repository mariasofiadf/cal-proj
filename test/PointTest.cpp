//
// Created by pedro on 08/04/21.
//

#include <gtest/gtest.h>
#include "../src/Point.h"

TEST(Point, equality) {
    Point p1(0, 0, "p1");
    Point p2(2, 0, "p1");
    EXPECT_EQ(p1 == p1, true);
    EXPECT_EQ(p1 == p2, false);
}