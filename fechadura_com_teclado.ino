#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define tamanho_senha 5

Servo myservo;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int pos = 0;

char Data[tamanho_senha];
char senhaCorreta[tamanho_senha] = "1803";
byte data_count = 0;
char customKey;


const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);



void setup() {
  myservo.attach(9, 2000, 2400);
  ServoClose();
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  lcd.begin(16, 2);
  lcd.print("Porta trancada");
  carregando("Carregando");
  lcd.clear();
}


void loop(){ abrir(); }

void carregando (char msg[]) {
  lcd.setCursor(0, 1);
  lcd.print(msg);

  for (int i = 0; i < 9; i++) {
    delay(1000);
    lcd.print(".");
  }
}

void clearData() {
  while (data_count != 0) Data[data_count--] = 0;
  return;
}

void ServoClose() {
  for (pos = 90; pos >= 0; pos -= 10) { 
    myservo.write(pos);
  }
}

void ServoOpen() {
  for (pos = 0; pos <= 90; pos += 10) {
    myservo.write(pos);  
  }
}

void abrir() {
  lcd.setCursor(0, 0);
  lcd.print("Digite a senha");
  
  customKey = customKeypad.getKey();
  if (customKey) {
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  if (data_count == tamanho_senha - 1) {
    if (!strcmp(Data, senhaCorreta)) {
      lcd.clear();
      ServoOpen();
      lcd.print("Porta destrancada");
      digitalWrite(13, HIGH);
  	  digitalWrite(12, LOW);
      delay(5000);
      carregando("Esperando");
      lcd.clear();
      lcd.print("Tempo expirado!");
      delay(1000);
      ServoClose();     
      digitalWrite(13, LOW);
  	  digitalWrite(12, HIGH);
      
    } else {
      lcd.clear();
      lcd.print("Senha errada");
    }
    delay(1000);
    lcd.clear();
    clearData();
  }
}