/******************************************************************************
  SSD1306_hello.ino

  This is a modified version of the Sparkfun example code for their MicroOLED Arduino Library
  It has been modified to work on the Hobbytronics OLED 128x64 module

  he same terms of use apply - see below

  *******************************************************************************
  MicroOLED_Hello.ino
  SFE_MicroOLED Hello World Demo
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: October 26, 2014
  
  This sketch lights up a familiar pattern on the MicroOLED
  Breakout. It's a great way to prove you've connected everything
  correctly and that your display is in working order.
  
  Hardware Connections:
    We'll be using the SPI interface on the MicroOLED, though it
    also supports I2C (and a really messy parallel). If you want
    to swap in I2C, read through the comments to find out how.
    
     OLED ------------------- Arduino
      GND ------------------- GND
       +V ------------------- 5V/3.3V
      DAT ------------------- D11(MOSI) (don't change)
      CLK ------------------- D13(SCK) (don't change)
       DC ------------------- D8 (can be any digital pin)
      RST ------------------- D9 (can be any digital pin)
       CS ------------------- D10 (can be any digital pin)
    
  Development environment specifics:
  	IDE: Arduino 1.0.5
  	Hardware Platform: MicroOLED Breakout
                           Arduino Pro 3.3V/8MHz
  
  Note: The display on the MicroOLED is a 1.8V-3.3V device only.
  Don't try to connect a 5V Arduino directly to it! Use level
  shifters in between the data signals if you have to resort to
  a 5V board.
  
  This code is beerware; if you see me (or any other SparkFun 
  employee) at the local, and you've found our code helpful, 
  please buy us a round!
  
  Distributed as-is; no warranty is given.
*******************************************************************************/
#include <Wire.h>  // Include Wire if you're using I2C
#include <SPI.h>  // Include SPI if you're using SPI
#include <HT_SSD1306.h>  // Include the HT_SSD1306 library

//////////////////////////
// SSD1306 Definition //
//////////////////////////
#define PIN_RESET 9  // Connect RST to pin 9
#define PIN_DC    8  // Connect DC to pin 8
#define PIN_CS    10 // Connect CS to pin 10
#define DC_JUMPER 1
// Also connect pin 13 to SCK and pin 11 to MOSI

//////////////////////////////////
// SSD1306 Object Declaration //
//////////////////////////////////
// Declare a SSD1306 object. The parameters include:
// 1 - Reset pin: Any digital pin
// 2 - D/C pin: Any digital pin (SPI mode only)
// 3 - CS pin: Any digital pin (SPI mode only, 10 recommended)
SSD1306 oled(PIN_RESET, PIN_DC, PIN_CS);
//HT_SSD1306 oled(PIN_RESET, DC_JUMPER); // Example I2C declaration

// I2C is great, but will result in a much slower update rate. The
// slower framerate may be a worthwhile tradeoff, if you need more
// pins, though.
void setup()
{

  // These three lines of code are all you need to initialize the
  // OLED and print the splash screen.

  // Before you can start using the OLED, call begin() to init
  // all of the pins and configure the OLED.
  oled.begin();
  // clear(ALL) will clear out the OLED's graphic memory.
  // clear(PAGE) will clear the Arduino's display buffer.
  oled.clear(ALL);  // Clear the display's memory (gets rid of artifacts)  
}

void loop()
{

  printTitle("Load Bitmap!", 1);  
  oled.display();
  delay(1000);  
  oled.logo();
  oled.display();
  delay(1000);    
}

void printTitle(String title, int font)
{
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;
  
  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)),
                 middleY - (oled.getFontWidth() / 2));
  // Print the title:
  oled.print(title);
  oled.display();
  delay(1500);
}