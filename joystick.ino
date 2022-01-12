int xValue = 0 ;
int yValue = 0 ; 
int bValue = 0 ;

void setup()  
{ 
  Serial.begin(9600) ;
  pinMode(8,INPUT); 
  digitalWrite(8,HIGH); 
} 

void loop() 
{ 
  xValue = analogRead(A0);  
  yValue = analogRead(A1);  
  bValue = digitalRead(8);  
  Serial.print(xValue,DEC);
  Serial.print(",");
  Serial.print(yValue,DEC);
  Serial.print(",");
  Serial.print(!bValue);
  Serial.print("\n");
  delay(500);  
}
