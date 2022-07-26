#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_Length 8 

int signalPin = 12;
int Buzzer = 11;
int tempoBuzzer = 50;

char Data[Password_Length]; 
char Master[Password_Length] = "855A855"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27,20,4);

void setup(){
  lcd.init(); 
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop(){

  lcd.setCursor(0,0);
  lcd.print("Digite a senha:");

  customKey = customKeypad.getKey();

  if (customKey !=0){
    digitalWrite(Buzzer, HIGH);
    delay(tempoBuzzer);
    digitalWrite(Buzzer, LOW);
  }
  
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.print("Senha correta!");
      digitalWrite(signalPin, HIGH); 
      digitalWrite(Buzzer, HIGH);
      delay(tempoBuzzer*25);
      digitalWrite(Buzzer, LOW);
      digitalWrite(signalPin, LOW);
      }
    else{
      lcd.print("Senha incorreta!");
      digitalWrite(Buzzer, HIGH);
      delay(tempoBuzzer);
      digitalWrite(Buzzer, LOW);
      delay(1000);
      }
    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
