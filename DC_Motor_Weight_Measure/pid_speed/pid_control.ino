#include <PID_v1_bc.h>
#include <math.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>//调用红外遥控对应的库

#define ENCODER_A 2
#define ENCODER_B 3
#define MOTOR_CW 9
#define MOTOR_CCW 10

#define __Kp 440
#define __Ki 140
#define __Kd 120

//设置LCD1602设备地址，这里的地址是0x3F，一般是0x20，或者0x27，具体看模块手册
LiquidCrystal_I2C lcd(0x27,16,2);  

double Setpoint=0;
double Input=0;
double Output=0;
PID myPID(&Input, &Output, &Setpoint, __Kp, __Ki, __Kd, DIRECT);

long int encoder_count = 0;
unsigned int IntValue = 0;
char incomingByte;
int motor_pwm_value = 255;
long int last_encoder_count = 0;
unsigned long lastTime = 0;
double current_speed = 0;

// 390ppr 52400ppr  52400/4 = 13100
int ppr = 52400;
int a = 10000;

double M = 0;
int M_count = 0;
int mode = 0;

void setup() {
  lcd.init();                  // 初始化LCD
  lcd.backlight();             //设置LCD背景等亮
  Serial.begin(115200);
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoder, RISING);

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255);

}

void loop() {
  while (Serial.available() > 0) {
    // 390/4 = 97.5
    IntValue = Serial.parseInt();
    incomingByte = Serial.read();
    Setpoint = (double)IntValue/a;
    if (incomingByte == '\n')
      continue;
  }

  if(M == 0){
    Input = double(encoder_count)/a;
    myPID.Compute();
    motor_pwm_value = Output;

    if (motor_pwm_value > 0)
      motor_ccw(abs(motor_pwm_value));
    else
      motor_cw(abs(motor_pwm_value));

    if(encoder_count>12900 & M_count == 0){
      M = 5.4431*double(motor_pwm_value)-5.5141;
      M_count++;
    }
  }  
  else{
    delay(200);
    digitalWrite(MOTOR_CW, LOW);
    digitalWrite(MOTOR_CCW, LOW);
  }

  lcd.setCursor(0,0);
  lcd.print(M,2);
  lcd.print(" g");

  delay(1);
}

void encoder() {
  if (digitalRead(ENCODER_B) == HIGH)
    encoder_count++;
  else
    encoder_count--;
}

void motor_cw(int power) {
  if (power > 3) {
    analogWrite(MOTOR_CW, power);
    digitalWrite(MOTOR_CCW, LOW);
  } else {
    digitalWrite(MOTOR_CW, LOW);
    digitalWrite(MOTOR_CCW, LOW);
  }
}

void motor_ccw(int power) {
  if (power > 3) {
    analogWrite(MOTOR_CCW, power);
    digitalWrite(MOTOR_CW, LOW);
  } else {
    digitalWrite(MOTOR_CW, LOW);
    digitalWrite(MOTOR_CCW, LOW);
  }
}
