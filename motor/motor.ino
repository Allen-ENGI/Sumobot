#include <Servo.h>

Servo esc;// 创建一个 Servo 对象

void setup() {
  esc.attach(9);// 将电调器的控制线连接到数字引脚 9
  esc.writeMicroseconds(1000);// 将电调器输出设为最低值，初始化
  delay(1000);
}

void loop() {
  esc.writeMicroseconds(1500);// 设置电调器输出为中值，可以根据需要调整
  delay(5000); //等待一段时间
  esc.writeMicroseconds(1000);// 设置电调器输出为最低值
  delay(5000);// 等待一段时间
}