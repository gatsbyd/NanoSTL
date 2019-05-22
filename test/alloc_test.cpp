#include "src/stl_alloc.h"
#include "src/stl_construct.h"
#include "gtest/gtest.h"

#include <iostream>

namespace NanoSTL {

class Foo {
public:
	Foo(int a) : a_(a) {
		std::cout << "Foo:construct" << std::endl;	
	};
	Foo(const Foo &rhs) :a_(rhs.a_) {
		std::cout << "Foo copy construct" << std::endl;
	}
	~Foo() {
		std::cout << "Foo:destruct" << std::endl;
	}
	int a_;
};

TEST(AllocTest, SampleTest) {
	Foo* pf = simple_alloc<Foo, alloc>::allocate();
	EXPECT_NE(nullptr, pf);
	
	Foo foo1(3);
	construct(pf, foo1);
	EXPECT_EQ(3, pf->a_);

	destroy(pf);

	simple_alloc<Foo, alloc>::deallocate(pf);	
}

}
