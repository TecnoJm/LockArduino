#include <SoftwareSerial.h>

#include <LiquidCrystal.h> 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); 
#include <Keypad.h>
#include <Password.h>
Password Pass = Password("13579"); 

const byte ROWS = 4;
byte sensorpin = A4;
int dato = 0;
bool V = false;
const byte COLS = 4;
int Buzzer = 12;
int intentos = 0;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { A0,A1,A2,A3 };
byte colPins[COLS] = { 8,9,10,11 };

Keypad teclado = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() { 
  delay(500);
  pinMode(Buzzer,OUTPUT);
  pinMode(sensorpin,INPUT);  
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("P");
  delay(100);
  lcd.print("o");
  delay(100);
  lcd.print("n");
  delay(100);
  lcd.print("g");
  delay(100);
  lcd.print("a");
  delay(100);
  lcd.print(" e");
  delay(100);
  lcd.print("l");
  delay(100);
  lcd.print(" P");
  delay(100);
  lcd.print("i");
  delay(100);
  lcd.print("n:");
  delay(100); 
  lcd.setCursor(0,1);
  teclado.addEventListener(tecladoEvent);  
}

void loop() {   
teclado.getKey();

if (V == true)
{
  if (digitalRead(sensorpin) == HIGH)
  {  
  tone(Buzzer,200);
  Serial.write("A");
  }
}
}

 void tecladoEvent(KeypadEvent eKey){
  switch (teclado.getState()){
    case PRESSED:
   lcd.print("*");
   //
    switch (eKey){
    case '*': checkPassword(); break;
    case '#': Pass.reset(); lcd.clear(); lcd.print("Ponga el Pin:"); lcd.setCursor(0,1); break;
    case 'D': Serial.flush(); Serial.end(); Serial.begin(9600); Serial.write("D"); Serial.flush(); Serial.end();  lcd.clear(); noTone(Buzzer); V = false; lcd.print("Desactivado"); Pass.reset(); delay(5000); lcd.clear(); lcd.print("Ponga el Pin:"); lcd.setCursor(0,1); break;
    default:  Pass.append(eKey);
     }
  }
}

void checkPassword(){
  if (Pass.evaluate()){
  lcd.clear();
  lcd.print("    Correcto");
  tone(Buzzer,440);
  delay(500);
  noTone(Buzzer);
  lcd.setCursor(0,1);
  delay(3000);
  lcd.clear();
  intentos = 0;
  V = true;
  Serial.begin(9600);
  }
  
  else{
  lcd.clear();
  tone(Buzzer,200);
  delay(100);
  noTone(Buzzer);
  lcd.print("   Incorrecto");
  intentos = intentos + 1;
  delay(800);
  lcd.setCursor(0,1);
  lcd.print("Limpiando...");
  delay(3000);
  lcd.clear();

  lcd.print("Ponga el Pin:"); 
  lcd.setCursor(0,1);
  Pass.reset();

  if (intentos > 2)
{
  lcd.clear();
  lcd.print("Excedio el N#");
  lcd.setCursor(0,1);
  lcd.print("de intentos");
  delay(2000);
  lcd.clear();
  lcd.print("Espere");
  lcd.setCursor(0,1);

  for (int i = 10; i!=0; i--)
  {
lcd.print(i); 
lcd.print(" segundos");
delay(1000);
lcd.clear();
lcd.print("Espere");
lcd.setCursor(0,1);
  }
  intentos = 0;
  
  lcd.clear();
  lcd.print("Ponga el Pin:");
  lcd.setCursor(0,1);
  }
}
}

