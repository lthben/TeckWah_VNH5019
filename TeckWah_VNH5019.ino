/* Author: Benjamin Low (benjamin.low@digimagic.com.sg)
 *
 * Description: Code for Pololu motor shield VNH5019 that
 * controls a pair of linear actuators. Documentation found at
 * https://www.pololu.com/product/2507
 *
 * Last updated: 26 Jan 2016
 */

#include "DualVNH5019MotorShield.h"

//USER DEFINED SETTINGS
bool DEBUG = false;
int thisLinearActuatorBoxNum = 2; //1 is for the horizontal drawer, 2 for the vertical display

DualVNH5019MotorShield md;
enum motor_states { extend, retract, neutral };
motor_states first_motor_state = neutral;
//motor_states second_motor_state = neutral;

void setup() {
  Serial.begin(9600);
  if (DEBUG) Serial.println("Dual VNH5019 Motor Shield");
  md.init();
}

void loop() {

  stopIfFault();
  
  switch (first_motor_state) {
    case (extend):
        md.setM1Speed(-400);
      break;
    case (retract):
        md.setM1Speed(400);
      break;
    case (neutral):
      md.setM1Brake(400);
      break;
    default:
      break;
  }

    /*
  switch (second_motor_state) {
    case (extend):
        md.setM2Speed(-400);
      break;
    case (retract):
        md.setM2Speed(400);
      break;
    case (neutral):
      md.setM2Brake(400);
      break;
    default:
      break;
  } */
}

void serialEvent() {

  int incoming = Serial.read();

  if (incoming == '1') {

    first_motor_state = extend;
    if (DEBUG)   Serial.println("extending");

  } else if (incoming == '0') {

    first_motor_state = retract;
    if (DEBUG) Serial.println("retracting");
  } 
}

void stopIfFault()
{
  if (md.getM1Fault())
  {
    if (DEBUG) Serial.println("M1 fault");
    while (1);
  } /*
  if (md.getM2Fault())
  {
    if (DEBUG) Serial.println("M2 fault");
    while (1);
  } */
}

