#include <Wire.h>
#include<Servo.h>
Servo myservo;
Servo myservo1;
Servo myservo2;
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN D3
DHT dht(DHTPIN, DHTTYPE);
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL6zqNdTRV"
#define BLYNK_DEVICE_NAME "moisture"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG


#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
 
#define pump D6
//#define servo D7
int f=0,f1=0,f2=0;
int d=0,e=0;
int d1=0,e1=0;
float moisture1,moisture2;
int pumpState;
int myservoState;
int servos;
int pos=10;
BLYNK_WRITE(V1) {
  pumpState = param.asInt();
  digitalWrite(pump, pumpState);
}
BLYNK_WRITE(V2) {
  myservo.write(param.asInt());
}
BLYNK_WRITE(V5) {
  myservo1.write(param.asInt());
}
BLYNK_WRITE(V6) {
  myservo2.write(param.asInt());
}
void setup()
{
  Serial.begin(115200);
  dht.begin();
  pinMode(pump,OUTPUT);
//  pinMode(servo,OUTPUT);
  myservo.attach(D5);
   myservo1.attach(D0);
    myservo2.attach(D7);
   myservo.write(10);
   myservo1.write(10);
   myservo2.write(10);
   Wire.begin(D1, D2);
  digitalWrite(pump, LOW); 
  delay(1000);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
//  servos=digitalRead(servo);
   if(f==0)
  {
 Wire.beginTransmission(8); 
 Wire.write(1); 
 Wire.endTransmission(); 
 delay(1000);
    Serial.println("request1");
 Wire.requestFrom(8, 1); 
 while(Wire.available()){
    d = Wire.read();
// Serial.println(d);
     f=1;
     f1=0; 
  }
  
  if(f1==0)
  {
 Wire.beginTransmission(8);
 Wire.write(2); 
 Wire.endTransmission(); 
delay(1000); 
  Wire.requestFrom(8, 1); 
 while(Wire.available()){
    e = Wire.read();
//  Serial.println(e);
  }
  f1=1;
  f=0;
  } 
//   if(servos==HIGH)
//  {
//   
//    myservo.write(100);              
//    delay(15);                       
//  
//  }
//  else
//  {
//   
//    myservo.write(10);            
//    delay(15);                    
//  
//  }
 
//  moisture1=d;
//  moisture2=e;
 float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Blynk.virtualWrite(V7, t); 
  Blynk.virtualWrite(V8, h);
  Blynk.virtualWrite(V3, e); 
  Blynk.virtualWrite(V4, d); 
}
delay(50);
}
