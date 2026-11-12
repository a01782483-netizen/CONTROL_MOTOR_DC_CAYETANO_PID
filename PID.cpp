#include "PID.h"

PID::PID()
{
}

void PID::setup(float gains[3], float dt)
{
    _kp = gains[0];
    _ki = gains[1];
    _kd = gains[2];
    _dt = dt;
}

float PID::calculate(float error)
{
    float max_duty = 100.0f;
    float min_duty = 0.0f;

    float p = _kp * error; // integral term = y[n] = y[n-1] +(dt/2)(e[n]+e[n-1])
    float i = _ki * _integral;
    float d = _kd * (error - _prev_error) / _dt;

    //antiwindup
    float d_integral = _dt * (error + _prev_error) / 2.0f;
    float d_i = _ki * d_integral;

    float u = p + i + d;

    float u_test = u + d_i;

    if ((u_test >= min_duty && u_test <= max_duty) ||
        (u_test > max_duty && d_i < 0.0f) ||
        (u_test < min_duty && d_i > 0.0f))
    {
        _integral += d_integral;
        u = u_test;
    }

    if (u <= min_duty)
    {
        u = min_duty;
    }
    else if (u >= max_duty)
    {
        u = max_duty;
    }

    _prev_error = error;
    return u;
}

float PID::getError()
{
    return _prev_error;
}
