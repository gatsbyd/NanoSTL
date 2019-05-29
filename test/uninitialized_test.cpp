#include "base/stl_alloc.h"
#include "base/stl_uninitialized.h"
#include "gtest/gtest.h"

#include <vector>

namespace NanoSTL {

struct Foo {
	Foo(int a) :a_(a) {}
	int a_;
};


TEST(UninitializedTest, BaseTest) {
	const int size = 5;

	int ia1[size] = {1, 2, 3, 4, 5};
	int *ip1 = simple_alloc<int, alloc>::allocate(size);
	uninitialized_copy(ia1, ia1+size, ip1);
	for (int i = 0; i < size; i++) {
		EXPECT_EQ(ia1[i], ip1[i]);
	}

	int *ip2 = simple_alloc<int, alloc>::allocate(size);
	uninitialized_fill(ip2, ip2+size, 100);
	for (int i = 0; i < size; i++) {
		EXPECT_EQ(100, ip2[i]);
	}

	int *ip3 = simple_alloc<int, alloc>::allocate(size);
	uninitialized_fill_n(ip3, size, 100);
	for (int i = 0; i < size; i++) {
		EXPECT_EQ(100, ip3[i]);
	}

	std::vector<Foo> vf = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5)};
	Foo *fp = simple_alloc<Foo, alloc>::allocate(size);
	NanoSTL::uninitialized_copy(vf.begin(), vf.end(), fp); //ADL.https://stackoverflow.com/questions/8111677/what-is-argument-dependent-lookup-aka-adl-or-koenig-lookup
	for (int i = 0; i < size; i++) {
		EXPECT_EQ(vf[i].a_, fp[i].a_);
	}


	//destroy
}

}


