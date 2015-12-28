/* Author: Benjamin Low (benjamin.low@digimagic.com.sg)
 *
 * Description: Code for Pololu motor shield VNH5019 that
 * controls a pair of linear actuators. Documentation found at
 * https://www.pololu.com/product/2507
 *
 * Last updated: 28 Dec 2015
 */

#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;
enum motor_states { extend, retract, neutral };
motor_states first_motor_state = neutral;
motor_states second_motor_state = neutral;

void setup() {
  Serial.begin(9600);
  Serial.println("Dual VNH5019 Motor Shield");
  md.init();
}

void loop() {

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
  }

}

void serialEvent() {

  int incoming = Serial.read();

  if (incoming == '1') {

    first_motor_state = extend;
    Serial.println("extending first");

  } else if (incoming == '2') {

    first_motor_state = retract;
    Serial.println("retracting first");

  } else if (incoming == '3') {

    first_motor_state = neutral;
    Serial.println("stopping first");

  } else if (incoming == '4') {

    second_motor_state = extend;
    Serial.println("extending second");

  } else if (incoming == '5') {

    second_motor_state = retract;
    Serial.println("retracting second");

  } else if (incoming == '6') {

    second_motor_state = neutral;
    Serial.println("stopping second");
  }
}

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while (1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault");
    while (1);
  }
}

