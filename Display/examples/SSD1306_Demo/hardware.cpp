/****************************************************************************** 
hardware.cpp

This is a modified version of the Sparkfun code for their SSD1306 Arduino Library
It has been modified to work on the Hobbytronics OLED 128x64 module

The same terms of use apply - see below
*******************************************************************************
hardware.cpp
MicroOLED Arduino Library Hardware Interface

Jim Lindblom @ SparkFun Electronics
October 26, 2014
https://github.com/sparkfun/Micro_OLED_Breakout/tree/master/Firmware/Arduino/libraries/SFE_MicroOLED

This file defines the hardware interface(s) for the Micro OLED Breakout. Those
interfaces include SPI, I2C and a parallel bus.

Development environment specifics:
Arduino 1.0.5
Arduino Pro 3.3V
Micro OLED Breakout v1.0

This code was heavily based around the MicroView library, written by GeekAmmo
(https://github.com/geekammo/MicroView-Arduino-Library), and released under 
the terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later 
version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "HT_SSD1306.h"
#include <SPI.h>
#include <Wire.h>

#define I2C_FREQ 400000L	// I2C Frequency is 400kHz (fast as possible)

/** \brief Set Up SPI Interface

	Sets up the SPI pins, initializes the Arduino's SPI interface.
**/
void SSD1306::spiSetup()
{
	// Gather the CS pin's PORT, PIN, and DDR registers. Writing
	// these directly will make things much faster.
	ssport		= portOutputRegister(digitalPinToPort(csPin));
	sspinmask	= digitalPinToBitMask(csPin);
	ssreg		= portModeRegister(digitalPinToPort(csPin));
	
	// Initialize the pins:
	pinMode(MOSI, OUTPUT);	// MOSI is an OUTPUT
	pinMode(SCK, OUTPUT);	// SCK is an OUTPUT
	pinMode(csPin, OUTPUT);	// CS is an OUTPUT
	digitalWrite(csPin, HIGH);	// Start CS High
	
	// Initialize the SPI library:
	SPI.setClockDivider(SPI_CLOCK_DIV4);	// Fastest SPI clock possible
	SPI.setDataMode(SPI_MODE0);	// CPOL=0 and CPHA=0, SPI mode 0
	pinMode(10, OUTPUT); // Required for setting into Master mode
	SPI.begin();
}

/** \brief Transfer a byte over SPI

	Use the SPI library to transfer a byte. Only used for data OUTPUT.
	This function does not toggle the CS pin. Do that before and after!
**/
void SSD1306::spiTransfer(byte data)
{
	SPI.transfer(data);	
}

/** \brief Initialize the I2C Interface

	This function initializes the I2C peripheral. It also sets up the
	I2C clock frequency.
**/
void SSD1306::i2cSetup()
{
	// Initialize Wire library (I2C)
	Wire.begin();
	
	// SCL frequency = (F_CPU) / (16 + 2(TWBR) * (prescalar))
	TWBR = ((F_CPU / I2C_FREQ) - 16) / 2;
}

/** \brief  Write a byte over I2C

	Write a byte to I2C device _address_. The DC byte determines whether
	the data being sent is a command or display data. Use either I2C_COMMAND
	or I2C_DATA in that parameter. The data byte can be any 8-bit value.
**/
void SSD1306::i2cWrite(byte address, byte dc, byte data)
{
	Wire.beginTransmission(address);
	Wire.write(dc); // If data dc = 0, if command dc = 0x40
	Wire.write(data);
	Wire.endTransmission();
}

