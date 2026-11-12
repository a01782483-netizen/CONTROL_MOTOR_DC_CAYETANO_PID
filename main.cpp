#include "definition.h"

extern "C" void app_main()
{
    //esp_task_wdt_init();
    //encoder
    encoder.setup(pins, degrees_per_edge);

    //H_bridge 
    motor.setup(in, ch, timer, threshold);
    motor.setDuty(0);

    //PID
    controler.setup(gains, dt_us * 1e-6f);

    float angulo_anterior = encoder.getAngle();
    prev_time = esp_timer_get_time();

    while (1)
    {

        current_time = esp_timer_get_time();
        if (current_time - prev_time >= dt_us)
        {
            float dt = (current_time - prev_time) * 1e-6f;
            float angulo = encoder.getAngle();
            float rpm = (angulo - angulo_anterior) / (6.0f * dt);

            const float error = obj_rpm - rpm;
            duty = controler.calculate(error);
            motor.setDuty(duty);

            angulo_anterior = angulo;

            printf("Ref: %.1f | RPM: %.1f | Error: %.1f | Comando: %.1f\n",
                   obj_rpm, rpm, controler.getError(), duty);

            prev_time = current_time;
            // //len = uart.available();

            // if (len)
            // {
            //     uart.read(message, len);
            //     sscanf(message, "%f\n", &duty);
            // }
            
            //printf("%.1f, %.2f\n", );

        }
    }
}