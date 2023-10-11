#include "PIDController.h"

#define ENCODER_A 2 
#define ENCODER_B 3

#define MOTOR_CW 9
#define MOTOR_CCW 10

#define __Kp 260 // Proportional constant
#define __Ki 2.7 // Integral Constant
#define __Kd 2000 // Derivative Constant

//390 ppr     52400 ppr  52400/4 = 13100

//volatile long int encoder_count = 0; // stores the current encoder count
unsigned int integerValue = 0; // stores the incoming serial value. Max value is 65535
char incomingByte; // parses and stores each character one by one
int motor_pwm_value = 255; // after PID computation data is stored in this variable.
PIDController pidcontroller;

long int encoder_count = 0;
long int pwm = 0;
double theta = 0;

void setup() {
  Serial.begin(115200); // Serial for Debugging
  pinMode(ENCODER_A, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B, INPUT); // ENCODER_B as Input
  pinMode(MOTOR_CW, OUTPUT); // MOTOR_CW as Output
  pinMode(MOTOR_CCW, OUTPUT); // MOTOR_CW as Output

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoder, RISING);
}


void loop(){
  // if(pwm<255){
  //   motor_ccw(pwm);

  //   theta = double(encoder_count)/195*M_PI;
  //   // Serial.print("theta: ");
  //   // Serial.println(theta,5);
  //   Serial.print("encoder_count: ");
  //   Serial.println(encoder_count);
  //   delay(30);
  //   pwm++;
  // }else{
  //   motor_ccw(255);

  //   theta = double(encoder_count)/195*M_PI;
  //   // Serial.print("theta: ");
  //   // Serial.println(theta,5);
  //   Serial.print("encoder_count: ");
  //   Serial.println(encoder_count);
  // }
  Serial.print("encoder_count: ");
  Serial.println(encoder_count);
  motor_cw(150);

}


void motor_ccw(int power) {
  if (power > 3) {
    analogWrite(MOTOR_CW, power);
    digitalWrite(MOTOR_CCW, LOW);
  }
// both of the pins are set to low
  else {
    digitalWrite(MOTOR_CW, LOW);
    digitalWrite(MOTOR_CCW, LOW);
  }
}

void motor_cw(int power) {
  if (power > 3) {
    analogWrite(MOTOR_CCW, power);
    digitalWrite(MOTOR_CW, LOW);
  }
  else {
    digitalWrite(MOTOR_CW, LOW);
    digitalWrite(MOTOR_CCW, LOW);
  }
}


void encoder() {
  if (digitalRead(ENCODER_B) == HIGH)
    encoder_count++;
  else
    encoder_count--;
}