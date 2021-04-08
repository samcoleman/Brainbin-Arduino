#include <SoftwareSerial.h>
#include "DoorControl.h"

#include <SPI.h>  // Include SPI if you're using SPI
#include "HT_SSD1306.h"  // Include the HT_SSD1306 library

//////////////////////////
// SSD1306 Definition //
//////////////////////////
#define PIN_RESET 12  // Connect RST to pin 9
#define PIN_DC    10  // Connect DC to pin 8
#define PIN_CS    8 // Connect CS to pin 10
#define DC_JUMPER 1

//////////////////////////////////
// SSD1306 Object Declaration //
//////////////////////////////////
SSD1306 oled(PIN_RESET, PIN_DC, PIN_CS); // SPI declaration

//                     (PWMPin, SweepSpeed, ClosedAngle, OpenAngle)
DoorControl DoorControl(6 , 65, 5, 175);

// Accepted Barcode
String accepted_barcode = "brainbin";

// Set up (RX, TX) pins of barcode scanner
SoftwareSerial Ser1(2, 3);

// Millis overflows after 50days of running, this would cause a timing issue if a barcode is scanned during the time of overflow
// But think the instance of event is unlikely and would just require the user to scan again. There are solutions but
// I dont think needed for the demo

unsigned long correct_timer_start_time;
unsigned long correct_timer_duration = 30000; // 30 seconds (Units ms)

unsigned long incorrect_timer_start_time;
unsigned long incorrect_timer_duration = 5000; // 5 seconds (Units ms)

int incorrect_scan_led = 9;

int interior_sensor = 7;

void setup() {
  Serial.begin(9600);
  Ser1.begin(9600); // Use software serial to interface with USB Host, leaving Serial open for debugging purposes

  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  
  pinMode(incorrect_scan_led, OUTPUT);
  pinMode(interior_sensor, INPUT);

  digitalWrite(incorrect_scan_led, LOW); 
  hide_qr(); 
  
  DoorControl.reset();
  delay(1000);
  Ser1.listen(); // Select Ser1 for receiving   
}

void display_qr(){
  oled.logo();
  oled.display(); 
}

void hide_qr(){
  oled.clear(PAGE); 
  oled.display();
}

void loop()
{
  if(Ser1.available() > 0 ){
    String str = Ser1.readString();

    // If barcode is correct start timer
    if (str == accepted_barcode){
      correct_timer_start_time = millis();
      digitalWrite(incorrect_scan_led, LOW); 
      display_qr();
      DoorControl.door_open();
    } else {
      incorrect_timer_start_time = millis();
      digitalWrite(incorrect_scan_led, HIGH); 
    }
    
    Serial.print("Scanned:");
    Serial.println(str);
  }

  if (digitalRead(interior_sensor) == LOW){
    DoorControl.door_close();
  }

  // If correct scan duration is exceeded close door and hide QR code
  if (millis() > correct_timer_start_time+correct_timer_duration){
    DoorControl.door_close();
    hide_qr();
  }

  // If incorrect scan duration is exceeded turn off incorrect LED
  if (millis() > incorrect_timer_start_time+incorrect_timer_duration){
    digitalWrite(incorrect_scan_led, LOW);
  }
}
