#include <functional>

struct SingletonTester {
    template <typename T>
    bool is_singleton(std::function<T* ()> factory) {
        T* a = factory();
        T* b = factory();
        return a == b;
    }
};