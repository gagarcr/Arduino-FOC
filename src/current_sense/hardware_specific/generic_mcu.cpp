#include "../hardware_api.h"
#include "api/Common.h"
#include "common/foc_utils.h"

// function reading an ADC value and returning the read voltage
__attribute__((weak))  float _readADCVoltageInline(const pin_size_t pinA, const void* cs_params){
  uint32_t raw_adc = analogRead(pinA);
  return raw_adc * ((GenericCurrentSenseParams*)cs_params)->adc_voltage_conv;
}

// function reading an ADC value and returning the read voltage
__attribute__((weak))  void* _configureADCInline(const void* driver_params, const pin_size_t pinA,const pin_size_t pinB,const pin_size_t pinC){
  _UNUSED(driver_params);

  if( _ispinset(pinA) ) pinMode(pinA, INPUT);
  if( _ispinset(pinB) ) pinMode(pinB, INPUT);
  if( _ispinset(pinC) ) pinMode(pinC, INPUT);

  GenericCurrentSenseParams* params = new GenericCurrentSenseParams {
    .pins = { pinA, pinB, pinC },
    .adc_voltage_conv = (5.0f)/(1024.0f)
  };

  return params;
}

// function reading an ADC value and returning the read voltage
__attribute__((weak))  float _readADCVoltageLowSide(const pin_size_t pinA, const void* cs_params){
  return _readADCVoltageInline(pinA, cs_params);
}

// Configure low side for generic mcu
// cannot do much but 
__attribute__((weak))  void* _configureADCLowSide(const void* driver_params, const pin_size_t pinA,const pin_size_t pinB,const pin_size_t pinC){
  return _configureADCInline(driver_params, pinA, pinB, pinC);
}

// sync driver and the adc
__attribute__((weak)) void _driverSyncLowSide(void* driver_params, void* cs_params){
  _UNUSED(driver_params);
  _UNUSED(cs_params); 
}
__attribute__((weak)) void _startADC3PinConversionLowSide(){ }
