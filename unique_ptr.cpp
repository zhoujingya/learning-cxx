#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
class A {

public:
    int a;
    string b;
    A(int a, string b) : a(a), b(b) {
        cout << "A constructor" << endl;
    }
    ~A() {
        cout << "A destructor" << endl;
    }
};

int main() {
    unique_ptr<A> a = std::make_unique<A>(1, "hello");
    unique_ptr<A> b = std::move(a);
    // cout << a->a << endl; // 会报错，因为 a 已经被移动了
    cout << b->a << endl;
    cout << b->b << endl;
    return 0;
}
