#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>

int R = 13;
int G = 12;
int B = 11;

LiquidCrystal_I2C display(0x27, 16,  2);

byte linhas_teclado[4] = {2, 3, 4, 5};
byte colunas_teclado[4] = {A0, A1, A2, A3};

char teclas[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad teclado = Keypad(makeKeymap(teclas), linhas_teclado, colunas_teclado, 4, 4);

const String senha = "123D";
String senha_comp = "";


bool confirma_senha(String str){
  return (str == senha);
}

void setup(){

  Serial.begin(9600);
  Wire.begin();

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  display.begin(16, 2);
  display.backlight();
  display.clear();

  display.setCursor(5,0);
  display.print("Ola :)");
  delay(500);
  display.clear();

}

void loop(){

  char scan_teclado = teclado.getKey();

  display.setCursor(0,0);
  display.print("Insira a senha:");

  if(scan_teclado != NO_KEY){
    
    if(scan_teclado != '*' && scan_teclado != '#'){
      senha_comp += scan_teclado;
      display.setCursor(senha_comp.length() -1, 1);
      display.print(scan_teclado);
      analogWrite(R, 0);
      analogWrite(G, 0);
      analogWrite(B, 255);
      Serial.println(senha_comp);
    }

    else if(scan_teclado == '*'){
      if(senha_comp.length() > 0){
        
        analogWrite(B, 0);

        if(confirma_senha(senha_comp)){
          senha_comp.remove(0, senha_comp.length());
          display.setCursor(0,0);
          display.clear();
          display.print("SENHA CORRETA!");
          analogWrite(G, 255);
          delay(2500);
        }

        else {
          
            senha_comp.remove(0, senha_comp.length());
            display.setCursor(0,0);
            display.clear();
            display.print("SENHA INCORRETA!");
            analogWrite(R, 255);
            delay(2500);
            display.clear();
          
        } 
      }  
    }
      
    if (scan_teclado == '#')
      if (senha_comp.length() > 0) {
          display.clear();
          senha_comp.remove((senha_comp.length() -1), 1);
          display.setCursor(0, 1);
          display.print(senha_comp);
          Serial.println(senha_comp);
      }

    if(senha_comp.length() == 0){
      analogWrite(R, 143);
      analogWrite(G, 0);
      analogWrite(B, 255);
    }
  }
}