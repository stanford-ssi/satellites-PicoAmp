/***
* This code tests a PI control loop's ability to center a laser beam on a
* quad-cell photodetector using a fast steering mirror
*
* S. Maldonado
* 2017-03-28
***/

#include "PicoAmp.h"
#include "PID.h"

const float picoamp_output_frequency = 1000.0; // [Hz]
const float picoamp_output_period = 1000000.0/picoamp_output_frequency; // [usec]

// PID Control Law:
// Dc(s)/err(s) = Kc + Kc/(Ti*s) + Kc*(Td*s)

const float Kc =        0.01;    // Proportional
const float Ti =        0.001;    // Integral
const float Td =        0.0;    // Derivative
const float PID_rate =  0.001;  // [sec]

uint8_t verbose_PID = 0;

volatile int16_t control_x = 0; // Volatile because this variable can be updated by a timer
volatile int16_t control_y = 0;

#define QUADCELL_X_PIN A0
#define QUADCELL_Y_PIN A1
#define MIRROR_MAX_ACTION 10000
#define QUADCELL_X_TARGET 512 // Center
#define QUADCELL_Y_TARGET 512 // Center
volatile int16_t quadcell_x = 0;
volatile int16_t quadcell_y = 0;

int8_t count = 0;

PicoAmp picoamp(180); // Desired low-pass filter frequency, in Hz
IntervalTimer output_clock;
PID mirror_PID_x(Kc, Ti, Td, PID_rate);
PID mirror_PID_y(Kc, Ti, Td, PID_rate);

void isr_picoamp_output();
void initPID();

void init() {
  // setup PicoAmp
  picoamp.init();

  // Set up PID
  initPID();

  pinMode(QUADCELL_X_PIN, INPUT);
  pinMode(QUADCELL_Y_PIN, INPUT);

  // setup serial
  Serial.begin(115200);
}

void initPID(){
  mirror_PID_x.setInputLimits(0, 1023); // Teensy ADC limits - 10 bit
  mirror_PID_x.setOutputLimits(-MIRROR_MAX_ACTION,MIRROR_MAX_ACTION);
  mirror_PID_x.setBias(0); // Output bias - output is centered around zero
  mirror_PID_x.setMode(AUTO_MODE);
  mirror_PID_x.setSetPoint(QUADCELL_X_TARGET); // Sets desired ADC input value

  mirror_PID_y.setInputLimits(0, 1023); // Teensy ADC limits - 10 bit
  mirror_PID_y.setOutputLimits(-MIRROR_MAX_ACTION,MIRROR_MAX_ACTION);
  mirror_PID_y.setBias(0); // Output bias - output is centered around zero
  mirror_PID_y.setMode(AUTO_MODE);
  mirror_PID_y.setSetPoint(QUADCELL_Y_TARGET); // Sets desired ADC input value
}

void setup() {
  // put your setup code here, to run once:
  init();
  output_clock.begin(isr_picoamp_output, picoamp_output_period);
}

void checkSerial() {
    noInterrupts(); // Disable interrupts, as things that the interrupts control are affected by these variables

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
      if (byte_in == 'v') {
        verbose_PID = !verbose_PID;
        if(verbose_PID) Serial.println("Verbose output on");
        else Serial.println("Verbose output off");
      }
      /*if(Serial.available() > 1 && byte_in == 'k'){

      }*/
    }

    interrupts(); // Resume your normally scheduled interruptions
}

void loop() {
  // put your main code here, to run repeatedly:
  delayMicroseconds(10);
  count++;
  // if count = 100, youve waited 1ms time to update things
  if (count == 100) {
    count = 0;
    checkSerial();
  }
}

void isr_picoamp_output(){
  // Read ADC values
  quadcell_x = analogRead(QUADCELL_X_PIN);
  quadcell_y = analogRead(QUADCELL_Y_PIN);

  // Print ADC values
  if(verbose_PID){
    Serial.println(quadcell_x);
    Serial.println(quadcell_y);
    Serial.println();
  }

  // Set new error values
  mirror_PID_x.setProcessValue(quadcell_x);
  mirror_PID_y.setProcessValue(quadcell_y);

  // Calculate controller outputs
  control_x = mirror_PID_x.compute();
  control_y = mirror_PID_y.compute();

  // Send controller output to mirror
  picoamp.setDiff(picoamp.X_AXIS, 2*control_x);
  picoamp.setDiff(picoamp.Y_AXIS, -2*control_y); // y-axis is inexplicably mirrored

  picoamp.update();
}
