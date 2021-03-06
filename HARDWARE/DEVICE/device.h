#ifndef _DEVICE_H_
#define _DEVICE_H_
#include "PWM_apply.h"

void LED_Laser_Driver(float led,float laser);
void LED_Laser_Init(void);
void MainEngine_Driver(float speed_L, float speed_R);
void MainEngine_Init(void);
void SteeringEngine_Driver(float pitch,float dir);
void SteeringEngine_Init(void);
extern Obj_PWMInit SteeringEngineCtrl;
extern Obj_PWMInit MainEngineCtrl;
extern Obj_PWMInit LED_Laser_Ctrl;
#endif
