#include "BluetoothSerial.h"

/* 
- Mover para a frente: entrada = 1
- Mover pra trás: entrada = 2
- Parar totalmente: entrada = 3
- Mover à esquerda: entrada = 4
- Mover à direita: entrada = 5
- Ligar Buzzer: entrada = 6
- Acender LED Frontal: entrada = 7
*/

BluetoothSerial SerialBT;

#define BUZZER_PIN 12    
#define LED3_PIN 14    
int LED1_PIN = 13;        
int LED2_PIN = 25;               

bool buzinaAtiva = false;   // Estado atual da buzina
bool led3Aceso = false;     // Controle do LED3 (liga/desliga)

char comando, comando_anterior;

int in1 = 26; //Verde
int in2 = 27; //Amarelo
int in3 = 32; //Azul
int in4 = 33; //Laranja

int velocidade = 250;

void setup(){
    Serial.begin(115200);
    SerialBT.begin("Carrinho"); 
    Serial.println("Bluetooth Ativo");

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
}

void loop(){
  if(Serial.available()){
    SerialBT.write(SerialBT.read());
  }
  
  if(SerialBT.available()){
    comando_anterior = comando;
    comando = (char)SerialBT.read();

    if(comando == '1'){ // Mover para frente
      if(comando_anterior == '2'){
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        delay(500);
      }

        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);

      digitalWrite(in1, velocidade);
      digitalWrite(in2, LOW);
      digitalWrite(in3, velocidade);
      digitalWrite(in4, LOW);
    } 
    
    else if(comando == '2'){ // Mover para trás
      if(comando_anterior == '1'){
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        delay(500);
      }

        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);

      digitalWrite(in1, LOW);
      digitalWrite(in2, velocidade);
      digitalWrite(in3, LOW);
      digitalWrite(in4, velocidade);
    }
    
    else if(comando == '4'){ // Mover à esquerda
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(50);

      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, LOW);

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, velocidade);
      digitalWrite(in4, LOW);
    } 
    
    else if(comando == '5'){ // Mover à direita
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(50);

      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, HIGH);

      digitalWrite(in1, velocidade);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    } 

    
    else if(comando == '3'){ // Parar

      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500);
    }

    // Controle da buzina e LEDs adicionais
    switch(comando){
      case '6': // Buzina
        if(!buzinaAtiva){
          buzinaAtiva = true;
          tocarNota(440);
        } 
        
        else{
          buzinaAtiva = false;
          pararNota();
          tocarBuzinaEstilizada();
        }

        break;
            
      case '7': // LED3
        led3Aceso = !led3Aceso;
        digitalWrite(LED3_PIN, led3Aceso ? HIGH : LOW);
        break;
    }
  }

    delay(50);
}

// Funções do buzzer
void tocarBuzinaEstilizada(){
  tocarNotaTemporaria(440, 120);
  tocarNotaTemporaria(554, 120);
  tocarNotaTemporaria(659, 150);
  tocarNotaTemporaria(554, 120);
  tocarNotaTemporaria(440, 300);
}

void tocarNotaTemporaria(int frequencia, int duracao){
  tocarNota(frequencia);
  delay(duracao);
  pararNota();
  delay(20);
}

void tocarNota(int frequencia){
  tone(BUZZER_PIN, frequencia); // Emite som com a frequência escolhida
}

void pararNota(){
  noTone(BUZZER_PIN); // Parar o som do buzzer
}
