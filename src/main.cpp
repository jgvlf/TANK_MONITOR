  #include <Arduino.h>
  #include <LiquidCrystal.h>
  LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
  #define LIGA 1
  #define LEDVE 8
  #define SNA 9
  #define MOTOR 10
  #define LEDVS 11
  #define SNB 12
  #define CLEANLED 13
  #define BUZZER 0

bool error = false;
int count = 0;

  void setup() {
    lcd.begin(16, 2);
    pinMode(LIGA, INPUT);
    pinMode(LEDVE, OUTPUT);
    pinMode(SNA, INPUT);
    pinMode(MOTOR, OUTPUT);
    pinMode(SNB, INPUT);
    pinMode(LEDVS, OUTPUT);
    pinMode(CLEANLED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    // put your setup code here, to run once:
  }

  void reset(){
    digitalWrite(LIGA, LOW);
    digitalWrite(LEDVE, LOW);
    digitalWrite(MOTOR, LOW);
    digitalWrite(LEDVS, LOW);
    digitalWrite(CLEANLED, LOW);
    digitalWrite(BUZZER, LOW);
  }

  void errorDisplay(){
    lcd.setCursor(5,0);
    lcd.print("ERROR!");
    digitalWrite(BUZZER, HIGH);
  }

  void turnOnMotorDisplay(){
    lcd.clear();
    digitalWrite(MOTOR, HIGH);
    for (int i = 5; i >= 0; i--)
    {
      lcd.setCursor(4,0);
      lcd.print("Agitando");
      lcd.setCursor(5,1);
      String timeStr = String(i);
      lcd.print(timeStr+" seg.");
      delay(1000);
    }
    lcd.clear();
    digitalWrite(MOTOR, LOW);
    outputValveDisplay();
    }

  void verifySNA(){
    if (digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)
        {
          lcd.clear();
          error = true;
          while (error)
          {
            errorDisplay();
            if (!(digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)){
              error = false;
              reset();
            }
          }
        }
      if(digitalRead(SNA) == HIGH && digitalRead(SNB) == HIGH || digitalRead(SNA) == LOW && digitalRead(SNB) == HIGH)
        {
          digitalWrite(LEDVE, LOW);
          turnOnMotorDisplay();
          count += 1;
        }
  }

  void verifySNB(){
    if (digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)
        {
          lcd.clear();
          error = true;
          while (error)
          {
            errorDisplay();
            if (!(digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)){
              error = false;
              reset();
            }
          }
          
        }
    if(digitalRead(SNB) == LOW && digitalRead(SNA) == LOW)
        {
          digitalWrite(LEDVS, LOW);
          lcd.clear();
        }
  }

  void inputValveDisplay(){
    if (digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)
        {
          lcd.clear();
          error = true;
          while (error)
          {
            errorDisplay();
            if (!(digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)){
              error = false;
              reset();
            }
          }
          
        }
    lcd.clear();
    while (digitalRead(SNA) == LOW)
    {
    lcd.setCursor(6,0);
    lcd.print("V.E.");
    lcd.setCursor(4,1);
    lcd.print("Acionada");
    digitalWrite(LEDVE, HIGH);
    }
    verifySNA();
  }

  void buttonLigaIsPressed(){
    if (digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)
        {
          lcd.clear();
          error = true;
          while (error)
          {
            errorDisplay();
            if (!(digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)){
              error = false;
              reset();
            }
          }
          
        }
    if(digitalRead(LIGA) == HIGH)
      {
          inputValveDisplay();
      }
  }


  void initialDisplay(){ //The inital message of programm
    lcd.setCursor(3,0);
    lcd.print("Pressione");
    lcd.setCursor(6,1);
    lcd.print("LIGA");
    buttonLigaIsPressed();
  }

  void outputValveDisplay(){
    if (digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)
        {
          lcd.clear();
          error = true;
          while (error)
          {
            errorDisplay();
            if (!(digitalRead(SNA) == HIGH && digitalRead(SNB) == LOW)){
              error = false;
              reset();
            }
          }
          
        }
    lcd.clear();
    while (digitalRead(SNB) == HIGH)
    {
    lcd.setCursor(6,0);
    lcd.print("V.S.");
    lcd.setCursor(4,1);
    lcd.print("Acionada");
    digitalWrite(LEDVS, HIGH);
    }
    verifySNB();
  }

  void cleanDisplay(){
    lcd.clear();
    for (int i = 3; i >= 0; i--)
    {
      lcd.setCursor(4,0);
      lcd.print("Limpando");
      lcd.setCursor(5,1);
      String timeStr = String(i);
      lcd.print(timeStr+" seg.");
      delay(1000);
    }
    digitalWrite(BUZZER, HIGH);
    delay(250);
    digitalWrite(BUZZER, LOW);
    delay(250);
    digitalWrite(BUZZER, HIGH);
    delay(250);
    digitalWrite(BUZZER, LOW);
    delay(250);
    digitalWrite(BUZZER, HIGH);
    delay(2000);
    digitalWrite(BUZZER, LOW);
    delay(2000);
    lcd.clear();
    count = 0;
  }

  void verifyClean(){
    if(count % 3 == 0 && count != 0){
      digitalWrite(CLEANLED, HIGH);
      cleanDisplay();
      digitalWrite(CLEANLED, LOW);
    }
  }

  void loop() {
    digitalWrite(BUZZER, LOW);
    initialDisplay();
    verifyClean();    
  }