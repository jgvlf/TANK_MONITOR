#include <Arduino.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#define LIGA 1
#define LEDVE 8
#define SNA 9
#define MOTOR 10


void setup() {
  lcd.begin(16, 2);
  pinMode(LIGA, INPUT);
  pinMode(LEDVE, OUTPUT);
  pinMode(SNA, INPUT);
  pinMode(MOTOR, OUTPUT);
  // put your setup code here, to run once:
}

void inputValveDisplay(){
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("V.E.");
  lcd.setCursor(4,1);
  lcd.print("Acionada");
  digitalWrite(LEDVE, HIGH);
  while (true)
  {
    delay(1000);
  }
}

void buttonLigaIsPressed(){
  if(digitalRead(LIGA) == HIGH && digitalRead(SNA) == LOW)
    {
      
      inputValveDisplay();
    }
}


void initialDisplay(){ //The inital message of programm
  lcd.setCursor(3,0);
  lcd.print("Pressione");
  lcd.setCursor(6,1);
  lcd.print("LIGA");
}

void loop() {
  initialDisplay();
  buttonLigaIsPressed();
}