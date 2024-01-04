#pragma once

template<typename T>
class IOstream {
public:
    IOstream() = default;
    virtual ~IOstream() = default;
    
    virtual void read(T data) = 0;

    virtual void write(T data) = 0;

private:

};
