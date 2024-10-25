#include <Servo.h> //include servo.h library
Servo myservo;
int pos = 30;
int motor_speed = 90;
int distance = 60;
boolean fire = false;
#define Left 19 // left sensor
#define Right 17 // right sensor
#define Forward 18 //front sensor
#define LM1 2 // left motor
#define LM2 4 // left motor
#define RM1 0 // right motor
#define RM2 1 // right motor
#define pump 6 //water pump
#define trigPin 14 // ultrasonic sensor trigger
#define echoPin 15 // ultrasonic sensor echo
#define Buzzer 12 // Buzzer
#define GreenL 8 // Led 
#define GreenR 9 // Led


void setup() {
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  pinMode(pump, OUTPUT);

  pinMode(GreenL, OUTPUT);
  pinMode(GreenR, OUTPUT);

  pinMode(Buzzer, OUTPUT);

  analogWrite(3, motor_speed);
  analogWrite(5, motor_speed);

  myservo.attach(11);
  myservo.write(0);
}


void put_off_fire() {
  delay(500);
  digitalWrite(pump,LOW);
  for (pos = -10; pos <= 60; pos += 1) {
    myservo.write(pos);
    delay(10);
    }
  for (pos = 60; pos >= -10; pos -= 1) {
    myservo.write(pos);
    delay(10);
    }
  if (digitalRead(Forward) == 0) {
    put_off_fire();
    }
  digitalWrite(pump,HIGH);
  myservo.write(30);
  fire=false;
}

long readUltrasonicDistance()
{
  pinMode(trigPin, OUTPUT);  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  
  return pulseIn(echoPin, HIGH);
}


void go_forward()
{
  digitalWrite(pump,HIGH);
  digitalWrite(GreenR, HIGH);
  digitalWrite(GreenL, HIGH);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void go_right(){
  digitalWrite(GreenR, HIGH);
  digitalWrite(GreenL, LOW);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
}

void go_left(){
  digitalWrite(GreenR, LOW);
  digitalWrite(GreenL, HIGH);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);

}

void go_back(){
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void stop(){
  digitalWrite(GreenR, HIGH);
  digitalWrite(GreenL, HIGH);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
}

void loop() {
  distance = 0.01723 * readUltrasonicDistance();
  myservo.write(30); //Sweep_Servo();
  

  if (digitalRead(Left) == 1 && digitalRead(Right)== 1 && digitalRead(Forward) == 1) {
    digitalWrite(pump,HIGH);
    digitalWrite(Buzzer, LOW);
    if (distance > 30){
      go_forward();
      delay(200);
      

    }
    else if (distance < 30){
      go_back();
      delay(700);
      go_right();
      delay(1300);
    }
  }

  else if (digitalRead(Left) == 0) {
    go_right();
    digitalWrite(Buzzer, HIGH);
  }

  else if (digitalRead(Right) == 0) {
    go_left();
    digitalWrite(Buzzer, HIGH);
  }

  else if (digitalRead(Forward) == 0) {
    go_forward();

    digitalWrite(Buzzer, HIGH);
    fire = true;
  }

  while (fire == true) {
    stop();
    put_off_fire();
  }
}
