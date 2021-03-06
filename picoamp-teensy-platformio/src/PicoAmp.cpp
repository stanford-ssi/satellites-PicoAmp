#include "PicoAmp.h"

PicoAmp::PicoAmp(uint16_t filter_freq = 1000){
    f_filter = (float)filter_freq;
    fclk_period = 1000000.0/(f_filter * 60.0);  // = 1000000us /(1kHz * 60) - drives filter clock at 60kHz to create 1kHz filter
}

void PicoAmp::init(){
  // initialize SPI:
  SPI.begin();

  // Setup Pins:
  pinMode (slaveSelectPin, OUTPUT); // SPI SS pin 10
  pinMode (FCLK_pin, OUTPUT); // Driver board filter clock pin 9
  pinMode (DRIVER_HV_EN_pin, OUTPUT); // driver board high voltage output enable pin 8

  // Run filter clock at desired frequency as a 50% duty cycle square wave
  Timer1.initialize(fclk_period);
  Timer1.pwm(FCLK_pin, FCLK_DUTY_50);

  // write pins low
  digitalWrite(slaveSelectPin,HIGH); //Chip select is inverted; pull low when writing a command, leave high otherwise
  digitalWrite(DRIVER_HV_EN_pin,hv_enabled); //Default low

  // Set up DAC
  // send the DAC write word one byte at a time:
  // 0x280001 FULL_RESET
  digitalWrite(slaveSelectPin,LOW);
  SPI.transfer(0x28);
  SPI.transfer(0x00);
  SPI.transfer(0x01);
  digitalWrite(slaveSelectPin,HIGH);
  delayMicroseconds(1);
  // 0x380001 INT_REF_EN
  digitalWrite(slaveSelectPin,LOW);
  SPI.transfer(0x38);
  SPI.transfer(0x00);
  SPI.transfer(0x01);
  digitalWrite(slaveSelectPin,HIGH);
  delayMicroseconds(1);
  // 0x20000F DAC_EN_ALL
  digitalWrite(slaveSelectPin,LOW);
  SPI.transfer(0x20);
  SPI.transfer(0x00);
  SPI.transfer(0x0F);
  digitalWrite(slaveSelectPin,HIGH);
  delayMicroseconds(1);
  // 0x300000 LDAC_EN
  digitalWrite(slaveSelectPin,LOW);
  SPI.transfer(0x30);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  digitalWrite(slaveSelectPin,HIGH);
  delayMicroseconds(1);
}

void PicoAmp::sendCommand() {
    // default SPI lib
    // manually toggle SS pin (blergh)
    digitalWrite(slaveSelectPin,LOW);
    //  send the DAC write word one byte at a time:
    SPI.transfer(DAC_write_word[0]);
    SPI.transfer(DAC_write_word[1]);
    SPI.transfer(DAC_write_word[2]);
    // take the SS pin high to de-select the chip:
    digitalWrite(slaveSelectPin,HIGH);
}

void PicoAmp::setCommand(uint8_t commandByte, uint8_t address) {
  DAC_write_word[0] = commandByte << 3 | address;
}

void PicoAmp::setData(uint16_t data) {
  DAC_write_word[1] = data >> 8;     // MSB
  DAC_write_word[2] = data & 0x00FF; // LSB
}

void PicoAmp::update() {
  setCommand(UPDATE, DAC_ALL);
  setData(0);
  sendCommand();
}

void PicoAmp::setChannel(uint16_t channel, uint16_t val) {
  setCommand(WRITE, channel);
  setData(min(val,HV_HI_LIMIT)); // Prevents driver from going above high voltage limit, preventing mirror damage (unheard of...)
  sendCommand();
}

void PicoAmp::setDiff(uint8_t axis, int32_t val) {
  uint16_t midpoint = 32768;
  if (axis == X_AXIS) {
    setChannel(DAC_A, (uint16_t)(midpoint + val/2));
    setChannel(DAC_B, (uint16_t)(midpoint - val/2));
  } else if (axis == Y_AXIS) {
    setChannel(DAC_D, (uint16_t)(midpoint + val/2));
    setChannel(DAC_C, (uint16_t)(midpoint - val/2));
  }
}

void PicoAmp::enableHV(){
  hv_enabled = true;
  digitalWrite(DRIVER_HV_EN_pin,hv_enabled);
}

void PicoAmp::disableHV(){
  hv_enabled = false;
  digitalWrite(DRIVER_HV_EN_pin,hv_enabled);
}
