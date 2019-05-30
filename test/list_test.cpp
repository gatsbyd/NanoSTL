#include "list/list"
#include "gtest/gtest.h"

#include <iostream>

namespace NanoSTL {

using std::cout;
using std::endl;
class Foo {
public:
    Foo() = default;
	Foo(int a) : a_(a) {
		// cout << "Foo:construct, a=" << a_ << endl;	
	};
	Foo(const Foo &rhs) :a_(rhs.a_) {
		// cout << "Foo copy construct" << endl;
	}
	~Foo() {
		//cout << "Foo:destruct a_=" << a_ << endl;
	}
	int a_;

    void print() {
        cout << a_;
    }
};

TEST(ListTest, BaseTest) {
    // default constructor
    list<int> li1;
    EXPECT_EQ(size_t(0), li1.size());
    li1.insert(li1.cbegin(), 1);
    li1.insert(li1.cbegin(), 2);
    EXPECT_EQ(size_t(2), li1.size());

    // range constructor
    int ai[] = {1, 2, 3, 4, 5};
    list<int> li2(ai, ai+5);
    
    int i = 0;
    for (auto it = li2.begin(); it != li2.end(); ++it, ++i) {
        EXPECT_EQ(ai[i], *it);
    }

    // copy
    list<int> li3 = li2;
    EXPECT_EQ(size_t(5), li3.size());
    i = 0;
    for (auto it = li3.begin(); it != li3.end(); ++it, ++i) {
        EXPECT_EQ(ai[i], *it);
    }

    // move
    list<int> li4 = std::move(li3);
    EXPECT_EQ(size_t(5), li4.size());
    i = 0;
    for (auto it = li4.begin(); it != li4.end(); ++it, ++i) {
        EXPECT_EQ(ai[i], *it);
    }

    // operator=
    list<int> li5;
    li5 = li4;
    EXPECT_EQ(size_t(5), li5.size());
    i = 0;
    for (auto it = li5.begin(); it != li5.end(); ++it, ++i) {
        EXPECT_EQ(ai[i], *it);
    }
}

TEST(ListTest, ModifyTest) {
    const int size = 66;
    list<Foo> lf;
    // insert()
    for (int i = 0; i < size; ++i) {
        Foo f(i);
        lf.insert(lf.end(), f);
    }
    auto it = lf.begin();
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(i, (it++)->a_);
    }

    // erase()
    lf.erase(lf.begin());
    EXPECT_EQ(size_t(size - 1), lf.size());
    it = lf.begin();
    for (int i = 1; i < size; ++i) {
        EXPECT_EQ(i, (it++)->a_);
    }

    // clear()
    lf.clear();
    EXPECT_EQ(size_t(0), lf.size());

}

}
