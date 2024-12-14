#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    if (i < cache.cached) {
        return cache.cache[i];
    }

    // Initialize first two numbers if not cached yet
    if (cache.cached < 2) {
        cache.cache[0] = 0;
        cache.cache[1] = 1;
        cache.cached = 2;
    }

    // Calculate and cache remaining numbers up to i
    for (int j = cache.cached; j <= i; j++) {
        cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
    }
    cache.cached = i + 1;

    return cache.cache[i];
}

int main(int argc, char **argv) {
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    FibonacciCache fib = {
        .cache = {0},// Initialize array to zeros
        .cached = 0  // No numbers cached initially
    };

    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
