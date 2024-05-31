// Include Library LCD
#include <LiquidCrystal_I2C.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal_I2C lcd(rs, en, d4, d5, d6, d6, d7);

// HC-SR04 UltraSonic Sensor Pins Declaration
const int trigPin = 13;
const int echoPin = 9;
long time_duration;
int distanceCM;

// Red and Green LED's
const int RedLed = 7;
const int GreenLed = 8;

// Piezzo Buzzer
const int buzzer = 6;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(RedLed, LOW);
  digitalWrite(GreenLed, LOW);
  tone(0, buzzer);
}

void loop() {
  // put your main code here, to run repeatedly:
  UltrasonicSensor();
  
  if (distanceCM < 30){
    lcd.setCursor(0,0);
    lcd.print("For Protection!");
    lcd.setCursor(0,1);
    lcd.print("Avoid Immediately!");
    digitalWrite(RedLed, HIGH);
    digitalWrite(GreenLed, LOW);
    tone(16000, buzzer, 500);
  }
  else if (distanceCM >= 30 && distanceCM <= 40){
    lcd.setCursor(0,0);
    lcd.print("Approaching Person!");
    lcd.setCursor(0,1);
    lcd.print("Avoid Immediately!");
    digitalWrite(RedLed, HIGH);
    digitalWrite(GreenLed, LOW);
    tone(16000, buzzer, 1500);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("I'm Safe!");
    lcd.setCursor(0,1);
    lcd.print("Yehey!");
    digitalWrite(RedLed, LOW);
    digitalWrite(GreenLed, HIGH);
  }
}

void UltrasonicSensor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time_duration = pulseIn(echoPin, HIGH);
  distanceCM = time_duration * 0.034 / 2;
}
