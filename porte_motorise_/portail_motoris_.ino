#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Ultrasonic.h>

Servo myservo;
Ultrasonic ultrasonic(11, 12);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int ledV = 8;
int ledR = 7;
int buzzer = 2;
int distance = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledV, LOW);
  digitalWrite(ledR, LOW);
  digitalWrite(buzzer, LOW);
  distance = ultrasonic.read();
  Serial.print(distance);
  Serial.println("cm");

  if (distance < 15) {
    myservo.write(0);
    lcd.setCursor(0, 0);
    lcd.print("Portail ouvert  ");
    digitalWrite(ledV, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(1000);
  } else if (distance >= 15) {
    myservo.write(90);
    digitalWrite(ledR, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Portail ferme  ");
    delay(1500);  // Déplacer le délai ici pour éviter des délais inutiles
  }
}
