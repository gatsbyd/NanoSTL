#include <iostream>

using namespace std;

class Base
{
public:
    int m_iNum = 1;
    virtual void foo() {
        cout << "base foo()" << endl;
    };
};

class Derived:public Base
{
public:
    char *m_szName[100];
    virtual void foo() {
        cout << "derived foo()" << endl;
    };
};


int main()
{
    Base *pb = new Base();
    Derived *pd = new Derived();
	const int b = 10;
	int *pc = const_cast<int *>(&b);
	*pc = 11;
	cout << *pc << endl;
	cout << b << endl;

    pd = static_cast<Derived *>(pb);
    if (pd) {
        cout << "pd is not null" << endl;
    } else {
        cout << "pd is null" << endl;
    }

    return 0;
}

