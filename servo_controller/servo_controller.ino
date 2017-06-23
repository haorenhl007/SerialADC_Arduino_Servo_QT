#include <Servo.h>

/*
CENTRO DE TECNOLOGIA AVANZADA (CIATEQ)
MAESTRIA EN SISTEMAS INTELIGENTES MULTIMEDIA
DOCENTE: DR HECTOR HUGO
ALUMNO: FRANCISCO JAVIER PEDRAZA GONZALEZ
*/
Servo servo;
const int pinPot = 0;
const int pinServo = 2;
const int pulsoMin = 650;  //pulse to turn the servo to 0 degrees.
const int pulsoMax = 2550; // pulse to turn the servo to 180 degrees.

int valor;
int angulo;

void setup()
{
  Serial.begin(9600);
  servo.attach(pinServo, pulsoMin, pulsoMax);
  // Las entradas analogicas se configuran automaticamente
}

void loop()
{
  if(Serial.available()>0)
  {
    char DatoSerial = Serial.read();
    if(DatoSerial == 'a')
    {
      int LecturaADC = analogRead(A0);
      Serial.write(LecturaADC>>8);
      Serial.write(LecturaADC);
      valor = analogRead(pinPot);            // read the pot value
      angulo = map(valor, 0, 1023, 0,  180); // conver the ange value
      servo.write(angulo);                   // Move the servo to the desired angle
      //delay(20);    // Allows to the servo to arrive 
      Serial.println(angulo);
      Serial.println(valor);
      }
     
    }
  }
