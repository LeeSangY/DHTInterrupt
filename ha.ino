#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <stdio.h>

const uint8_t DHT11PIN =14;

unsigned long long lastMs=0;
unsigned long long lastUs=0;
unsigned long long lastMMs=0;
unsigned long long lastUUs=0;
unsigned long long startUs=0;
int cnt[40]={0,};
int readTemp=0;
int readHumid=0;
int t=0;
int n=0;
void setup()
{
   Serial.begin(74880);
   
   
}

ICACHE_RAM_ATTR void ReadytoRead()
{
   Serial.printf("This Interrupt 1\r\n");
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), DataCollector, RISING);
   
}
/*
ICACHE_RAM_ATTR void GO()
{
 //   Serial.printf("This Interrupt 2\r\n");
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), ZeroCollector, FALLING);
   cnt[t] = lastUUs-lastUs;
   
}

ICACHE_RAM_ATTR void ZeroCollector()
{
  lastUs=micros();
   Serial.printf("lastUs= %d\r\n",lastUs);
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), Zero1Collector, RISING);
 return;
}

ICACHE_RAM_ATTR void Zero1Collector()
{
  Serial.printf("lastUUs= %d\r\n",lastUUs);
  lastUUs=micros();
  return;
}*/
ICACHE_RAM_ATTR void DataCollector()
{
  Serial.printf("This Interrupt 1\r\n");
  if(t<40)
  {
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), Data1Collector, FALLING);
  startUs = micros();
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), Data2Collector, RISING);
  lastUs = micros();
  attachInterrupt(digitalPinToInterrupt(DHT11PIN), Data3Collector, FALLING);
  lastUUs = micros();
   cnt[t] = lastUUs-lastUs;
   cnt[n] = lastUs-startUs;
   t++;
   n++;
   Serial.printf("[cnt[%d].cnt[%d] = [%d, %d]\r\n",t,n,cnt[t],cnt[n]);
    if(t=40)
    {
      attachInterrupt(digitalPinToInterrupt(DHT11PIN), ReadytoRead, FALLING);
      t=0;
      n=0;
    }
  }
}
ICACHE_RAM_ATTR void Data1Collector()
{
  return;
}
ICACHE_RAM_ATTR void Data2Collector()
{
  return;
}
ICACHE_RAM_ATTR void Data3Collector()
{
  return;
}
void loop()
{
   digitalWrite(DHT11PIN, 1);
   pinMode(DHT11PIN, OUTPUT);
   digitalWrite(DHT11PIN, 0);
   delay(20);
   pinMode(DHT11PIN, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(DHT11PIN), ReadytoRead, FALLING);
  
}
