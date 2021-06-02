/*-------------------------------------------------------------------
Arduino Code for IOT tracking system, for Thesis using GPS and GSM.
---------------------------------------------------------------------*/
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
float latt,longi; // create variable for latitude and longitude object 
float a[2]; //array to store gps data;
float *location_pointer;//pointer to point the array location
SoftwareSerial gpsSerial(10,11);  // software serial for gps module
SoftwareSerial gsmSerial(7,8);   // software serial for gsm module
TinyGPSPlus gps; // new gps object
void setup(){
Serial.begin(9600); 
delay(1000);
gpsSerial.begin(9600); 
delay (1000);
gsmSerial.begin(9600); 
delay(1000);
gsmSerial.println("AT+CNMI=2,2,0,0,0");// AT Command to receive a live SMS
Serial.println("AT+CNMI=2,2,0,0,0");
delay(3000);
}

void loop(){
  while(gsmSerial.available()){
   gsmSerial.read();
}
  while(Serial.available()){
   Serial.read();
}
 send_the_location(); 
}
float *get_gps()
{
   gpsSerial.listen();
   while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }
      if (gps.location.isUpdated())
      {
       Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
       Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
       latt=gps.location.lat();
       longi=gps.location.lng();
      break;
      }
      
}
a[0]=latt;
a[1]=longi;
return a;
}

void send_the_location()
{
  
   gsmSerial.listen();
   
  
   
   while(gsmSerial.available()>0)
   {Serial.println("INSIDE gsmSerial.available");
  
    if(gsmSerial.find("Track")) // if the txt is received
    {Serial.println("SMS Received, starting to Track");
     gsmSerial.println("AT+CMGF=1");     //GSM Module is set into Text Mode
     delay(1000);
     gsmSerial.println("AT+CMGS=\"+4915213892570\"\r"); //number from which the Vehicle is tracked
     delay(1000);
     location_pointer=get_gps();
     gsmSerial.listen();
     gsmSerial.print("https://www.google.com/maps/?q=");
     Serial.print("LATTITUDE=");
     Serial.print(*location_pointer,6);
     gsmSerial.print(*location_pointer,6);gsmSerial.print(",");
     Serial.print("LONGITUDE="); Serial.print(*(location_pointer+1),6);
     gsmSerial.print(*(location_pointer+1),6);// This is the end of the SMS 
     delay(100);
     gsmSerial.println((char)26);// This lets the module know its the end of the sms
    }
   }
}