//Henry's Bench
//KY-031 Knock Sensor Tutorial

int knockPin = 4; // Use Pin 10 as our Input
int knockVal = HIGH; // This is where we record our shock measurement
boolean bAlarm = false;
int contador = 0;
int i = 0;

unsigned long lastKnockTime; // Record the time that we measured a shock


int knockAlarmTime = 500; // Number of milli seconds to keep the knock alarm high


void setup ()
{
  Serial.begin(9600);  
  pinMode (knockPin, INPUT) ; // input from the KY-031
}
void loop ()
{
  Serial.println("Nada Papi");
  checkSensor();
 
}

void checkSensor()
{
  knockVal = digitalRead (knockPin) ; // read KY-031 Value
  if (knockVal == LOW) // If we see a knock
  {
    contador = 1;
    while(i<80)
    {
      Serial.print(i);
       Serial.print(" While: Cont = ");
       Serial.println(contador);
       if (digitalRead (knockPin) == LOW) contador += 1;
       //delay(15);
       i++;
    }
    i=0;
  }
  
  if(contador >= 7)
      {
        Serial.println("madres........");
        digitalWrite(5,HIGH);
        delay(5000);
        contador =0;
        digitalWrite(5,LOW);
      }
}

