// Code to use SoftwareSerial
#include <SoftwareSerial.h>
SoftwareSerial esp8266 = SoftwareSerial(2,3);/* arduino RX pin=2 arduino TX pin=3
 connect the arduino RX pin to esp8266 module TX pin - connect the arduino TX pin
to esp8266 module RX pin */
int redLed = 12;
int greenLed = 11;
int buzzer = 10;
float MQ2 = A0;
float MQ135 = A1;
float MQ3 = A2;
float MQ9 = A3;
float MQ8 = A4;
float Flame = A5;
float gas_value;
String API = "OGCTK0EEAE0IR3SZ";// replace with your channel's thingspeak WRITE API key
String AP ="V2025"; // Wifi network SSID
String PASS ="94EEEC87"; // Wifi network password
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand;
boolean found = false;
//================================================================================
setup
void setup() {
 //----------my sensor code-----------
 Serial.begin(9600);
 pinMode(MQ2, INPUT);
 pinMode(MQ135, INPUT);
 pinMode(MQ9, INPUT);
 pinMode(MQ8, INPUT);
 pinMode(MQ3, INPUT);
 pinMode(Flame, INPUT);
 pinMode(redLed, OUTPUT);
 pinMode(greenLed, OUTPUT);
 pinMode(buzzer, OUTPUT); // declare the LDR as an INPUT
 esp8266.begin(115200);
 sendCommand("AT",20,"OK");
 sendCommand("AT+CWMODE=1",20,"OK");
 sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}
// ======================================================================= loop
void loop() {
 // put your main code here, to run repeatedly:
Serial.print("\n");
Serial.print("Sensor readings :\n");
String getData = "GET /update?api_key="+ API +"&field1="+getMQ2Value()
+"&field2="+getMQ135Value()
+"&field3="+getMQ3Value()
+"&field4="+getMQ9Value()
+"&field5="+getMQ8Value()
+"&field6="+getFLAMEValue();
sendCommand("AT+CIPMUX=1",5,"OK");
sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,20,"OK");
sendCommand("AT+CIPSEND=0," +String(getData.length()+4),20,">");

 esp8266.println(getData);delay(1500);countTrueCommand++;
sendCommand("AT+CIPCLOSE=0",20,"OK");
}
 //----------Reading Mq2 Sensor Value-----------
String getMQ2Value(){
 Serial.print(" MQ2 Sensor value = ");
 int S0 = analogRead(MQ2);
 Serial.println(S0);
 delay(50);
 return String(S0);

}
 //----------Reading Mq135 Sensor Value-----------
String getMQ135Value(){
 Serial.print(" MQ135 Sensor value = ");
 int S1 = analogRead(MQ135);
 Serial.println(S1);
 delay(50);
 return String(S1);

}
 //----------Reading Mq3 Sensor Value-----------
String getMQ3Value(){
 Serial.print(" MQ3 Sensor value = ");
 int S2 = analogRead(MQ3);
 Serial.println(S2);
 delay(50);
 return String(S2);

}
 //----------Reading Mq9 Sensor Value-----------
String getMQ9Value(){
 Serial.print(" MQ9 Sensor value = ");
 int S3 = analogRead(MQ9);
 Serial.println(S3);
 delay(50);
 return String(S3);

}
 //----------Reading Mq8 Sensor Value-----------
String getMQ8Value(){
 Serial.print(" MQ8 Sensor value = ");
 int S4 = analogRead(MQ8);
 Serial.println(S4);
 delay(50);
 return String(S4);

}

 //----------Reading Flame Sensor Value-----------
String getFLAMEValue(){
 Serial.print(" Flame Sensor value = ");
 int S5 = analogRead(Flame);
 Serial.println(S5);
 delay(50);
 return String(S5);

}
 //----------sendind the data-----------
void sendCommand(String command, int maxTime, char readReplay[]) {
Serial.print(countTrueCommand);
Serial.print(". at command => ");
Serial.print(command);
Serial.print(" ");
while(countTimeCommand< (maxTime*1))
 {
 esp8266.println(command);//at+cipsend
 if(esp8266.find(readReplay))//ok
 {
 found = true;
 break;
 }
countTimeCommand++;
 }
if(found == true)
 {
Serial.println("OYI");
countTrueCommand++;
countTimeCommand = 0;
 }
if(found == false)
 {
Serial.println("Fail");
countTrueCommand = 0;
countTimeCommand = 0;
 }
 found = false;
 }
