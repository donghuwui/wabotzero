#include <SoftwareSerial.h>
#include <Servo.h>  //add '<' and '>' before and after servo.h
 
int joint_l_0_pin = 4; // pwm pin 4
int joint_l_1_pin = 5; // pwm pin 5
int joint_l_2_pin = 6; // pwm pin 6
int joint_r_0_pin = 7; // pwm pin 7
int joint_r_1_pin = 8; // pwm pin 8
int joint_r_2_pin = 9; // pwm pin 9

SoftwareSerial inSerial(2,3);
Servo joint_l_0;

#define MAX_CMD_COUNT 7

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  inSerial.begin(9600);

//  pinMode(4, OUTPUT);
  joint_l_0.attach(joint_l_0_pin);
}

int doMovingByPreset(unsigned char preset)
{
  Serial.print("preset: ");
  Serial.print(preset, DEC);

  return preset;
}

int doMovingJointArm(char lr, unsigned char j0, unsigned char j1, unsigned char j2)
{
  Serial.print("manual: ");
  if (lr == 'L') {
    Serial.print("left, ");
    joint_l_0.write((int)j0);
    joint_l_1.write((int)j1);
    joint_l_2.write((int)j2);
  } else if (lr == 'R') {
    Serial.print("right, ");
    joint_r_0.write((int)j0);
    joint_r_1.write((int)j1);
    joint_r_2.write((int)j2);
  }

  delay(2000);

  return lr;
}

int doMovingJointDisc(unsigned char value)
{
  Serial.print("manual: disc, ");
  Serial.print(value, DEC);

  return value;
}

int doMovingWheel(unsigned char d, unsigned char m)
{
  return d;
}

char testCmds[MAX_CMD_COUNT][10] = {
  { 'P', 0x01, '\n' },
  { 'P', 0x02, '\n' },
  { 'M', 'J', 'A', 'L', 20, 0xB4, 0xB4,'\n' },
  { 'M', 'J', 'A', 'R', 50, 0xB4, 0xB4,'\n' },
  { 'M', 'J', 'D', 0xB4, '\n' },
  { 'M', 'W', 'D', 'F', '\n' },
  { 'M', 'W', 'D', 'B', '\n' }
};

void loop() {
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

  }
//  while (Serial1.available()) {
//   
//      Serial.print(Serial1.read(), HEX);
//      Serial.println();
//  }//
}
