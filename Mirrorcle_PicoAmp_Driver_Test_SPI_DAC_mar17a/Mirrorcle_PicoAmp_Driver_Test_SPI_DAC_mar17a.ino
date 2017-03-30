/*
 * Teensy 3.2 SPI test to control Mirrorcle PicoAmp MEMS mirror driver board.
 * PicoAmp board is based on AD5664R quad 16 bit DAC with SPI input.
 * Uses 'fast' SPI library from: https://github.com/xxxajk/spi4teensy3
 * ^ is very barebones, polling to fill TX FIFO / write. No interrupts enabled / used.
 * 
 * Gave up on fast SPI library for now. Will need to flesh it out more and add interrupts later
 * 
 * This program generates a buffer for a 1024 point sinusoid, initializes the SPI, initializes the DAC, sets a period (loop delay for now, will use timers later)
 * then plays back the sinusoid.
 * 
 * Michael Taylor
 * Mar 17th 2017
 */

//#include <spi4teensy3.h>
#include <SPI.h>

#define PI 3.14159265359

#define BUFFER_LEN 1024

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
const uint8_t DAC_A = 0b000;
const uint8_t DAC_B = 0b001;
const uint8_t DAC_C = 0b010;
const uint8_t DAC_D = 0b011;
const uint8_t DAC_ALL = 0b111;

const uint8_t X_AXIS = 1;
const uint8_t Y_AXIS = 2;

// Pins
const int slaveSelectPin = 10;
const int FCLK_pin = 9;
const int DRIVER_HV_EN_pin = 8;

static int sine_wave[BUFFER_LEN]; // buffer to hold our sinusoid playback. Since DAC channels are 16 bits, array is uint16
static uint8_t DAC_write_word[3]; // DAC input register is 24 bits, SPI writes 8 bits at a time. Need to queue up 3 bytes (24 bits) to send every time you write to it

int sample = 0;
int sample2 = 1024 >> 2;
int FCLK_state = LOW;
int count = 0;
int num_update = 0;

void setPin(int pin, int state) {
  digitalWrite(pin, state);
}

void print(String str) {
  Serial.println(str);
}

void spiWriteByte(uint8_t b) {
  SPI.transfer(b);
}

byte hv_enabled = 0;

void setupPins() {
  // Setup Pins:
  pinMode (slaveSelectPin, OUTPUT); // SPI SS pin 10
  pinMode (FCLK_pin, OUTPUT); // Driver board filter clock pin 9
  pinMode (DRIVER_HV_EN_pin, OUTPUT); // driver board high voltage output enable pin 8
  // write pins low
  setPin(slaveSelectPin,LOW);
  setPin(FCLK_pin,FCLK_state);
  setPin(DRIVER_HV_EN_pin,LOW);
  // setup serial
  Serial.begin(19200);
  
  // setup SPI
  print("Setting up SPI");
  // fast SPI lib
  // spi4teensy3::init(); // full speed, cpol 0, cpha 0

  // initialize SPI:
  SPI.begin();
}

void init() {
  setupPins();
    // setup DAC
  print("Setting up DAC");
  //  send the DAC write word one byte at a time:
  // 0x280001 FULL_RESET
  setPin(slaveSelectPin,LOW);
  spiWriteByte(0x28);
  spiWriteByte(0x00);
  spiWriteByte(0x01);
  setPin(slaveSelectPin,HIGH);
  delayMicroseconds(1);
  // 0x380001 INT_REF_EN
  setPin(slaveSelectPin,LOW);
  spiWriteByte(0x38);
  spiWriteByte(0x00);
  spiWriteByte(0x01);
  setPin(slaveSelectPin,HIGH);
  delayMicroseconds(1);
  // 0x20000F DAC_EN_ALL
  setPin(slaveSelectPin,LOW);
  spiWriteByte(0x20);
  spiWriteByte(0x00);
  spiWriteByte(0x0F);
  setPin(slaveSelectPin,HIGH);
  delayMicroseconds(1); 
  // 0x300000 LDAC_EN
  setPin(slaveSelectPin,LOW);
  spiWriteByte(0x30);
  spiWriteByte(0x00);
  spiWriteByte(0x00);
  setPin(slaveSelectPin,HIGH);
  delayMicroseconds(1);
}

void create_sine() {
  float twopi = 2*PI; // good old pi
  float phase = twopi/BUFFER_LEN; // phase increment for sinusoid
  float val = 0; // temp variable to store value for sine wave
  int num = 0;
  // Fill the sine wave buffer with 1024 points
  print("Filling in sine wave");
  for (int i = 0; i < BUFFER_LEN; i++){
    //val = sin(i*phase); // fill 0 to twopi phase, output range -1 to 1
    //num = (int) (val*65535);// convert decimal to uint16 representation: multiply range to fill 65536 values (-32768 -> 32768) and add 32767 offset to go 0-65535 (ish, lose one value for 0)
    num = (int) ((65535 * 4 * i)/1024);// convert decimal to uint16 representation: multiply range to fill 65536 values (-32768 -> 32768) and add 32767 offset to go 0-65535 (ish, lose one value for 0)
    num = 2 * 65535 - num;
    num = abs(num) - 65535;
    
    sine_wave[i] = num; // put in buffer  
  }
}

void setup() {
  // put your setup code here, to run once:
  init();
  create_sine();
}

void checkSerial() {
    // simple input to toggle things on / off for now
    if (Serial.available() >0) {
      // read a byte 
      byte byte_in = Serial.read();
      // turn HV output on / off with command
      if (byte_in == '1') {
        hv_enabled = 1;
        setPin(DRIVER_HV_EN_pin,HIGH);

        print("HV outputs enabled.");
      }
      if (byte_in == '0') {
        hv_enabled = 0;
        setPin(DRIVER_HV_EN_pin,LOW);

        print("HV outputs disabled.");
      }
    }
}

void sendCommand() {
    // default SPI lib
    // manually toggle SS pin (blergh)
    setPin(slaveSelectPin,LOW);
    //  send the DAC write word one byte at a time:
    spiWriteByte(DAC_write_word[0]);
    spiWriteByte(DAC_write_word[1]);
    spiWriteByte(DAC_write_word[2]);
    // take the SS pin high to de-select the chip:
    setPin(slaveSelectPin,HIGH);  
}

void setCommand(uint8_t commandByte, uint8_t address) {
  DAC_write_word[0] = commandByte << 3 | address;
}

void setData(uint16_t data) {
  DAC_write_word[1] = data >> 8;     // MSB
  DAC_write_word[2] = data & 0x00FF; // LSB
}

void flush() {
  setCommand(UPDATE, DAC_ALL);
  setData(0);
  sendCommand();
}

void setChannel(uint16_t channel, uint16_t val) {
  setCommand(WRITE, channel);
  setData(val);
  sendCommand();
}

void setDiff(uint8_t axis, int val) {
  uint16_t midpoint = 65535/2;
  if (axis == X_AXIS) {
    setChannel(DAC_A, midpoint + val/2);
    setChannel(DAC_B, midpoint - val/2);
  } else if (axis == Y_AXIS) {
    setChannel(DAC_D, midpoint + val/2);
    setChannel(DAC_C, midpoint - val/2);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // driver LPF's need a clock supplied to even work. Needs to be 60x desired cutoff freq
  // quick and dirty way to get this by toggling a pin at 50kHz (ish)
  delayMicroseconds(10);
  count++;
  // if count = 100, youve waited 1ms time to update things
  if (true) {
    //count = 0;
    // grab next sample from sine wave and line it up in the DAC write word
    setDiff(X_AXIS, sine_wave[sample]);
    setDiff(Y_AXIS, sine_wave[sample2]);
    flush();
    
    sample++; // increment for next sample
    sample2++;
    if (sample >= 1024) sample = 0; // reset to start of array
    if (sample2 >= 1024) sample2 = 0; // reset to start of array
    checkSerial();
    
  }
  if (count == 10) {
    count = 0;
  // toggle the FCLK pin every time
  if (FCLK_state == LOW){
    FCLK_state = HIGH;
  } else {
    FCLK_state = LOW;
  }
  setPin(FCLK_pin,FCLK_state);
  }
  num_update++;
  if (num_update % 500000 == 0) {
    //print(num_update);
  }
}
