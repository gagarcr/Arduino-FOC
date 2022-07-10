//TODO: #ifdef _EFM32_
#ifdef EFM32JG12B500F1024GM48
#include "../hardware_api.h"
#include "skm_output/skm_pwm.h"

#define _PWM_FREQUENCY 100000 // s25khz
#define _PWM_FREQUENCY_MAX 100000 // 50khz

static bool initialized = false;

void _writeDutyCycle1PWM(float dc_a, pin_size_t pinA);

//TODO: include in EFM32driver params
static const SKM_PWM_TypeDef PWM_MOTOR0_A =
{
 .gpioPort = SKM_MOTOR0_A_PORT,
 .gpioPin = SKM_MOTOR0_A_PIN,
 .gpioInverted = SKM_MOTOR0_A_INVERTED,                /* Enable high */
 .timer = SKM_MOTOR0_A_TIMER,
 .timerCh = SKM_MOTOR0_A_TIMER_CH,
 .timerChLoc = SKM_MOTOR0_A_TIMER_CH_LOC,
 .timerInverted = SKM_MOTOR0_A_TIMER_CH_INV            /* Channel 0 not inverted */
};


static const SKM_PWM_TypeDef PWM_MOTOR0_B =
{
 .gpioPort = SKM_MOTOR0_B_PORT,
 .gpioPin = SKM_MOTOR0_B_PIN,
 .gpioInverted = SKM_MOTOR0_B_INVERTED,                /* Enable high */
 .timer = SKM_MOTOR0_B_TIMER,
 .timerCh = SKM_MOTOR0_B_TIMER_CH,
 .timerChLoc = SKM_MOTOR0_B_TIMER_CH_LOC,
 .timerInverted = SKM_MOTOR0_B_TIMER_CH_INV            /* Channel 0 not inverted */
};


static const SKM_PWM_TypeDef PWM_MOTOR0_C =
{
 .gpioPort = SKM_MOTOR0_C_PORT,
 .gpioPin = SKM_MOTOR0_C_PIN,
 .gpioInverted = SKM_MOTOR0_C_INVERTED,                /* Enable high */
 .timer = SKM_MOTOR0_C_TIMER,
 .timerCh = SKM_MOTOR0_C_TIMER_CH,
 .timerChLoc = SKM_MOTOR0_C_TIMER_CH_LOC,
 .timerInverted = SKM_MOTOR0_C_TIMER_CH_INV            /* Channel 0 not inverted */
};


static const SKM_PWM_TypeDef PWM_MOTOR1_A =
{
 .gpioPort = SKM_MOTOR1_A_PORT,
 .gpioPin = SKM_MOTOR1_A_PIN,
 .gpioInverted = SKM_MOTOR1_A_INVERTED,                /* Enable high */
 .timer = SKM_MOTOR1_A_TIMER,
 .timerCh = SKM_MOTOR1_A_TIMER_CH,
 .timerChLoc = SKM_MOTOR1_A_TIMER_CH_LOC,
 .timerInverted = SKM_MOTOR1_A_TIMER_CH_INV            /* Channel 0 not inverted */
};


static const SKM_PWM_TypeDef PWM_MOTOR1_B =
{
 .gpioPort = SKM_MOTOR1_B_PORT,
 .gpioPin = SKM_MOTOR1_B_PIN,
 .gpioInverted = SKM_MOTOR1_B_INVERTED,                /* Enable high */
 .timer = SKM_MOTOR1_B_TIMER,
 .timerCh = SKM_MOTOR1_B_TIMER_CH,
 .timerChLoc = SKM_MOTOR1_B_TIMER_CH_LOC,
 .timerInverted = SKM_MOTOR1_B_TIMER_CH_INV            /* Channel 0 not inverted */
};


static const SKM_PWM_TypeDef PWM_MOTOR1_C =
{
 .gpioPort = SKM_MOTOR1_C_PORT,
 .gpioPin = SKM_MOTOR1_C_PIN,
 .gpioInverted = SKM_MOTOR1_C_INVERTED,                /* Enable high */
 .timer = SKM_MOTOR1_C_TIMER,
 .timerCh = SKM_MOTOR1_C_TIMER_CH,
 .timerChLoc = SKM_MOTOR1_C_TIMER_CH_LOC,
 .timerInverted = SKM_MOTOR1_C_TIMER_CH_INV            /* Channel 0 not inverted */
};

//TODO: ASSERT timerA == timerB == timerC

//  configure High PWM frequency
void _setHighFrequency(const long freq, const pin_size_t pin)
{
  if (initialized == false)
  {

    skm_pwm_init(&PWM_MOTOR0_A);
    skm_pwm_init(&PWM_MOTOR0_B);
    skm_pwm_init(&PWM_MOTOR0_C);
    skm_pwm_enableOutChannel(&PWM_MOTOR0_A, true);
    skm_pwm_enableOutChannel(&PWM_MOTOR0_B, true);
    skm_pwm_enableOutChannel(&PWM_MOTOR0_C, true);

    skm_pwm_init(&PWM_MOTOR1_A);
    skm_pwm_init(&PWM_MOTOR1_B);
    skm_pwm_init(&PWM_MOTOR1_C);
    skm_pwm_enableOutChannel(&PWM_MOTOR1_A, true);
    skm_pwm_enableOutChannel(&PWM_MOTOR1_B, true);
    skm_pwm_enableOutChannel(&PWM_MOTOR1_C, true);

    initialized = true;

    //skm_pwm_setFrequency(&PWM_MOTOR0_A, freq);
    //skm_pwm_setValue_u16(&PWM_MOTOR0_A, 65535);
    //skm_pwm_setValue_u16(&PWM_MOTOR0_B, 65535);
    //skm_pwm_setValue_u16(&PWM_MOTOR0_C, 0);

    //while(1)
    //{

    //}
  }

  _writeDutyCycle1PWM(0, pin);
  //analogWrite(pin, 0);
  skm_pwm_setFrequency(&PWM_MOTOR0_A, freq); // All share same timer, so we can allways use A.
  skm_pwm_setFrequency(&PWM_MOTOR1_A, freq); // All share same timer, so we can allways use A.

}


// function setting the high pwm frequency to the supplied pins
// - Stepper motor - 2PWM setting
// - hardware speciffic
void* _configure2PWM(long pwm_frequency, const pin_size_t pinA, const pin_size_t pinB) {
  GenericDriverParams* params = new GenericDriverParams {
    .pins = { pinA, pinB },
    .pwm_frequency = pwm_frequency,
    .dead_zone = 0
  };

  if(!pwm_frequency || !_isset(pwm_frequency) ) pwm_frequency = _PWM_FREQUENCY; // default frequency 25khz
  else pwm_frequency = _constrain(pwm_frequency, 0, _PWM_FREQUENCY_MAX); // constrain to 50kHz max

  _setHighFrequency(pwm_frequency, pinA);
  _setHighFrequency(pwm_frequency, pinB);

  return params;
}

// function setting the high pwm frequency to the supplied pins
// - BLDC motor - 3PWM setting
// - hardware speciffic
void* _configure3PWM(long pwm_frequency,const pin_size_t pinA, const pin_size_t pinB, const pin_size_t pinC) {
  GenericDriverParams* params = new GenericDriverParams {
     .pins = { pinA, pinB, pinC },
     .pwm_frequency = pwm_frequency,
     .dead_zone = 0
   };

  if(!pwm_frequency || !_isset(pwm_frequency) ) pwm_frequency = _PWM_FREQUENCY; // default frequency 25khz
  else pwm_frequency = _constrain(pwm_frequency, 0, _PWM_FREQUENCY_MAX); // constrain to 50kHz max
  _setHighFrequency(pwm_frequency, pinA);
  _setHighFrequency(pwm_frequency, pinB);
  _setHighFrequency(pwm_frequency, pinC);

  return params;
}

// function setting the high pwm frequency to the supplied pins
// - Stepper motor - 4PWM setting
// - hardware speciffic
void* _configure4PWM(long pwm_frequency,const pin_size_t pinA, const pin_size_t pinB, const pin_size_t pinC, const pin_size_t pinD) {
  GenericDriverParams* params = new GenericDriverParams {
     .pins = { pinA, pinB, pinC, pinD },
     .pwm_frequency = pwm_frequency,
     .dead_zone = 0
  };

  if(!pwm_frequency || !_isset(pwm_frequency) ) pwm_frequency = _PWM_FREQUENCY; // default frequency 25khz
  else pwm_frequency = _constrain(pwm_frequency, 0, _PWM_FREQUENCY_MAX); // constrain to 50kHz max
  _setHighFrequency(pwm_frequency, pinA);
  _setHighFrequency(pwm_frequency, pinB);
  _setHighFrequency(pwm_frequency, pinC);
  _setHighFrequency(pwm_frequency, pinD);

  return params;
}

bool findPWMfromPin(pin_size_t pin, const SKM_PWM_TypeDef ** pwm)
{
  if ((pin.port == PWM_MOTOR0_A.gpioPort) && (pin.pin == PWM_MOTOR0_A.gpioPin))
  {
    *pwm = &PWM_MOTOR0_A;
    return true;
  }
  else if ((pin.port == PWM_MOTOR0_B.gpioPort) && (pin.pin == PWM_MOTOR0_B.gpioPin))
  {
    *pwm = &PWM_MOTOR0_B;
    return true;
  }
  else if ((pin.port == PWM_MOTOR0_C.gpioPort) && (pin.pin == PWM_MOTOR0_C.gpioPin))
  {
    *pwm = &PWM_MOTOR0_C;
    return true;
  }
  else if ((pin.port == PWM_MOTOR1_A.gpioPort) && (pin.pin == PWM_MOTOR1_A.gpioPin))
  {
    *pwm = &PWM_MOTOR1_A;
    return true;
  }
  else if ((pin.port == PWM_MOTOR1_B.gpioPort) && (pin.pin == PWM_MOTOR1_B.gpioPin))
  {
    *pwm = &PWM_MOTOR1_B;
    return true;
  }
  else if ((pin.port == PWM_MOTOR1_C.gpioPort) && (pin.pin == PWM_MOTOR1_C.gpioPin))
  {
    *pwm = &PWM_MOTOR1_C;
    return true;
  }

  return false;
}

void _writeDutyCycle1PWM(float dc_a, pin_size_t pinA)
{
  const SKM_PWM_TypeDef * pinA_pwm;

  if (findPWMfromPin(pinA, &pinA_pwm) == false)
 {
   EFM_ASSERT(0);
   return;
 }
   // transform duty cycle from [0,1] to [0,65535]
 skm_pwm_setValue_u16(pinA_pwm, 65535.0f*dc_a);
}


// function setting the pwm duty cycle to the hardware
// - Stepper motor - 2PWM setting
// - hardware specific
void _writeDutyCycle2PWM(float dc_a,  float dc_b, void* params){
  const SKM_PWM_TypeDef * pinA_pwm, * pinB_pwm;
  GenericDriverParams const * p = (GenericDriverParams*)params;

  if ((findPWMfromPin(p->pins[0], &pinA_pwm) && findPWMfromPin(p->pins[1], &pinB_pwm) ) == false)
  {
    EFM_ASSERT(0);
    return;
  }
  // transform duty cycle from [0,1] to [0,65535]
  skm_pwm_setValue_u16(pinA_pwm, 65535.0f*dc_a);
  skm_pwm_setValue_u16(pinB_pwm, 65535.0f*dc_b);

  //analogWrite(pinA, 255.0f*dc_a);
  //analogWrite(pinB, 255.0f*dc_b);
}
// function setting the pwm duty cycle to the hardware
// - BLDC motor - 3PWM setting
// - hardware speciffic
void _writeDutyCycle3PWM(float dc_a,  float dc_b, float dc_c, void* params){
   const SKM_PWM_TypeDef * pinA_pwm, * pinB_pwm, * pinC_pwm;
   GenericDriverParams const * p = (GenericDriverParams*)params;

   if ((findPWMfromPin(p->pins[0], &pinA_pwm) && findPWMfromPin(p->pins[1], &pinB_pwm) && findPWMfromPin(p->pins[2], &pinC_pwm) ) == false)
   {
     EFM_ASSERT(0);
     return;
   }
   // transform duty cycle from [0,1] to [0,65535]
   skm_pwm_setValue_u16(pinA_pwm, 65535.0f*dc_a);
   skm_pwm_setValue_u16(pinB_pwm, 65535.0f*dc_b);
   skm_pwm_setValue_u16(pinC_pwm, 65535.0f*dc_c);
}

// function setting the pwm duty cycle to the hardware
// - Stepper motor - 4PWM setting
// - hardware specific
void _writeDutyCycle4PWM(float dc_1a,  float dc_1b, float dc_2a, float dc_2b, void* params){
  // transform duty cycle from [0,1] to [0,255]
  EFM_ASSERT(0); //TODO
  GenericDriverParams const * p = (GenericDriverParams*)params;
  UNUSED(*p);
  UNUSED(dc_1a); UNUSED(dc_1b); UNUSED(dc_2a); UNUSED(dc_2b);
  //analogWrite(pin1A, 255.0f*dc_1a);
  //analogWrite(pin1B, 255.0f*dc_1b);
  //analogWrite(pin2A, 255.0f*dc_2a);
  //analogWrite(pin2B, 255.0f*dc_2b);
}

#endif
