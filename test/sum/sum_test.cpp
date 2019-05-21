#include "src/sum/sum.h"
#include "gtest/gtest.h"

TEST(SumTest, Test1) {
	EXPECT_EQ(4, sum(1, 2));
}
