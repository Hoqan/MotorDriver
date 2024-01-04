#pragma once

template<typename T>
class Filter {
public:
    Filter();
    virtual ~Filter() = default;

    virtual T calc(const T &val);
};
