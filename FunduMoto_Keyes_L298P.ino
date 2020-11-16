/*Exemplo controlador de velocidade shield FunduMoto Keyes_L289P
*
* Este exemplo foi feito por Maxson C. Maidlinger
* Nele é mostrado como: 
* Utilisar o Serial read para montar comandos e utilizar como Debug ou com o modulo Bluetooth
* Controlar dois motores continuos por meio do PWM (Pulse Width Modulation)
* Utilizar a saida para o servo motor
* Utilizar o buzzer
*/
#include <Servo.h>

int servo = 9;
int Buzzer = 4;
int E1 = 10;// pino digital PWM
int M1 = 12;// pino digital
int E2 = 11;// pino digital PWM
int M2 = 13;// pino digital                    

char command;
String string;
Servo myservo;

void setup() 
{ 
    Serial.begin(9600);   // aber a porta serial e define a velocidade em 9600 bps
    pinMode(Buzzer, OUTPUT);
    pinMode(M1, OUTPUT);  //define pino como saída
    pinMode(M2, OUTPUT);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
    myservo.attach(servo);
    Serial.write("\nSETUP finalizado");
    tone(Buzzer, 1000, 250);
    delay(250);
    tone(Buzzer, 1500, 250);
} 
 
void loop() 
{ 
  while(Serial.available() > 0)
  {
    command = (Serial.read());
    
    if(command == ':')
    {
        break;
    }
    else
    {
        string += command;
    }
    delay(10);
  }
  
  if (string.length() > 0 ){
    string.toUpperCase();
    if ( string == "FRENTE" ){
        Serial.write("\nFrente");
        frenteTotal();
    } else if (string == "TRAS"){
        Serial.write("\nTras");
        trasTotal();
    } else if (string == "DIREITA"){
        Serial.write("\nGirar Horario");
        girarHorario();
    } else if (string == "ESQUERDA"){
        Serial.write("\nGirar Anti-Horario");
        girarAnteHorario();
    } else if (string == "PARAR"){
        Serial.write("\nParar");
        parar();
    } else if (string.substring(0,1) == "V"){       
       Serial.write("\nServo em ");
       Serial.print(string.substring(1).toInt());
       myservo.write(string.substring(1).toInt());
    } else {
        
        tone(Buzzer, 200, 250);        
        delay(500);
        tone(Buzzer, 500, 250);
        delay(250);        
        Serial.print((String)"\nComando não encontrado: ");        
        Serial.print(string);
        
    }
    string = "";
    delay(20);
  }
}

void parar(){
    digitalWrite(M1, LOW);   
    digitalWrite(M2, LOW);
    digitalWrite(E1, LOW);   
    digitalWrite(E2, LOW);
}
void frenteTotal(){
    digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 255);   //Controle de velocidade por PWM
    analogWrite(E2, 255);   //Controle de velocidade por PWM
}

void trasTotal(){
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 255);   //Controle de velocidade por PWM
    analogWrite(E2, 255);   //Controle de velocidade por PWM
}

void girarHorario(){
    digitalWrite(M1,LOW);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, 255);   //Controle de velocidade por PWM  //255 para maximo
    analogWrite(E2, 255);   //Controle de velocidade por PWM // 0 para minimo
}

void girarAnteHorario(){
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, 255);
    analogWrite(E2, 255);
}

