#pragma once


template<typename T>
class Pid {
public:
    Pid();
    virtual ~Pid() = default;

    T calc(T ref, T feedback);
private:
    float Ts_;
    T kp_;
    T ki_;
    T kd_;
    T last_error_;
    T error_sum_;
    T output_;
    T int_lmt_;
    T output_lmt_;
};

template<typename T>
T Pid<T>::calc(T ref, T feedback) {
    T error = ref - feedback;
    error_sum_ += last_error_;
    T inter = ki_ * error_sum_ * Ts_;
    output_ = kp_ * error_ + ki_ * error_sum * Ts_ + kd_ * (error - last_error) / Ts_;

    if (inter > int_lmt_) {
        inter = int_lmt_;
    } else if (inter < -int_lmt_) {
        inter = -int_lmt_;
    }

    if (output_ > output_lmt_)
        output_ = output_lmt_;
    else if (output_ < -output_lmt_) {
        output_ = -output_lmt_;
    }
}


