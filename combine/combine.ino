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
  int angle = map(speed, -100, 100, 0, 180); //Sets servo positions to different speeds ESC1.write(angle);
  ESCL.write(angle); 
  // delay(1000);
}
void setSpeedR(int speed){
  int angle = map(speed, -100, 100, 0, 180); //Sets servo positions to different speeds ESC1.write(angle);
  ESCR.write(angle); 
  // delay(1000);
}




void setup() {
  //motor
  ESCL.attach(2, 1000, 2000); //Adds ESC to certain pin. 
  ESCR.attach(3, 1000, 2000); //Adds ESC to certain pin. 
  setSpeedL(0); 
  setSpeedR(0);
  delay(500);
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
    setSpeedR(10);
    setSpeedL(11);
  } else{
    setSpeedR(0);
    setSpeedL(0);
    //delay(50);
    setSpeedR(20);
    setSpeedL(22);
    //delay(50);
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
  setSpeedL(-22);
  setSpeedR(-20);
 
  delay(700);
  setSpeedR(0);
  setSpeedL(0);
  delay(300);
}
void turn_left(){
  setSpeedR(-20);
  setSpeedL(20);
  delay(400);
  setSpeedR(0);
  setSpeedL(0);
}

void turn_right(){
  setSpeedL(20);
  setSpeedR(-20);
  delay(400);
  setSpeedR(0);
  setSpeedL(0);
}

void search(){
  //setSpeedR(13);
  setSpeedR(0);
  setSpeedL(0);
  setSpeedL(27);
  setSpeedR(19);
  delay(100);
  setSpeedL(0);
  //setSpeedR(21);
  setSpeedR(0);
  delay(10);
  

  //setSpeedR(-20);
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


int attack_counter = 200;
 

void loop() {  
  int speedL, speedR;
  
  //edge
  //low is white, hight is black
  int edgeL = digitalRead(detectL);
  int edgeR = digitalRead(detectR);
  float disF = ultro(trigPinF, echoPinF);
  //delay(1000);
  if(!digitalRead(detectL) && digitalRead(detectR) && disF > 30){//left sensor reaching edge
    //right back turn
    move_back();
    turn_left();
    //setSpeedR(0);
    //setSpeedL(0);
    attack_counter = 200;

  }else if(!digitalRead(detectR) && digitalRead(detectL) && disF>30){
    //left back turn
    Serial.println("right edge");
    // setSpeedR(0);
    // setSpeedL(0);
    move_back();
    turn_right();
    attack_counter = 200;
  }
  
  else if((!digitalRead(detectL)) && (!digitalRead(detectR)) && disF >50){//both sesnor
    Serial.println("Both");
    //back
    move_back();
    turn_right();
    setSpeedR(0);
    setSpeedL(0);
    attack_counter = 200;

    //turn around
  }

  else if((!digitalRead(detectL)) && (!digitalRead(detectR)) && disF < 30){
    // setSpeedR(0);
    // setSpeedL(0);
    // delay(20);

    setSpeedR(22);
    setSpeedL(20);
    attack_counter = 200;
  }

  else{
    //no edge sensor, activate Search or attack
    Serial.println("Not edge");
    float disF = ultro(trigPinF, echoPinF);
    float disL = ultro(trigPinL, echoPinL);
    float disR = ultro(trigPinR, echoPinR);
    // Serial.println(disR);

    if(disF < 60){//front detect
      Serial.println("Front side enemy");
      //attack(att_counter);
      //att_counter = 1;
      // setSpeedR(0);
      // setSpeedL(0);
      // delay(20);

      // setSpeedR(22);
      // setSpeedL(20);
      // if(60> disF > 12){
      //   setSpeedR(0);
      //   setSpeedL(0);
      //   delay(5);

      //   setSpeedR(22);
      //   setSpeedL(20);
      // } else { //强力攻击
      //   setSpeedR(0);
      //   setSpeedL(0);
      //   delay(5);

      //   setSpeedR(33);
      //   setSpeedL(30);
      // }
    //delay(1000);
      setSpeedR(0);
      setSpeedL(0);
      delay(5);

      setSpeedR((attack_counter + 20)/10);
      setSpeedL(attack_counter/10);
      //forward attack
      if(attack_counter < 300){
        attack_counter = attack_counter + 4;
      }
      
    } else if(disL < 60){//one of the sensors detecting
      //left turn, attack
      attack_counter = 20;
      Serial.println("left side enemy");
      //delay(1000);
      setSpeedR(0);
      setSpeedL(0);
      delay(5);
      setSpeedR(25);
      delay(20);
      

    }else if(disR < 60){
      attack_counter = 200;
      Serial.println("Right side enemy");
      //delay(1000);

      setSpeedR(0);
      setSpeedL(0);
      delay(5);
      setSpeedL(19);
      delay(5);
      
      
      //right turn, attack
    }else{//no sensor detected
      Serial.println("Searching");
      search();
      attack_counter = 200;
      //delay(1000);
      //search
    }
    Serial.println("1");
  }


  //需要测试内容：
  //1. 左右转90°所需速度和时间
  //2. searching function
  //3. 躲避edge的速度和时间
  //4. 检测距离50cm是否合理
  //5. 去掉所有条件中的delay测试
  //

}
