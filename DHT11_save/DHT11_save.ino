#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <stdio.h>

const uint8_t DHT11PIN =14;

unsigned long long lastMs=0;
unsigned long long lastUs=0;
unsigned long long lastMMs=0;
unsigned long long lastUUS=0;
unsigned long long startUUS=0;
int cnt[33]={0,};
int readTemp=0;
int readHumid=0;
int t=0;
void setup()
{
   Serial.begin(115200);
   
   
}


ICACHE_RAM_ATTR void ReadytoRead()
{
  // Serial.printf("This Interrupt 1\r\n");
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), GO, RISING);
   
}
ICACHE_RAM_ATTR void GO()
{
 //   Serial.printf("This Interrupt 2\r\n");
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), DataCollector, FALLING);
  
}

ICACHE_RAM_ATTR void DataCollector()
{
 // Serial.printf("This Interrupt 3\r\n");

    attachInterrupt(digitalPinToInterrupt(DHT11PIN), GetData, RISING);
    readHumid=0;
    readTemp=0;
    t=0;

}

ICACHE_RAM_ATTR void GetData()
{ 
 //Serial.printf("This Interrupt 4\r\n");
//Serial.printf("cnt = %d, dt=[%d]\r\n",t, cnt[t]);
 
  if(t<32)
  {
    Serial.printf("Humid : %d   t : %d \r\n", readHumid, t);
  lastUs=micros();
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), Get, FALLING);
 // attachInterrupt(digitalPinToInterrupt(DHT11PIN), Timecollectorstart, FALLING);
  //cnt[t]=lastUUS-startUUS;
  } 
}

ICACHE_RAM_ATTR void  Get()
{
 
 if(t<8){
  readHumid = readHumid<<1;
  if(micros()-lastUs>50)
    {
      cnt[t]=micros()-lastUs;
      //readHumid = readHumid +1;
      t=t+1;
      attachInterrupt(digitalPinToInterrupt(DHT11PIN), GetData, RISING);
    }
  else
  {
    cnt[t]=micros()-lastUs;
   // readHumid = readHumid +0;
     t=t+1;
      
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), GetData, RISING);
  }
}
 if((t>15)&&(t<24))
 {
  readTemp = readTemp<<1;
  if(micros()-lastUs>50)
    {
      readTemp = readTemp +1;
      
      attachInterrupt(digitalPinToInterrupt(DHT11PIN), GetData, RISING);
    }
  else
  {
      readTemp = readTemp +0;    
     
    attachInterrupt(digitalPinToInterrupt(DHT11PIN), GetData, RISING);
  }
 }
   
 if(((t>23)&&(t<32))||((t>7)&&(t<16)))
 {
   t++;
   return;
 }
 
 
}


void loop() {
    
  digitalWrite(DHT11PIN, 1);
   pinMode(DHT11PIN, OUTPUT);
   digitalWrite(DHT11PIN, 0);
   delay(20);
   pinMode(DHT11PIN, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), ReadytoRead, FALLING);
  //Serial.printf("Humid : %d,  Temp : %d,   t : %d \r\n", readHumid, readTemp, t);
 
   
}
