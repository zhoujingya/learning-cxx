#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // std::vector<bool>的operator[]返回一个代理对象(proxy object)而不是bool&
        // 这个代理对象可以修改底层的bool值
        // 所以当我们通过ref修改值为false时,实际上修改了vec[30]的值
        auto ref = vec[30];  // ref是代理对象,此时vec[30]为true
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;  // 通过代理对象修改vec[30]的值为false
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // vec[30]已经被修改为false
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}
