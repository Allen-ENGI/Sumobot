#define detect A3
#include <Servo.h>
Servo esc;// 创建一个 Servo 对象


int value;
void setup() {
  // put your setup code here, to run once:
  pinMode(detect,INPUT);
  esc.attach(9);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = digitalRead(detect);
  if (digitalRead(detect) == LOW)
  {
    Serial.println("detect!");
    esc.writeMicroseconds(100);
    // Serial.println(value);
    // delay(10);
  }else{
    Serial.println("No detect!");
    // esc.writeMicroseconds(0);
    // esc.write(0);
    delay(2000);
  }
}
