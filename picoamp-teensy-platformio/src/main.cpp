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
#include "PicoAmp.h"

#define BUFFER_LEN 1024
static int16_t sine_wave[BUFFER_LEN]; // buffer to hold our sinusoid playback. Since DAC channels are 16 bits, array is int16

int sample = 0;
int sample2 = 1024 >> 2;
int count = 0;

PicoAmp picoamp;

void init() {
  // setup PicoAmp
  picoamp.init();

  // setup serial
  Serial.begin(19200);
}

void create_sine() {
  float twopi = 2*PI; // good old pi
  float phase = twopi/BUFFER_LEN; // phase increment for sinusoid
  float val = 0; // temp variable to store value for sine wave
  int16_t num = 0;
  // Fill the sine wave buffer with 1024 points
  Serial.println("Filling in sine wave");
  for (int i = 0; i < BUFFER_LEN; i++){
    val = sin(i*phase); // fill 0 to twopi phase, output range -1 to 1
    num = (int16_t) ((val*32767));// convert decimal to int16 representation: multiply range to fill 65535 values (-32767 -> 32767) (lose one value, but don't have to deal with rollover)
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
        picoamp.hv_enabled = 1;
        digitalWrite(DRIVER_HV_EN_pin,HIGH);

        Serial.println("HV outputs enabled.");
      }
      if (byte_in == '0') {
        picoamp.hv_enabled = 0;
        digitalWrite(DRIVER_HV_EN_pin,LOW);

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

  // driver LPF's need a clock supplied to even work. Needs to be 60x desired cutoff freq
  // quick and dirty way to get this by toggling a pin at 50kHz (ish)
  delayMicroseconds(10);
  count++;
  // if count = 100, youve waited 1ms time to update things
  if (count == 100) {
    count = 0;
    // grab next sample from sine wave and line it up in the DAC write word
    picoamp.setDiff(X_AXIS, 2*sine_wave[sample]);
    //picoamp.setChannel(DAC_A, sine_wave[sample]);
    //picoamp.setChannel(DAC_B, 65535-sine_wave[sample]);
    picoamp.setDiff(Y_AXIS, 2*sine_wave[sample2]);
    picoamp.update();

    sample++; // increment for next sample
    sample2++;
    if (sample >= 1024) sample = 0; // reset to start of array
    if (sample2 >= 1024) sample2 = 0; // reset to start of array
    checkSerial();

  }

  // toggle the FCLK pin every time
  if (picoamp.FCLK_state == LOW){
    picoamp.FCLK_state = HIGH;
  } else {
    picoamp.FCLK_state = LOW;
  }
  digitalWrite(FCLK_pin,picoamp.FCLK_state);
}
