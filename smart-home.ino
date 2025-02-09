#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12
#define D13 13

const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
 
const char hexaKeys[ROWS][COLS] = {
  {'a','b','c','d'},
  {'e','f','g','h'},
  {'i','j','k','l'},
  {'m','o','p','q'}
};

LiquidCrystal_I2C lcd(0x27, 16, 2);

class MapForKeys {
  public: 
    const char* const Info[16] = 
    {
      "A - first letter", 
      "B - second letter", 
      "C - C++)", 
      "D - Debil"
    };  

    void getInfoAtKey(char key) {
      switch(key) {
        case 'a':
          lcd.print(Info[0]);
          break;
        case 'b':
          lcd.print(Info[1]);
          break;
        case 'c':
          lcd.print(Info[2]);
          break;
        case 'd':
          lcd.print(Info[3]);
          break;
      }
    }
};

const byte rowPins[ROWS] = {D5, D4, D3, D2}; // цифровые выводы строк 
const byte colPins[COLS] = {D6, D7, D8, D9}; // цифровые выводы столбцов 

Keypad customKeypad = Keypad(*hexaKeys, colPins, rowPins, COLS, ROWS);  
 
void setup(){
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D12, OUTPUT);
  pinMode(D13, INPUT);

  digitalWrite(D11, LOW);

  Serial.begin(9600);

  lcd.begin();
} 

bool isTaken = false;
bool active = false;

int counter = 0;

MapForKeys keysMap;
 
void loop(){
  if(digitalRead(D13) == HIGH && !isTaken) {
    counter = counter + 1;
    
    if(counter % 2 == 1) {
      lcd.backlight();
    } else {
      lcd.noBacklight();
    }

    isTaken = true;
  }

  if(digitalRead(D13) == LOW) {
    isTaken = false;
  }

  char customKey = customKeypad.getKey(); 
  if (customKey){
    lcd.clear();
    
    keysMap.getInfoAtKey(customKey);
  }

  digitalWrite(D11, LOW);
  shiftOut(D12, D10, LSBFIRST, 0b01000000);
  digitalWrite(D11, HIGH);
}