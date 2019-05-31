#include "queue/queue"
#include "gtest/gtest.h"

#include "iostream"

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
		// cout << "Foo:destruct a_=" << a_ << endl;
	}
	int a_;

    void print() {
        cout << a_;
    }
};

struct FooLess {
    bool operator()(const Foo& x, const Foo& y) const { return x.a_ < y.a_; }
};

TEST(QueueTest, BaseTest) {
    // default constructor
    priority_queue<int> pq1;
    EXPECT_EQ(size_t(0), pq1.size());
    EXPECT_TRUE(pq1.empty());
    pq1.push(1);
    EXPECT_EQ(1, pq1.top());

    // range
    const int size = 5;
    int ia[] = {0, 1, 2, 3, 4};
    priority_queue<int> pq2(ia, ia + size);
    EXPECT_EQ(size_t(size), pq2.size());
    for (int i = size - 1; !pq2.empty(); --i) {
        EXPECT_EQ(i, pq2.top());
        pq2.pop();
    }

    // push()
    for (int i = 0; i < 666; ++i) {
        pq2.push(i);
    }
    // pop()
    for (int i = 665; !pq2.empty(); --i) {
        EXPECT_EQ(i, pq2.top());
        pq2.pop();
    }

    // Compare defined by user
    vector<Foo> vf;
    for (int i = 0; i < size; ++i) {
        Foo f(i);
        vf.push_back(f);
    }
    FooLess less;
    priority_queue<Foo, vector<Foo>, FooLess> pqf(vf.begin(), vf.end(), less);
    EXPECT_EQ(size_t(size), pqf.size());
    for (int i = size - 1; !pqf.empty(); --i) {
        EXPECT_EQ(i, pqf.top().a_);
        pqf.pop();
    }
}

}