#include "BluetoothSerial.h"

/* 
- Mover para a frente: entrada = 1
- Mover pra trás: entrada = 2
- Parar totalmente: entrada = 3
- Mover 90° à esquerda: entrada = 4
- Mover 90° à direita: entrada = 5
*/

BluetoothSerial SerialBT;

char comando, comando_anterior;

int in1 = 22;
int in2 = 23;
int in3 = 16;
int in4 = 17;

int velocidade = 0;
int velocidade_back = 0;

void setup(){
  Serial.begin(115200);

  SerialBT.begin("Carrinho"); 
  Serial.println("Bluetooth iniciado. Pronto para emparelhar!");

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop(){

  if(Serial.available()) {
    SerialBT.write(SerialBT.read());
  }
  
  if(SerialBT.available()){

    comando = (char)SerialBT.read();

    //Forward

      //Acelera
    if(comando == '1' && velocidade >= 0){
      if(velocidade < 255)
        velocidade += 10;

      Serial.printf("Velocidade: %d\n", velocidade);
      Serial.printf("velocidade_back: %d\n\n", velocidade_back);

      digitalWrite(in1, velocidade);
      digitalWrite(in2, LOW);
      digitalWrite(in3, velocidade);
      digitalWrite(in4, LOW);
      delay(500);
    }

      //Desacelera
    else if(comando == '2' && velocidade > 0){
      if(velocidade > 0){
        velocidade -= 10;
        velocidade_back = 0;
      }

        Serial.printf("Velocidade: %d\n", velocidade);
        Serial.printf("velocidade_back: %d\n\n", velocidade_back);

        digitalWrite(in1, velocidade);
        digitalWrite(in2, LOW);
        digitalWrite(in3, velocidade);
        digitalWrite(in4, LOW);
        delay(500);
    }

    //Backward

      //Acelera
    if(comando == '2' && velocidade_back >= 0){
      if(velocidade_back < 255)
        velocidade_back += 10;

      Serial.printf("Velocidade: %d\n", velocidade);
      Serial.printf("velocidade_back: %d\n\n", velocidade_back);

      digitalWrite(in1, velocidade_back);
      digitalWrite(in2, LOW);
      digitalWrite(in3, velocidade_back);
      digitalWrite(in4, LOW);
      delay(500);
    }

      //Desacelera 
    else if(comando == '1' && velocidade_back > 0){
      if(velocidade_back > 0){
        velocidade_back -= 10;
        velocidade = 0;
      }

        Serial.printf("Velocidade: %d\n", velocidade);
        Serial.printf("velocidade_back: %d\n\n", velocidade_back);

        digitalWrite(in1, velocidade_back);
        digitalWrite(in2, LOW);
        digitalWrite(in3, velocidade_back);
        digitalWrite(in4, LOW);
        delay(500);
    }

    //Girar 90° à esquerda
    else if(comando == '4'  && (velocidade - velocidade_back) != 0){
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, abs(velocidade - velocidade_back));
      digitalWrite(in4, LOW);

      Serial.printf("abs: %d\n", abs(velocidade - velocidade_back));
      delay(3000);

      if(velocidade > 0){
        digitalWrite(in1, velocidade);
        digitalWrite(in2, LOW);
        digitalWrite(in3, velocidade);
        digitalWrite(in4, LOW);
        delay(500);
      }

      else if(velocidade_back > 0){
        digitalWrite(in1, velocidade_back);
        digitalWrite(in2, LOW);
        digitalWrite(in3, velocidade_back);
        digitalWrite(in4, LOW);
        delay(500);
      }

    }

    //Girar 90° à direita
    else if(comando == '5' && (velocidade - velocidade_back) != 0){
      digitalWrite(in1, abs(velocidade - velocidade_back));
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);

      Serial.printf("abs: %d\n", abs(velocidade - velocidade_back));
      
      delay(3000);

      if(velocidade > 0){
        digitalWrite(in1, velocidade);
        digitalWrite(in2, LOW);
        digitalWrite(in3, velocidade);
        digitalWrite(in4, LOW);
        delay(500);
      }

      else if(velocidade_back > 0){
        digitalWrite(in1, velocidade_back);
        digitalWrite(in2, LOW);
        digitalWrite(in3, velocidade_back);
        digitalWrite(in4, LOW);
        delay(500);
      }

    }

    //Parar
    else if(comando == '3' || (velocidade == 0 && velocidade_back == 0)){
      velocidade = 0;
      velocidade_back = 0;

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500);
    }
  }

  delay(50);
}

void Forward(char comando){
  
}
