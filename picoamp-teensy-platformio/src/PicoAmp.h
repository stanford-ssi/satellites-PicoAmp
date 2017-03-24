#ifndef PICOAMP
#define PICOAMP

#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>
#include <TimerOne.h>

// Pins
const int slaveSelectPin = 10;
const int FCLK_pin = 3;
const int DRIVER_HV_EN_pin = 8;

class PicoAmp {
public:
  // Constructor
  PicoAmp(uint16_t filter_freq);

  // Methods
  void init();
  void sendCommand();
  void setCommand(uint8_t commandByte, uint8_t address);
  void setData(uint16_t data);
  void update();
  void setChannel(uint16_t channel, uint16_t val);
  void setDiff(uint8_t axis, uint32_t val);
  void enableHV();
  void disableHV();
  //void toggleFCLK();

  // Commands
  const uint8_t WRITE = 0b000;
  const uint8_t UPDATE = 0b001;
  const uint8_t WRITEUPDATEALL = 0b010;
  const uint8_t WRITEUPDATE = 0b011;
  const uint8_t POWERDAC = 0b0;
  const uint8_t RESET = 0b101;
  const uint8_t LDAC = 0b110;
  const uint8_t REFERENCE = 0b111;

  // Addresses
  const uint8_t DAC_A = 0b000; //x-
  const uint8_t DAC_B = 0b001; //x+
  const uint8_t DAC_C = 0b010; //y- (probably)
  const uint8_t DAC_D = 0b011; //y+ (probably)
  const uint8_t DAC_ALL = 0b111;

  const uint8_t X_AXIS = 1;
  const uint8_t Y_AXIS = 2;

private:

  // Buffers
  volatile uint8_t DAC_write_word[3]; // DAC input register is 24 bits, SPI writes 8 bits at a time. Need to queue up 3 bytes (24 bits) to send every time you write to it
                                      // Volatile keyword is required because this variable is (often) changed by a timer
  // State Variables
  uint8_t hv_enabled = 0;
  //volatile uint8_t FCLK_state = 0; // Volatile keyword is required because this variable is changed by a timer

  // Filter Clock
  //IntervalTimer timer_fclk;
  float f_filter;
  float fclk_period;
  const uint16_t FCLK_DUTY_50 = 512;
};

#endif
