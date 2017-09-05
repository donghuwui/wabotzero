#include <SoftwareSerial.h>
#include <Servo.h> //add '<' and '>' before and after servo.h
#include <Wire.h> // I2C Control
#include <Adafruit_PWMServoDriver.h> // PCA9685 Servo Drive Board

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define WheelBack1 2
#define WheelBack2 3
#define WheelLeft1 4
#define WheelLeft2 5
#define WheelFront1 6
#define WheelFront2 7
#define WheelRight 8
#define WheelRight 9
#define MaxSpeed 180
#define acc 3 //속도 증감



int joint_l_0_pin = 0; // PCA9865 Pin 0
int joint_l_1_pin = 1; // PCA9865 Pin 1
int joint_l_2_pin = 2; // PCA9865 Pin 2
int joint_r_0_pin = 3; // PCA9865 Pin 3
int joint_r_1_pin = 4; // PCA9865 Pin 4
int joint_r_2_pin = 5; // PCA9865 Pin 5


<<<<<<< HEAD
=======

#define MAX_PRESET 3
int presetJoint[MAX_PRESET][6] = {
  { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 },
  { 0x50, 0x50, 0x50, 0x50, 0x50, 0x50 },
  { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }
};
>>>>>>> 21c47be11a68bdba7ea8f0781bc025d15d998273

int setJointAngle(Servo s, int v);

void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(WheelBack1, OUTPUT); 
  pinMode(WheelBack2, OUTPUT);
  pinMode(WheelLeft1, OUTPUT);
  pinMode(WheelLeft2, OUTPUT);
  pinMode(WheelFront1, OUTPUT);
  pinMode(WheelFront2, OUTPUT);
  pinMode(WheelRight1, OUTPUT);
  pinMode(WheelRight2, OUTPUT); // Wheel PWM Control

<<<<<<< HEAD

=======
>>>>>>> 21c47be11a68bdba7ea8f0781bc025d15d998273
}

int doMovingByPreset(unsigned char preset)
{
  Serial.print("preset: ");
  Serial.print(preset, DEC);

  if (preset < 0 || preset > MAX_PRESET)
    return -1;
 
  setJointAngle(joint_l_0, presetJoint[preset][0]);
  setJointAngle(joint_l_1, presetJoint[preset][1]);
  setJointAngle(joint_l_2, presetJoint[preset][2]);

  setJointAngle(joint_r_0, presetJoint[preset][3]);
  setJointAngle(joint_r_1, presetJoint[preset][4]);
  setJointAngle(joint_r_2, presetJoint[preset][5]);
    
  return preset;
}

int setJointAngle(Servo s, int v)
{
  if (v > 0 && v < 0xFF)
  {
    s.write(v);
    Serial.println(v);
  }
  // do sth or not?
}
int doMovingJointArm(char lr, unsigned char j0, unsigned char j1, unsigned char j2)
{
  Serial.print("manual: ");
  if (lr == 'L')
  {
    Serial.println("left");
    setJointAngle(joint_l_0, (int)j0);
    setJointAngle(joint_l_1, (int)j1);
    setJointAngle(joint_l_2, (int)j2);
  }
  else if (lr == 'R')
  {
    Serial.println("right");
    setJointAngle(joint_r_0, (int)j0);
    setJointAngle(joint_r_1, (int)j1);
    setJointAngle(joint_r_2, (int)j2);
  }

  delay(1000);

  return lr;
}

int doMovingJointDisc(unsigned char value)
{
  Serial.print("manual: disc, ");
  Serial.print(value, DEC);

  return value;
}

int setWheelForward(bool on)
{
  for(i=0; i<MaxSpeed; i=i+acc)
  {
    analogWrite(WheelLeft1,i);
    analogWrite(WheelLeft2,0);
    analogWrite(WheelRight1,0);
    analogWrite(WheelRight2,i);
  }

}

int setWheelBackward(bool on)
{
  for(i=0; i<MaxSpeed; i=i+acc)
  {
    analogWrite(WheelLeft1,0);
    analogWrite(WheelLeft2,i);
    analogWrite(WheelRight1,i);
    analogWrite(WheelRight2,0);
  }
}

int setWheelLeft(bool on)
{
    for(i=0; i<MaxSpeed; i=i+acc)
  {
    analogWrite(WheelLeft1,0);
    analogWrite(WheelLeft2,i);
    analogWrite(WheelRight1,i);
    analogWrite(WheelRight2,0);
  }
}

int setWheelRight(bool on)
{
    for(i=0; i<MaxSpeed; i=i+acc)
  {
    analogWrite(WheelFront1,i);
    analogWrite(WheelFront2,0);
    analogWrite(WheelBack1,0);
    analogWrite(WheelBack2,i);
  }
}

int setWheelTurnLeft(bool on)
{
    for(i=0; i<MaxSpeed; i=i+acc)
  {
    analogWrite(WheelFront1,0);
    analogWrite(WheelFront2,i);
    analogWrite(WheelBack1,0);
    analogWrite(WheelBack2,i);
    analogWrite(WheelLeft1,0);
    analogWrite(WheelLeft2,i);
    analogWrite(WheelRight1,0);
    analogWrite(WheelRight2,i);

  }
}

int setWheelTurnRight(bool on)
{
     for(i=0; i<MaxSpeed; i=i+acc)
  {
    analogWrite(WheelFront1,i);
    analogWrite(WheelFront2,0);
    analogWrite(WheelBack1,i);
    analogWrite(WheelBack2,0);
    analogWrite(WheelLeft1,i);
    analogWrite(WheelLeft2,0);
    analogWrite(WheelRight1,i);
    analogWrite(WheelRight2,0);

  }
}

int setWheelStop(bool on)
{



 }
  
   for(i=0; i<MaxSpeed; i=i+acc)
  {
    analogWrite(WheelFront1,0);
    analogWrite(WheelFront2,i);
    analogWrite(WheelBack1,0);
    analogWrite(WheelBack2,i);
    analogWrite(WheelLeft1,0);
    analogWrite(WheelLeft2,i);
    analogWrite(WheelRight1,0);
    analogWrite(WheelRight2,i);

  }
  
}


#define COUNT_FP 4
int doMovingWheel(unsigned char d, unsigned char m, unsigned char t)
{
  int (*wheelMoveFp[COUNT_FP])(bool) = {
    setWheelForward,
    setWheelBackward,
    setWheelLeft,
    setWheelRight
  };

  int (*wheelTurnFp[2])(bool) = {
    setWheelTurnLeft,
    setWheelTurnRight
  };

  int op = (int)m;

  if (d == 'D') {
    
    if (op < 0 || op > COUNT_FP)
      return -1;

    wheelMoveFp[op]((t > 0 ? true : false));

  } else if (d == 'T') {
    if (op < 0 || op > 2)
      return -1;

    wheelTurnFp[op]((t > 0 ? true : false));
  }

  return d;
}

int dispatchCommand(char cmd[])
{
  if (cmd[0] == 'M')
  {
    if (cmd[1] == 'J' && cmd[2] == 'A')
      doMovingJointArm(cmd[3], cmd[4], cmd[5], cmd[6]);
    if (cmd[1] == 'J' && cmd[2] == 'D')
      doMovingJointDisc(cmd[3]);
    if (cmd[1] == 'W' && cmd[2] == 'D')
      doMovingWheel(cmd[2], cmd[3], cmd[4]);
    if (cmd[1] == 'W' && cmd[2] == 'T')
      doMovingWheel(cmd[2], cmd[3], cmd[4]);
  }
  else if (cmd[0] == 'P')
  {
    doMovingByPreset(cmd[1]);
  }
  return 0;
}

<<<<<<< HEAD
char EspCmd[10];

void loop() {

  if (inSerial.available())
  {
    EspCmd = inSerial.read();
  }
  while (1) {
    for (int i; i < MAX_CMD_COUNT; i++) {
      if (testCmds[i][0] == 'M') {
        if (testCmds[i][1] == 'J' && testCmds[i][2] == 'A')
          doMovingJointArm(testCmds[i][3], testCmds[i][4], testCmds[i][5], testCmds[i][6]);
        if (testCmds[i][1] == 'J' && testCmds[i][2] == 'D')
          doMovingJointDisc(testCmds[i][3]);
        if (testCmds[i][1] == 'W' && testCmds[i][2] == 'D')
          doMovingWheel(testCmds[i][3], testCmds[i][4]);
      } else if (testCmds[i][0] == 'P') {
        doMovingByPreset(testCmds[i][1]);
      }
      Serial.println();
    }
=======
void loop()
{
  String cmd;
>>>>>>> 21c47be11a68bdba7ea8f0781bc025d15d998273

  while (Serial1.available())
  {
    cmd = Serial1.readString(); // read the incoming data as string
    dispatchCommand(cmd.c_str());
    Serial.println(cmd);
  }
}
