#include <vector>

#include "gtest/gtest.h"
#include "vector/vector"

namespace NanoSTL {

using std::cout;
using std::endl;

struct Base {
    virtual void print() = 0;
    virtual ~Base() = default;
};

class Foo: public Base {
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
    const int size = 666;

    // push_back(), insert()
    vector<int> vi;
    for (int i = 0; i < size; ++i) {
        vi.push_back(i);
    }

    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(i, vi[i]);
    }

    vector<Foo> vf;
    for (int i = 0; i < size; ++i) {
        Foo f(i);
        vf.push_back(f);
    }
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(i, vf[i].a_);
    }

    Foo x(999);
    vf.insert(vf.begin(), size, x);
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(999, vf[i].a_);
    }
    for (int i = size; i < size + size; ++i) {
        EXPECT_EQ(i - size, vf[i].a_);
    }

    // erase()
    vf.erase(vf.begin(), vf.begin() + size);
    EXPECT_EQ(size, static_cast<int>(vf.size()));
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(i, vf[i].a_);
    }

    // pop_back()
    vf.pop_back();
    EXPECT_EQ(size - 1, static_cast<int>(vf.size()));
    for (int i = 0; i < size - 1; ++i) {
        EXPECT_EQ(i, vf[i].a_);
    }

    // clear()
    vf.clear();
    EXPECT_EQ(0, static_cast<int>(vf.size()));
}   

}
