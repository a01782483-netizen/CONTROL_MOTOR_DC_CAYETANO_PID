#ifndef __H_BRIDGE_H__
#define __H_BRIDGE_H__

#include "SimplePWM.h"
#include <math.h>

class H_bridge
{

public:
    H_bridge();
    // pines direccion y pwm, canales de mi PWM, Timer, duty cycle a partir del cual nuestro motor se enciende
    void setup(uint8_t in[2], uint8_t ch[2], ledc_timer_t timer, float threshold = 0.0f);
    void setDuty(float duty);

private:
    SimplePWM _in[2];
    float _m, _b;
};

#endif // __H_BRIDGE_H__