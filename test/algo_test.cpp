#include "src/stl_algobase.h"
#include "gtest/gtest.h"

namespace NanoSTL {

TEST(AlgoTest, BaseTest) {
    const int size = 5;
    int ia1[] = {1, 2, 3, 4, 5};
    int ia2[size];
    copy(ia1, ia1 + size, ia2);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(ia1[i], ia2[i]);
    }
}

}