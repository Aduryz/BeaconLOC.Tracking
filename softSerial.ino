#include <SoftwareSerial.h>
SoftwareSerial BSerial(2, 3); //TX to 2, RX to 3
 
void setup()  
{
  Serial.begin(9600);
  Serial.println("Hello!");
 
  // set the data rate for the BT port
  BSerial.begin(9600);
}
 
void loop()
{
  if (BSerial.available())
    Serial.write(BSerial.read());
  if (Serial.available())
    BSerial.write(Serial.read());
}
