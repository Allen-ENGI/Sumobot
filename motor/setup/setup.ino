#include <Servo.h>;
Servo ESC1;
Servo ESC2;
int pos = 0; //Sets position variable

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

setSpeed(22,20);
delay(5000); 

setSpeed(0,0); //Sets speed variable to zero no matter what

delay(3000); //Turns off for 1 second

}