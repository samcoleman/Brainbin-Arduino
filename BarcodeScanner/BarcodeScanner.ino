#include <SoftwareSerial.h>

SoftwareSerial Ser1(2, 3);
//Set up (RX, TX) pins^

void setup() {
  Serial.begin(9600);
  Ser1.begin(9600); // Use software serial to interface with USB Host, leaving Serial open for debugging purposes
}

void loop()
{

  delay(1000);

  Ser1.listen(); // Select Ser1 for receiving   

  delay(100); // Give it time to send a response or you'll get nothing!

  while(Ser1.available() > 0 ){
    String str = Ser1.readString();
    Serial.print("I received:");
    Serial.println(str);
  } 
}
