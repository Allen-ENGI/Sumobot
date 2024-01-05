//setup ultrosonic
const int trigPinF = 5;
const int echoPinF = 4;

const int trigPinL = 7;
const int echoPinL = 6;

const int trigPinR = 9;
const int echoPinR = 8;
float durationF, distanceF;
float durationL, distanceL;
float durationR, distanceR;

//setup motor
#include <Servo.h>;
Servo ESCL;
Servo ESCR;
int pos = 0; //Sets position variable

//edge sensor
#define detectL 10
#define detectR 11

void arm(){
setSpeedL(0); //Sets speed variable delay(1000);
setSpeedR(0); //Sets speed variable delay(1000);
}


void setSpeedL(int speed){
  int angle = map(speed, -50, 50, 0, 180); //Sets servo positions to different speeds ESC1.write(angle);
  ESCL.write(angle); 
  // delay(1000);
}

void setSpeedR(int speed){
  int angle = map(speed, -50, 50, 0, 180); //Sets servo positions to different speeds ESC1.write(angle);
  ESCR.write(angle); 
  // delay(1000);
}

void setup() {
  //motor
  ESCL.attach(2, 1000, 2000); //Adds ESC to certain pin. 
  ESCR.attach(3, 1000, 2000); //Adds ESC to certain pin. 
  setSpeed(0);

  arm();
  
  // put your setup code here, to run once:
  //ultrosonic
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);


  //edge
  pinMode(detectL,INPUT);
  pinMode(detectR,INPUT);

  Serial.begin(9600);
  
}

float ultro(){
  float result;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  result = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(result);
  return result;
}

void loop() {
  
  int speedL, speedR;

  //edge
  bool edgeL = digitalRead(detectL);
  bool edgeR = digitalRead(detectR);
  if(){

  }else if(){

  }else{
    
    if(){//no sensor detect
      //search
    }else if(){//one of the sensors detecting
      //attack
    }
  }

  // distance = ultro();
  // delay(100);
  
  //0-50
  // put your main code here, to run repeatedly:
  //Implements speed variable

  if (!digitalRead(detect))//white
  {
    Serial.println("detect!");
    speed = -20;

    setSpeed(speed);
    delay(100);
  }else{//black
    Serial.println("No detect!");
    speed = 20;
    setSpeed(speed);
    delay(100);

  }

  // if(distance<100){
  //   Serial.println("first");
  //   speed = 25;
  //   // ESC1.write(90); 
  //   setSpeed(speed);
  //   // delay(1000);
  // }else{
  //   Serial.println("second");
  //   speed = 0;
  //   setSpeed(speed);
  //   //  ESC1.write(0); 
  //   // delay(1000);
  // }

}
