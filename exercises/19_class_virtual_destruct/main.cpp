#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    static int num_a;

    A() {
        ++num_a;
        std::cout << "A::num_a: " << num_a << std::endl;
    }
    // Make destructor virtual to allow proper cleanup of derived classes
    virtual ~A() {
        --num_a;
        std::cout << "A::~A: " << num_a << std::endl;
    }

    virtual char name() const {
        return 'A';
    }
};

int A::num_a = 0;
struct B final : public A {
    // TODO: 正确初始化静态字段
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() override {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};
int B::num_b = 0;
int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    // 因为创建了两个对象:
    // 1. auto a = new A; 创建了一个A对象，A::num_a++
    // 2. auto b = new B; 创建了一个B对象，由于B继承自A，也会调用A的构造函数，A::num_a++
    // 所以此时 A::num_a == 2
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    B &bb = dynamic_cast<B&>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
