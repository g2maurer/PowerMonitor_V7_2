# PowerMonitor_V7_2

## Code:
* ESP32 code files.
* Compile with Arduino Sketch IDE version 1.8.19.
* ESP Board Manager - esp32 by Espressif Systems version 2.0.17.
	* NOTE: Don't try to use newer versions (3.0.x or newer).
* Board: DOIT ESP32 DEVKIT V1

* Required Libraries:
	* RV3028C7.h - Realtime Clock
	* TimeLib.h -
	* Adafruit_ADS1X15.h - Analog-to-Digital converter.
	* WiFi.h
	* WiFiUdp.h
	* NTPClient.h
	* TFT_eSPI.h - TFT screen with Touch.
	* SD.h - SD memory card.
	* SPIFFS.h

## Enclosure:
* STL files for enclosure (front and back).
* FreeCAD enclosure design files.

## Images:
* Image files for PCB and enclosure.

## KiCAD:
* PCB design files.

## Misc:
* TFT user setup file. 
	* Contains the ESP32 to TFT pin definitions.
	* The TFT_eSPI "User_Setup_Select.h" file selects the User_Setup file. 
	* Use ILI9488_g2m.h file found in Misc directory for User_Setup file.
	
## PCB Components:
* ESP32-WROOM-32S.
* 3.5 inch TFT with Touch. 
	* SPI interface.
* ADS1015 Analog to Digital converter ICs. 
	* Configured in differntail mode, two CT channels per A2D converter IC.
* CH340K USB to serial inteface IC.
	* microUSB interface (USB-B).
* RV3028__C7 Realtime Clock IC and battery. 
	* Not required if WiFi connected to get the time via NTP.

