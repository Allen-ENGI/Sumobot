//setup ultrosonic
const int trigPinF = 5;
const int echoPinF = 4;

const int trigPinL = 7;
const int echoPinL = 6;

const int trigPinR = 9;
const int echoPinR = 8;

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

//Speed control
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
  setSpeedL(0); 
  setSpeedR(0);

  //arm();
  
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

void attack(int a) {
  if(a == 1){
    setSpeedR(45);
    setSpeedL(45);
  } else{
    setSpeedR(0);
    setSpeedL(0);
    delay(50);
    setSpeedR(20);
    setSpeedL(20);
    delay(50);
    setSpeedR(45);
    setSpeedL(45);
    Serial.println("attack");
  }

  if(digitalRead(detectR) || digitalRead(detectL)) {
    setSpeedR(0);
  setSpeedL(0);
  }
}


void move_back(){
  Serial.println("left edge");
  setSpeedR(0);
  setSpeedL(0);
  delay(300); 
  setSpeedL(20);
  setSpeedR(-20);
 
  delay(1000);
  setSpeedR(0);
  setSpeedL(0);
  delay(300);
}
void turn_left(){
  setSpeedR(-15);
  setSpeedL(15);
  delay(500);
  setSpeedR(0);
  setSpeedL(0);
}


float ultro(const int tri, const int echo){
  float result;
  float duration;
  digitalWrite(tri, LOW);
  delayMicroseconds(2);
  digitalWrite(tri, HIGH);
  delayMicroseconds(10);
  digitalWrite(tri, LOW);
  duration = pulseIn(echo, HIGH);

  result = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(result);

  return result;
}


int att_counter = 0;


void loop() {  
  int speedL, speedR;

  //edge
  //low is white, hight is black
  int edgeL = digitalRead(detectL);
  int edgeR = digitalRead(detectR);

  if(!digitalRead(detectL) && digitalRead(detectR) ){//left sensor reaching edge
    //right back turn
    move_back();
    turn_left();
    //setSpeedR(0);
    //setSpeedL(0);
    att_counter = 0;

  }else if(!digitalRead(detectR) && digitalRead(detectL)){
    //left back turn
    Serial.println("right edge");
    setSpeedR(0);
    setSpeedL(0);
    att_counter = 0;
  }
  // else if((!digitalRead(detectL)) && (!digitalRead(detectR))){//both sesnor
  //   Serial.println("Both");
  //   //back
  //   //turn around
  // }

  else{
    //no edge sensor, activate Search or attack
    Serial.println("Not edge");
    float disF = ultro(trigPinF, echoPinF);
    float disL = ultro(trigPinL, echoPinL);
    float disR = ultro(trigPinR, echoPinR);
    // Serial.println(disR);

    if(disF < 30){//front detect
    Serial.println("Front side enemy");
    attack(att_counter);
    att_counter = 1;


      //forward attack
    }else if(disL < 50){//one of the sensors detecting
      //left turn, attack
      Serial.println("left side enemy");
      delay(1000);
    }else if(disR < 50){
      Serial.println("Right side enemy");
      delay(1000);
      //right turn, attack
    }else{//no sensor detected
      Serial.println("Searching");
      delay(1000);
      //search
    }
    Serial.println("1");
  }

  // distance = ultro();
  // delay(100);
  
  //0-50
  // put your main code here, to run repeatedly:
  //Implements speed variable

  // if (!digitalRead(detect))//white
  // {
  //   Serial.println("detect!");
  //   speed = -20;

  //   setSpeed(speed);
  //   delay(100);
  // }else{//black
  //   Serial.println("No detect!");
  //   speed = 20;
  //   setSpeed(speed);
  //   delay(100);

  // }

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
