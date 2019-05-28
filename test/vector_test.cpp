#include <vector>

#include "gtest/gtest.h"
#include "src/vector"

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
		cout << "Foo:destruct a_=" << a_ << endl;
	}
	int a_;

    void func() {
        cout << a_;
    }
};

TEST(VectorTest, CopyControlTest) {
    const size_t size = 6;

    //vector()
    vector<int> vi1();

    // //vector(size_type n, const value_type& value)
    Foo f(1);
    vector<Foo> vf1(size, f);
    vector<int> vi2(size, 666);
    EXPECT_EQ(size, vf1.size());
    EXPECT_EQ(size, vi2.size());

    //vector(const vector<value_type, Alloc>& rhs)
    vector<Foo> vf2(vf1);
    EXPECT_EQ(size, vf2.size());

    //vector(vector<value_type, Alloc>&& rhs)
    vector<Foo> vf3(std::move(vf1));
    EXPECT_EQ(size, vf3.size());

    //operator=
    vector<Foo> vf4;
    vf4 = vf3;
    EXPECT_EQ(size, vf4.size());

    vector<Foo> vf5;
    vf5 = std::move(vf3);
    EXPECT_EQ(size, vf5.size());
}

TEST(VectorTest, ModifyTest) {
    const size_t size = 666;
    vector<int> vi;
    for (size_t i = 0; i < size; ++i) {
        vi.push_back(i);
    }


}

}
