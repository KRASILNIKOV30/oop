#include <string>
#include <compare>

template <class T>
T max(T a, T b)
{
    return a > b ? a : b;
}

template <class T>
T Foo()
{
    return T();
}

template <>
const char* max(const char* a, const char* b)
{
    return strcmp(a, b) == 1 ? a : b;
}

template <class T, class U>
T F(T a, U b)
{
    return T();
}

template <class U>
int F(int a, U b)
{
    return 0;
}

std::strong_ordering R(int a, int b)
{
    return a <=> b;
}