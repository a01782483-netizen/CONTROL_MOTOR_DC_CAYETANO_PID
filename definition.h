#ifndef __DEFINITION_H__
#define __DEFINITION_H__

#include <esp_task_wdt.h>
#include <esp_timer.h>
#include <SimpleUART.h>
#include "H_bridge.h"
#include "QuadratureEncoder.h"
#include "PID.h"


// SimpleUART uart(115200);
H_bridge motor;
QuadratureEncoder encoder;
PID controler;

int64_t prev_time, current_time;
int64_t dt_us = 100000;

//MOTOR
uint8_t in[] = {25,26};
uint8_t ch[] = {0,1};
ledc_timer_t timer = LEDC_TIMER_0;
float threshold = 56.0f;
float duty = 0.0f;

//ENCODER
uint8_t pins[] = {32,33};
float PPR = 495.45;
float degrees_per_edge = 360/(2.0f * PPR);
float speed = 0.0f;

//PID 
float gains[] = {1.3f, 0.4f, 0.0f};
float obj_rpm = 50.0f;


// char message[];
// int len;

//State_machine



#endif // __DEFINITION_H__