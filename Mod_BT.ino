#include <SoftwareSerial.h>


//PINES
int knockPin = 3; //Pin que recibirá la señal del senor de choque
int contador = 0;
int i = 0;        //Contador
int LED = 2;      //LED que muestra la activación de la alarma
const byte TXpin = 5;
const byte RXpin = 4;
int text;
bool Alerta = false;

SoftwareSerial miBT(RXpin, TXpin);

void setup ()
{
  Serial.begin(9600);  
  pinMode (knockPin, INPUT) ; // Pin del seonsor KY-031 como entrada
  //miBT.begin(38400);
  miBT.begin(9600);
  Serial.println("LISTO");
}

void loop ()
{ 
  
  if(miBT.available())
  {
    text = miBT.read();
    Serial.write(text);
  }
  
  if(text == 49)
  {
    miBT.write("ON#");
    if(Alerta == false)
    {
      checkSensor();
    }
  }
  
  if(text == 48)
  {
     miBT.write("OFF#");
     Alerta = false;
  }
  
  
  if(Serial.available())
  {
    miBT.write(Serial.read());
  }
  
//  if(text == 49)
//  {
//    Serial.println("YES");
//    digitalWrite(LED,HIGH);
//    miBT.write("ALERTA#");
//    delay(2000);
//  }
//  else
//  {
//    Serial.println("NEL");
//    digitalWrite(LED,LOW);
//  }
 
}

void checkSensor()
{
  if (digitalRead (knockPin) == LOW) // SI se activa el sensor
  {
    contador = 1;
    while(i<80) //Tiempo de espera para recibir mas activaciones o descartar por falsa alarma
    {
      Serial.print(i);
      Serial.print(" While: Cont = ");
      Serial.println(contador);
      if (digitalRead (knockPin) == LOW) contador += 1; //Si se activa sensor se aumentara un contador
      i++;
    }
    i=0;
  }
  
  if(contador >= 7) //Si el sensor se activo repetidamente, activa la alarma
  {
    Serial.println("madres........");
    //delay(5000);
    contador = 0;
    miBT.write("ALERTA#");
    Alerta = true;
  }
}
