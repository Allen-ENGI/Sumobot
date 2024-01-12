#include <Servo.h>;
Servo ESC1;
Servo ESC2;
const int trigPinF = 5;
const int echoPinF = 4;
int pos = 0; //Sets position variable
#define detectL 10

void arm(){

setSpeed(0,0); //Sets speed variable delay(1000);

}

void setSpeed(int speed1, int speed2){

int angle1 = map(speed1, -100, 100 , 0, 180); //Sets servo positions to different speeds ESC1.write(angle);
ESC1.write(angle1);

int angle2 = map(speed2, -100, 100 , 0, 180); //Sets servo positions to different speeds ESC1.write(angle);
ESC2.write(angle2);
}

void setup() {

ESC1.attach(3, 1000, 2000); //Adds ESC to certain pin.
ESC2.attach(2, 1000, 2000);
pinMode(trigPinF, OUTPUT);
pinMode(echoPinF, INPUT);
pinMode(detectL,INPUT);
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




void loop() {

int speed; //Implements speed variable

// for(speed = 0; speed <= 40; speed += 5) { //Cycles speed up to 70% power for 1 second

// setSpeed(speed); //Creates variable for speed to be used in in for loop

// delay(1000);

// }


//delay(3000); //Stays on for 4 seconds

// for(speed = 40; speed > 0; speed -= 5) { // Cycles speed down to 0% power for 1 second

// setSpeed(speed); delay(1000);

// }

//======ultra sensor测试==========
// float disF = ultro(trigPinF, echoPinF);
// if(disF < 40){
//   setSpeed(0,0);
//   Serial.println("stop");
// } else{
//   setSpeed(20,20);
//   Serial.println("run");
// }


//============ir sensor测试==============
if(! digitalRead(detectL)){
  setSpeed(-10,-10);
  delay(600);
  setSpeed(0,0);
} else{
  setSpeed(20,20);
}
//======================================


//setSpeed(22,20);
//setSpeed(0,0); //Sets speed variable to zero no matter what

//delay(3000); //Turns off for 1 second

}