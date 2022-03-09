#include "../hardware_api.h" 

#if defined(__arm__) && defined(CORE_TEENSY)

#define _ADC_VOLTAGE 3.3f
#define _ADC_RESOLUTION 1024.0f

// function reading an ADC value and returning the read voltage
void* _configureADCInline(const void* driver_params, const pin_size_t pinA,const pin_size_t pinB,const pin_size_t pinC){
  _UNUSED(driver_params);

  if( _ispinset(pinA) ) pinMode(pinA, INPUT);
  if( _ispinset(pinB) ) pinMode(pinB, INPUT);
  if( _ispinset(pinC) ) pinMode(pinC, INPUT);

  GenericCurrentSenseParams* params = new GenericCurrentSenseParams {
    .pins = { pinA, pinB, pinC },
    .adc_voltage_conv = (_ADC_VOLTAGE)/(_ADC_RESOLUTION)
  };

  return params;
}

#endif