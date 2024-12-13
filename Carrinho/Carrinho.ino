#include "BluetoothSerial.h"

/* 
- Mover para a frente: entrada = 1
- Mover para trás: entrada = 2
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

int in1 = 26; // Motor 1 Esquerda Frontal Verde
int in2 = 27; // Motor 1 Roxo
int in3 = 32; // Motor 2 Direita Frontal Marrom Claro
int in4 = 33; // Motor 2 Marrom Escuro
int in5 = 16; // Motor 3 Esquerda Traseira Amarelo
int in6 = 17; // Motor 3 Branco
int in7 = 18; // Motor 4 Direita Traseira Laranja
int in8 = 19; // Motor 4 Marrom Escuro

int velocidade = 250;

void setup() {
    Serial.begin(115200);
    SerialBT.begin("M.T.E.X"); 
    Serial.println("Bluetooth Ativo");

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(in5, OUTPUT);
    pinMode(in6, OUTPUT);
    pinMode(in7, OUTPUT);
    pinMode(in8, OUTPUT);
   

    pararMotores();
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
}

void loop() {
    if (Serial.available()) {
        SerialBT.write(SerialBT.read());
    }

    if (SerialBT.available()) {
        comando_anterior = comando;
        comando = (char)SerialBT.read();

        switch (comando) {
            case '1': // Mover para frente
                if(comando_anterior == '2'){
                  pararMotores();
                  delay(50);
                }

                moverFrente();
                break;

            case '2': // Mover para trás
                if(comando_anterior == '1'){
                  pararMotores();
                  delay(50);
                }
                moverTras();
                break;

            case '3': // Parar
                if(comando_anterior != '3'){
                  pararMotores();
                  delay(50);
                }
                break;

            case '4': // Mover Lado a esquerda 
                if(comando_anterior != '4'){
                  pararMotores();
                  delay(50);
                  andarLadoEsq();
                }
                break;

            case '5': // Mover Lado a direita
              if(comando_anterior != '5'){
                  pararMotores();
                  delay(50);
                  andarLadoDir();
              }
                break;

            case '6': //Girar a Esquerda
              if(comando_anterior != '6'){
                pararMotores();
                delay(50);
                girarEsquerda();
              }
                break;

            case '7': //Girar a Direita
              if(comando_anterior != '7'){
                pararMotores();
                delay(50);
                girarDireita();
              }
                break;

            case '8': //Diagonal Direita Triangulo
              if(comando_anterior != '8'){
                pararMotores();
                delay(50);
                moverDiagonalDirFrente();
              }
                break;

            case '9': //Diagonal Esquerda X
              if(comando_anterior != '9'){
                pararMotores();
                delay(50);
                moverDiagonalEsqFrente();
              }
                break;
              

            /*case '6': // Buzina
                if (!buzinaAtiva) {
                    buzinaAtiva = true;
                    tocarNota(440);
                } else {
                    buzinaAtiva = false;
                    pararNota();
                }
                break;

            case '7': // LED3
                led3Aceso = !led3Aceso;
                digitalWrite(LED3_PIN, led3Aceso ? HIGH : LOW);
                break;*/

              
        }
    }

    delay(50);
}

// Funções de controle dos motores
void moverFrente() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);

    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
    
}

void moverTras() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);

    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
    
}

//Gira no proprio eixo à esquerda
void girarEsquerda() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);

    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
    
}

//Gira no proprio eixo à direita
void girarDireita() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);

    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);

}

//Andar de Lado à esquerda
void andarLadoEsq() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);

    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
    
}

void andarLadoDir() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);

    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);

}

void pararMotores() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);

    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);
    
}

void moverDiagonalEsqFrente(){

    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    digitalWrite(in5, LOW); // Frente Esquerda
    digitalWrite(in6, HIGH);

    digitalWrite(in7, LOW); // Frente Direita
    digitalWrite(in8, LOW);
    
}

/*void moverDiagonalEsqBack(){

    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    digitalWrite(in5, LOW); 
    digitalWrite(in6, HIGH);

    digitalWrite(in7, LOW); 
    digitalWrite(in8, LOW);
    
}*/

void moverDiagonalDirFrente(){

    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    digitalWrite(in5, LOW); 
    digitalWrite(in6, LOW);

    digitalWrite(in7, LOW); 
    digitalWrite(in8, HIGH);
    
}

/*void moverDiagonalDirBack(){

    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    digitalWrite(in5, HIGH); // Frente Esquerda
    digitalWrite(in6, LOW);

    digitalWrite(in7, LOW); // Frente Direita
    digitalWrite(in8, LOW);
    
}*/

// Funções do buzzer
void tocarNota(int frequencia) {
    tone(BUZZER_PIN, frequencia);
}

void pararNota() {
    noTone(BUZZER_PIN);
}
