#ifndef IGINO_StepperMotor_h
#define IGINO_StepperMotor_h

#include "Arduino.h"
#include "Stepper.h"

class IGINO_StepperMotor
{
private:
    Stepper *_stepper;

public:
    IGINO_StepperMotor(uint16_t stepsPerRevolution,
                       uint8_t motorPin1,
                       uint8_t motorPin2,
                       uint8_t motorPin3,
                       uint8_t motorPin4);
    ~IGINO_StepperMotor();
    void dispatchPill();
};

#endif