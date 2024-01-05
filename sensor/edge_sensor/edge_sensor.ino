#define detect A3
#include <Servo.h>

Servo esc;// 创建一个 Servo 对象

int value;
void setup() {
  // put your setup code here, to run once:
  pinMode(detect,INPUT);
  esc.attach(9);// 将电调器的控制线连接到数字引脚 9
  // esc.writeMicroseconds(1000);// 将电调器输出设为最低值，初始化
  delay(1000);
  Serial.begin(9600);


}
void rotate(){
  
  esc.writeMicroseconds(500);// 设置电调器输出为最低值
  delay(1000);
  // delay(5000);// 等待一段时间
}

void loop() {
  // put your main code here, to run repeatedly:
  // value = digitalRead(detect);
  if (digitalRead(detect))
  {
    Serial.println("Black!");
    rotate();
  }else{
    Serial.println("White!");
    //  esc.writeMicroseconds(0);
  }
}
