
#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(19, 18);
MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;


int leftMotorForward = A1;    
int leftMotorBackward = A2;   
int rightMotorForward = A3;  
int rightMotorBackward = A4;  

int rightMotorENB = A0; 
int leftMotorENB = A5;  
void setup() {
  Serial.begin(9600);
   mySerial.begin(4800);
  mySerial.println("Hello, world?");
    pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
 
  mpu.calibrateGyro();

  
  mpu.setThreshold(3);
  Serial.print("hello");
}

void loop() {
//gyro();

 if (mySerial.available() > 0) {
   int inByte = mySerial.read();
   Serial.print(inByte);{
    if (inByte=='f')
{Serial.print("hi");
  MotorForward();}
else if(inByte=='b')
{MotorBackward();}
else if(inByte=='l')
{TurnLeft();}
else if(Serial.read()=="rt")
{TurnRight();}
else if(Serial.read()=="sp")
{MotorStop();}}}
}
void gyro()
{
   timer = millis();

  Vector norm = mpu.readNormalizeGyro();

  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

//  Serial.print(" Pitch = ");
  //Serial.print(pitch);
  //Serial.print(" Roll = ");
  //Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  delay((timeStep*1000) - (millis() - timer));
}
void straight()
{
   {if ( yaw <= 1 && yaw >= -1 ) {  MotorStop(); }
  else if ( yaw >1 ) { TurnRight(); }

  else {TurnLeft(); }}
}
void rightangle()
{
 {if ( yaw >= -91 && yaw <= -89) {  MotorStop(); }
  else {
    if ( yaw  >-89) { TurnRight(); }

  else {TurnLeft(); }}}
}
void leftangle()
{
 {if ( yaw >= 91 && yaw <= 89) {  MotorStop(); }
  else {
    if ( yaw < 89) { TurnLeft(); }

  else {TurnRight(); }}}
}
void MotorForward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

void MotorBackward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}

void TurnLeft(void)   
{
  digitalWrite(leftMotorENB,100);
  digitalWrite(rightMotorENB,100); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
}

void TurnRight(void)   
{
  digitalWrite(leftMotorENB,100);
  digitalWrite(rightMotorENB,100);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}

void MotorStop(void)   
{
  digitalWrite(leftMotorENB,100);
  digitalWrite(rightMotorENB,100);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}
