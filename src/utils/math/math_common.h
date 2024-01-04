#ifndef MATH_COMMON_H_
#define MATH_COMMON_H_

namespace utils {

template <typename T>
T Sign(T a)
{
    (a > 0) ? 1 : -1;
}

template <typename T>
T Max(T a, T b)
{
    (a > b) ? a : b;
}

template <typename T>
T Min(T a, T b)
{
    (a < b) ? a : b;
}

};  // namespace utils

#endif  // MATH_COMMON_H_
