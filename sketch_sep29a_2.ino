#include <AFMotor.h>  

AF_DCMotor motorR(2);
AF_DCMotor motorL(4);

int incomingByte = 0; 
bool flag = false;
bool L = false;
bool R = false;

enum Command {
    kNeedCommand = 0x00,
    kForward = 0x01,
    kBack = 0x02,
    kLeft = 0x03,
    kRight = 0x04,
    kStop = 0x05,
    kAbort = 0x6
  };


void moveit(int L, int R, int speed, int time)
{
  if(R != -1)
  {
    motorR.run(R);
    motorR.setSpeed(speed);
  }
  if(L != -1)
  {
    motorL.run(L); 
    motorL.setSpeed(speed);
  } 
  delay(time);
  stop(L != -1, R != -1);
}

void stop(bool L, bool R)
{
  if(R)
    motorR.run(RELEASE);
  if(L)
    motorL.run(RELEASE);
  delay(500);
}

void forward(int speed, int time)
{
  moveit(FORWARD, FORWARD, speed, time);
}

void backward(int speed, int time)
{
  moveit(BACKWARD, BACKWARD, speed, time);
}

void left(int speed, int time)
{
  moveit(-1, FORWARD, speed, time);
}

void right(int speed, int time)
{
  moveit(FORWARD, -1, speed, time);
}

void leftward(int speed, int time)
{
  moveit(BACKWARD, FORWARD, speed, time);
}

void rightward(int speed, int time)
{
  moveit(FORWARD, BACKWARD, speed, time);
}

void setup() { 
  
  Serial.begin(9600);
  
  motorR.setSpeed(255);
  motorL.run(RELEASE);
  motorR.setSpeed(255);
  motorL.run(RELEASE);
}

int i;

void loop() {
  if(flag)
    return;
   if (Serial.available() > 0) {  
        incomingByte = Serial.read();
        switch(incomingByte){
         case kNeedCommand:  printf("Need a command!\n");
         break;
         case kForward: forward(255, 1000);
         break;
         case kBack: backward(255, 1000);
         break;
         case kLeft: left(255, 500);
         break;
         case kRight: right(255, 500);
         break;
         case kStop: stop(L, R);
         break;
         case kAbort: flag = 1;
         break;
        }
        Serial.write(kNeedCommand);
    }
  delay(5000);
}

