#include <vector>

#include "gtest/gtest.h"
#include "src/vector"

namespace NanoSTL {


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
        using std::cout;
        using std::endl;
		cout << "Foo:destruct a_=" << a_ << endl;
	}
	int a_;

    void func() {
        using std::cout;
using std::endl;
        cout << a_;
    }
};

TEST(VectorTest, Test1) {
    vector<int> vi();
}

}
