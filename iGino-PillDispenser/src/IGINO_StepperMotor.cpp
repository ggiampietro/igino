#include "IGINO_StepperMotor.h"

#define MAX_STEPS 2000

IGINO_StepperMotor::IGINO_StepperMotor(uint16_t stepsPerRevolution,
                                       uint8_t motorPin1,
                                       uint8_t motorPin2,
                                       uint8_t motorPin3,
                                       uint8_t motorPin4)
{
    this->_stepper = new Stepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);
}

IGINO_StepperMotor::~IGINO_StepperMotor()
{
    free(this->_stepper);
    this->_stepper = NULL;
}

void IGINO_StepperMotor::dispatchPill()
{
    for (int i = 0; i <= 20; i++)
    {
        this->_stepper->step(1);
        delay(100);
    }
}
