#ifndef STEPPER_DRIVER_4PWM_h
#define STEPPER_DRIVER_4PWM_h

#include "../common/base_classes/StepperDriver.h"
#include "../common/foc_utils.h"
#include "../common/time_utils.h"
#include "../common/defaults.h"
#include "hardware_api.h"

/**
 4 pwm stepper driver class
*/
class StepperDriver4PWM: public StepperDriver
{
  public:
    /**
      StepperMotor class constructor
      @param ph1A 1A phase pwm pin
      @param ph1B 1B phase pwm pin
      @param ph2A 2A phase pwm pin
      @param ph2B 2B phase pwm pin
      @param en1 enable pin phase 1 (optional input)
      @param en2 enable pin phase 2 (optional input)
    */
    StepperDriver4PWM(pin_size_t ph1A,pin_size_t ph1B,pin_size_t ph2A,pin_size_t ph2B, pin_size_t en1 = PIN_NOT_SET, pin_size_t en2 = PIN_NOT_SET);
    
    /**  Motor hardware init function */
  	int init() override;
    /** Motor disable function */
  	void disable() override;
    /** Motor enable function */
    void enable() override;

    // hardware variables
    pin_size_t pwm1A; //!< phase 1A pwm pin number
  	pin_size_t pwm1B; //!< phase 1B pwm pin number
  	pin_size_t pwm2A; //!< phase 2A pwm pin number
  	pin_size_t pwm2B; //!< phase 2B pwm pin number
    pin_size_t enable_pin1; //!< enable pin number phase 1
    pin_size_t enable_pin2; //!< enable pin number phase 2

    /** 
     * Set phase voltages to the harware 
     * 
     * @param Ua phase A voltage
     * @param Ub phase B voltage
    */
    void setPwm(float Ua, float Ub) override;

  private:
        
};


#endif
