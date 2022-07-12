//Farm automation Project

#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h> 
#define DHTPIN 2
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial SIM900(7, 8); // Pins 7, 8 are used as used as software serial pins
String incomingData;   // for storing incoming serial data
String message = "";   // A String for storing the message
int relay_pin = 3;//  pin for relay module
int relay_pin1 = 4;
float h;
float f;
float t;
int flag1=0;
int flag2=0;
void setup()
{
  Serial.begin(19200); // baudrate for serial monitor
  SIM900.begin(19200); // baudrate for GSM shield
  delay(20000);
  SIM900.print("AT+CMGF=1\r");  
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
  delay(100);
  pinMode(relay_pin, OUTPUT);   // Setting erlay pin as output pin
  digitalWrite(relay_pin, HIGH);  // Making relay pin initailly low
  pinMode(relay_pin1, OUTPUT);   // Setting erlay pin as output pin
  digitalWrite(relay_pin1, HIGH);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  // set SMS mode to text mode
  dht.begin(); 
}
void loop()
{
  receive_message();
  if(incomingData.indexOf("Motor1_on")>=0)
  {
    digitalWrite(relay_pin, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    flag1=1;
    SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
    delay(100);  
    SIM900.println("AT+CMGS=\"+91XXXXXXXXXX\""); 
    delay(100);
    message = "Motor1 is turned ON";
    // Send a sms 
    send_message(message);
  SIM900.println("AT");
  delay(1000);
  SIM900.println("AT+CPIN?");
  delay(1000);
  SIM900.println("AT+CREG?");
  delay(1000);
 SIM900.println("AT+CGATT?");
  delay(1000);
   SIM900.println("AT+CIPSHUT");
  delay(1000);
 SIM900.println("AT+CIPSTATUS");
  delay(2000);
   SIM900.println("AT+CIPMUX=0");
  delay(2000);
  ShowSerialData();
 SIM900.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
  ShowSerialData();
  SIM900.println("AT+CIICR");//bring up wireless connection
  delay(3000);
  ShowSerialData();
   SIM900.println("AT+CIFSR");//get local IP adress
  delay(2000);
   ShowSerialData();
 SIM900.println("AT+CIPSPRT=0");
  delay(3000);
   ShowSerialData();
   SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
  ShowSerialData();
   SIM900.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  String str="GET https://api.thingspeak.com/update?api_key=4VF00HR2L5R2JEXQ&field3=1";
  Serial.println(str);
  SIM900.println(str);//begin send data to remote server
    delay(4000);
  ShowSerialData();
  SIM900.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  SIM900.println();
   ShowSerialData();
   SIM900.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  }
  if(incomingData.indexOf("Motor2_on")>=0)
  {
    digitalWrite(relay_pin1, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    flag2=1;
    SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
    delay(100);  
    SIM900.println("AT+CMGS=\"+919850319955\""); 
    delay(100);
    message = "Motor2 is turned ON";
    // Send a sms 
    send_message(message);
      SIM900.println("AT");
  delay(1000);
 
  SIM900.println("AT+CPIN?");
  delay(1000);
   SIM900.println("AT+CREG?");
  delay(1000);
 SIM900.println("AT+CGATT?");
  delay(1000);
 SIM900.println("AT+CIPSHUT");
  delay(1000);
 SIM900.println("AT+CIPSTATUS");
  delay(2000);
   SIM900.println("AT+CIPMUX=0");
  delay(2000);
   ShowSerialData();
  SIM900.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
   ShowSerialData();
  SIM900.println("AT+CIICR");//bring up wireless connection
  delay(3000);
  ShowSerialData();
  SIM900.println("AT+CIFSR");//get local IP adress
  delay(2000);
   ShowSerialData();
 
 SIM900.println("AT+CIPSPRT=0");
 delay(3000);
  ShowSerialData();
    SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
   ShowSerialData();
  SIM900.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
    String str="GET https://api.thingspeak.com/update?api_key=4VF00HR2L5R2JEXQ&field4=1";
  Serial.println(str);
  SIM900.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();
 SIM900.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  SIM900.println();
  ShowSerialData();
  SIM900.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  }
    if(incomingData.indexOf("Motor1_off")>=0)
  {
    digitalWrite(relay_pin, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    flag1=0;
    SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
    delay(100);  
    SIM900.println("AT+CMGS=\"+919850319955\""); 
    delay(100);
    message = "Motor1 is turned OFF";
    // Send a sms back 
    send_message(message);
    SIM900.println("AT");
  delay(1000);
   SIM900.println("AT+CPIN?");
  delay(1000);
  SIM900.println("AT+CREG?");
  delay(1000);
 SIM900.println("AT+CGATT?");
  delay(1000);
   SIM900.println("AT+CIPSHUT");
  delay(1000);
   SIM900.println("AT+CIPSTATUS");
  delay(2000);
   SIM900.println("AT+CIPMUX=0");
  delay(2000);
   ShowSerialData();
  SIM900.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
   ShowSerialData();
   SIM900.println("AT+CIICR");//bring up wireless connection
  delay(3000);
  ShowSerialData();
   SIM900.println("AT+CIFSR");//get local IP adress
  delay(2000);
   ShowSerialData();
   SIM900.println("AT+CIPSPRT=0");
  delay(3000);
   ShowSerialData();
    SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
  ShowSerialData();
   SIM900.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
    String str="GET https://api.thingspeak.com/update?api_key=4VF00HR2L5R2JEXQ&field3=0";
  Serial.println(str);
  SIM900.println(str);//begin send data to remote server
     delay(4000);
  ShowSerialData();
  SIM900.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  SIM900.println();
 ShowSerialData();
  SIM900.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  }     
  if(incomingData.indexOf("Motor2_off")>=0)
  {
    digitalWrite(relay_pin1, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    flag2=0;
    SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
    delay(100);  
    SIM900.println("AT+CMGS=\"+919850319955\""); 
    delay(100);
    message = "Motor2  is turned OFF";
    // Send a sms 
    send_message(message);
      SIM900.println("AT");
  delay(1000);
 SIM900.println("AT+CPIN?");
  delay(1000);
  SIM900.println("AT+CREG?");
  delay(1000);
  SIM900.println("AT+CGATT?");
  delay(1000);
  SIM900.println("AT+CIPSHUT");
  delay(1000);
   SIM900.println("AT+CIPSTATUS");
  delay(2000);
  SIM900.println("AT+CIPMUX=0");
  delay(2000);
   ShowSerialData();
  SIM900.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
  ShowSerialData();
   SIM900.println("AT+CIICR");//bring up wireless connection
  delay(3000);
  ShowSerialData();
   SIM900.println("AT+CIFSR");//get local IP adress
  delay(2000); 
  ShowSerialData();
   SIM900.println("AT+CIPSPRT=0");
  delay(3000);
 ShowSerialData();
  SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 ShowSerialData();
   SIM900.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
    String str="GET https://api.thingspeak.com/update?api_key=4VF00HR2L5R2JEXQ&field4=0";
  Serial.println(str);
  SIM900.println(str);//begin send data to remote server
   delay(4000);
  ShowSerialData();
  SIM900.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  SIM900.println();
   ShowSerialData();
 SIM900.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  }     
  if(incomingData.indexOf("Allon")>=0)
  {
    //digitalWrite(relay_pin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    flag2=1;
    flag1=1;
    SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
    delay(100);  
    SIM900.println("AT+CMGS=\"+919850319955\""); 
    delay(100);
    message = "All Motors are Turned on";
    // Send a sms 
    send_message(message);
    SIM900.println("AT");
  delay(1000);
 
  SIM900.println("AT+CPIN?");
delay(1000);
 SIM900.println("AT+CREG?");
  delay(1000);
 SIM900.println("AT+CGATT?");
  delay(1000);
   SIM900.println("AT+CIPSHUT");
  delay(1000);
   SIM900.println("AT+CIPSTATUS");
  delay(2000);
   SIM900.println("AT+CIPMUX=0");
  delay(2000);
  ShowSerialData();
 SIM900.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
 ShowSerialData();
   SIM900.println("AT+CIICR");//bring up wireless connection
  delay(3000);
  ShowSerialData();
  SIM900.println("AT+CIFSR");//get local IP adress
  delay(2000);
 ShowSerialData();
   SIM900.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
    SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
   ShowSerialData();
 SIM900.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  String str="GET https://api.thingspeak.com/update?api_key=4VF00HR2L5R2JEXQ&field3=1&field4=1";
  Serial.println(str);
  SIM900.println(str);//begin send data to remote server
      delay(4000);
  ShowSerialData();
   SIM900.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  SIM900.println();
   ShowSerialData();
   SIM900.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  }     
   if(incomingData.indexOf("Alloff")>=0)
  {
    //digitalWrite(relay_pin, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    flag2=0;
    flag1=0;
    SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
    delay(100);  
    SIM900.println("AT+CMGS=\"+919850319955\""); 
    delay(100);
    message = "All Motors are Turned off";
    // Send a sms 
    send_message(message);
    SIM900.println("AT");
  delay(1000);
   SIM900.println("AT+CPIN?");
  delay(1000);
  SIM900.println("AT+CREG?");
  delay(1000);
   SIM900.println("AT+CGATT?");
  delay(1000);
   SIM900.println("AT+CIPSHUT");
  delay(1000);
   SIM900.println("AT+CIPSTATUS");
  delay(2000);
   SIM900.println("AT+CIPMUX=0");
  delay(2000);
   ShowSerialData();
   SIM900.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
   ShowSerialData();
   SIM900.println("AT+CIICR");//bring up wireless connection
  delay(3000);
   ShowSerialData();
 SIM900.println("AT+CIFSR");//get local IP adress
  delay(2000);
   ShowSerialData();
   SIM900.println("AT+CIPSPRT=0");
  delay(3000);
   ShowSerialData();
   SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 ShowSerialData();
   SIM900.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);  ShowSerialData();  
String str="GET https://api.thingspeak.com/update?api_key=4VF00HR2L5R2JEXQ&field3=0&field4=0";
  Serial.println(str);
  SIM900.println(str);//begin send data to remote server
      delay(4000);
  ShowSerialData();
  SIM900.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  SIM900.println();
  ShowSerialData();
   SIM900.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  }     
  if(incomingData.indexOf("State")>=0)
  {
    if(flag1==1 and flag2==1)
    {
      message="Motor1 and Motor2 are ON";
    }
    else if(flag1==1 and flag2== 0)
    {
      message="Motor1:ON  Motor2:OFF";
    }
    else if(flag1==0 and flag2==1)
    {
      message="Motor1:OFF  Motor2:ON";
    }
    else
    {
      message="Motor1:OFF Motor2:OFF";
    }
    SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
    delay(100);  
    SIM900.println("AT+CMGS=\"+919850319955\""); 
    delay(100);
    //send a sms
    send_message(message);
  }     
  if(incomingData.indexOf("temp")>=0)
  {
    delay(10);
    SIM900.println("AT+CMGS=\"+919850319955\"\r");
    delay(100);
    //digitalWrite(relay_pin, HIGH);
    h = dht.readHumidity();//Read humidity
    t = dht.readTemperature(); // Read temperature as Celsius
    f = dht.readTemperature(true);// Read temperature as Fahrenheit
    t = dht.computeHeatIndex(t,h,false);// Compute temperature values in Celcius
    message = ("Temperature: " + String(t) + "*C " + " Humidity: " + String(h) + "%");
    //send a sms
    send_message(message);
      SIM900.println("AT");
  delay(1000);
   SIM900.println("AT+CPIN?");
  delay(1000);
   SIM900.println("AT+CREG?");
  delay(1000);
  SIM900.println("AT+CGATT?");
  delay(1000);
   SIM900.println("AT+CIPSHUT");
  delay(1000);
   SIM900.println("AT+CIPSTATUS");
  delay(2000);
  SIM900.println("AT+CIPMUX=0");
  delay(2000);
   ShowSerialData();
  SIM900.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
  ShowSerialData();
  SIM900.println("AT+CIICR");//bring up wireless connection
  delay(3000);
   ShowSerialData();
  SIM900.println("AT+CIFSR");//get local IP adress
  delay(2000);
 ShowSerialData();
   SIM900.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
    SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
  ShowSerialData();
   SIM900.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  String str="GET https://api.thingspeak.com/update?api_key=4VF00HR2L5R2JEXQ&field1=" + String(t) +"&field2="+String(h);
  Serial.println(str);
  SIM900.println(str);//begin send data to remote server
   delay(4000);
  ShowSerialData();
 SIM900.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  SIM900.println();
   ShowSerialData();
   SIM900.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
      }     
}
void ShowSerialData()
{
  while(SIM900.available()!=0)
  Serial.write(SIM900.read());
  delay(5000); 
  }
void receive_message()
{
  if (SIM900.available() > 0)
  {
    incomingData = SIM900.readString(); // Get the data from the serial port.
    Serial.print(incomingData); 
    delay(10); 
  }
}
void send_message(String message)
{
  Serial.print(message); 
  SIM900.println(message);   
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  delay(1000);  
}
