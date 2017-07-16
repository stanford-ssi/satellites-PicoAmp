/*
 * Teensy 3.6 SPI test to control SSI's clone of Mirrorcle PicoAmp MEMS mirror driver board.
 * PicoAmp board is based on AD5664R quad 16 bit DAC with SPI input.
 * Uses 'fast' SPI library from: https://github.com/xxxajk/spi4teensy3
 * ^ is very barebones, polling to fill TX FIFO / write. No interrupts enabled / used.
 *
 * Gave up on fast SPI library for now. Will need to flesh it out more and add interrupts later
 *
 * This program generates a buffer for a 1024 point sinusoid, initializes the SPI, initializes the DAC, sets a period (loop delay for now, will use timers later)
 * then plays back the sinusoid.
 *
 * S. Maldonado
 * Jun 16th 2017
 */

//#include <spi4teensy3.h>
#include "PicoAmp.h"

#define SINE_FREQ 1       //Hz
#define BUFFER_LEN 64     //Number of samples per period of sine wave
static int16_t sine_wave[BUFFER_LEN]; // buffer to hold our sinusoid playback. Since DAC channels are 16 bits, array is int16

const float picoamp_output_period = 1000000.0/float(SINE_FREQ*BUFFER_LEN);

volatile int16_t sample = 0;     // Volatile because this variable can be updated by a timer
volatile int16_t sample2 = 16;
int8_t count = 0;

PicoAmp picoamp(0); // Desired low-pass filter frequency, in Hz - 0 disables software low-pass filter when hardware filter installed
IntervalTimer output_clock;

void isr_picoamp_output();

void init() {
  // setup PicoAmp
  picoamp.init();

  // setup serial
  Serial.begin(19200);
}

void create_sine() {
  noInterrupts();
  float twopi = 2*PI; // good old pi
  float phase = twopi/BUFFER_LEN; // phase increment for sinusoid
  float val = 0; // temp variable to store value for sine wave
  int16_t num = 0;
  // Fill the sine wave buffer with 1024 points
  Serial.println("Filling in sine wave");
  for (int i = 0; i < BUFFER_LEN; i++){
    val = sin(i*phase); // fill 0 to twopi phase, output range -1 to 1
    num =(int16_t) ((val*2000));// convert decimal to int16 representation: multiply range to fill 65535 values (-32767 -> 32767) (lose one value, but don't have to deal with rollover)
    sine_wave[i] = num; // put in buffer
  }
  interrupts();
}

void setup() {
  // put your setup code here, to run once:
  init();
  create_sine();
  output_clock.begin(isr_picoamp_output, picoamp_output_period);
}

void checkSerial() {
    // simple input to toggle things on / off for now
    if (Serial.available() >0) {
      // read a byte
      byte byte_in = Serial.read();
      // turn HV output on / off with command
      if (byte_in == '1') {
        picoamp.enableHV();

        Serial.println("HV outputs enabled.");
      }
      if (byte_in == '0') {
        picoamp.disableHV();

        Serial.println("HV outputs disabled.");
      }

      if (byte_in == 's') {
        for (int i = 0; i < BUFFER_LEN; i++){
          Serial.println(sine_wave[i]);
        }
      }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  delayMicroseconds(10);
  count++;
  // if count = 100, youve waited 1ms time to update things
  if (count == 100) {
    count = 0;
    // grab next sample from sine wave and line it up in the DAC write word
    checkSerial();

  }
}

void isr_picoamp_output(){
  picoamp.setDiff(picoamp.X_AXIS, 2*sine_wave[sample]);
  picoamp.setDiff(picoamp.Y_AXIS, 2*sine_wave[sample2]);

  // picoamp.setDiff(picoamp.X_AXIS, -43000);
  // picoamp.setDiff(picoamp.Y_AXIS, 43000);
  picoamp.update();

  sample++; // increment for next sample
  sample2++;
  if (sample >= BUFFER_LEN) sample = 0; // reset to start of array
  if (sample2 >= BUFFER_LEN) sample2 = 0; // reset to start of array
}
