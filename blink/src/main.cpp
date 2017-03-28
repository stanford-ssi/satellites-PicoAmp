/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <TimerOne.h>
#include "PID.h"
//#include <TimerThree.h>
//#include <PID.h>
#ifndef READPIN
#define READPIN A0
#endif
#ifndef OUTPIN
#define OUTPIN A14
#endif
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif
#ifndef TESTPIN
#define  TESTPIN 1
#endif
#define Kc   1.0// Proportional
#define Ti   1000 // Integral
#define Td    0.0 // Derivative
#define RATE 0.001
volatile bool state = false;
void changeVoltage(void);
PID thisPID(Kc, Ti, Td, RATE);

void setup()
{
  pinMode(READPIN, INPUT);
  pinMode(OUTPIN, OUTPUT);
  pinMode(TESTPIN, OUTPUT);
   pinMode(LED_BUILTIN, OUTPUT);
  analogWriteResolution(12);
  analogReference(INTERNAL);
Timer1.initialize(1000);
Timer1.attachInterrupt(changeVoltage); // changes voltage every 0.15 seconds
//Timer3.initialize(10000000);
//Timer3.attachInterrupt(outPut);
Serial.begin(115200);
thisPID.setInputLimits(0, 1023);
thisPID.setOutputLimits(0, 4095);
thisPID.setBias(2048);
thisPID.setMode(AUTO_MODE);
thisPID.setSetPoint(512);
interrupts();
}

void changeVoltage(void){
  state=!state;
  digitalWrite(TESTPIN, state);
  Serial.println(analogRead(READPIN));
        thisPID.setProcessValue(analogRead(READPIN));
    //   analogWrite(OUTPIN, 2000);
       analogWrite(OUTPIN,  thisPID.compute());
}
/*void outPut(void){

}*/

void loop()
{
  // turn the LED on (HIGH is the voltage level)
digitalWrite(LED_BUILTIN, HIGH);

// wait for a second
delay(100);

// turn the LED off by making the voltage LOW
digitalWrite(LED_BUILTIN, LOW);

 // wait for a second
  delay(100);
}
