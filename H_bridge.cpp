#include <H_bridge.h>

H_bridge::H_bridge()
{
}

void H_bridge::setup(uint8_t in[2], uint8_t ch[2], ledc_timer_t timer, float threshold)
{
    _in[0].setup(in[0], ch[0], timer);
    _in[1].setup(in[1], ch[1], timer);
    _b = threshold;
    _m = (100.0f - _b) / 100.0f;
}

void H_bridge::setDuty(float duty)
{
    float adj_Duty = _m * fabs(duty) + _b;

    if (duty == 0.0f)
    {
        _in[0].setDuty(0);
        _in[1].setDuty(0);
        return;
    } else if (duty < 0)
    {
        _in[0].setDuty(adj_Duty);
        _in[1].setDuty(0);
    }
    else
    {
        _in[1].setDuty(adj_Duty);
        _in[0].setDuty(0);
    }
}