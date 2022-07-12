# Farmify

Farmify aims to control farm appliances wirelessly.
The system uses a GSM module which is based on SMS technique to operate devices remotely. 
Temperature and humidity sensor DHT22 captures the surrounding temperature and humidity of environment. 
These readings are sent to the user via SMS and also uploaded to ThingsSpeak Cloud Platform for analysis and storing for User reference.

## Demo

https://bit.ly/FarmifyDemo
## Features

- Operates Appliances without an Internet Connection
- Runtime Temperature and humidity data can be accessed
- Status of Appliances can be monitored on a Cloud Platform
- Number of Appliances can be scaled by using bigger relay modules


## Tech Stack
            
**Hardware:** Arduino UNO, GSM SIM 800C, Relay Module, DHT22 Sensor

**Software:** Arduino IDE


## Usage
Replace the XXXXXXXXXX with the Mobile NUmber of the Inserted Sim 

    SIM900.println("AT+CMGS=\"+91XXXXXXXXXX\""); 

Replace the gprs site according to your Network Service provider
(Default: Airtel India)

     SIM900.println("AT+CSTT=\"airtelgprs.com\""); 
