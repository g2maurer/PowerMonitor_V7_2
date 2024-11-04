# PowerMonitor_V7_2

Initial Release
 
Source code for Power Monitor/Logger.
  
## Note the following:
  

## Build:
* Compile with Arduino Sketch IDE version 1.8.19.
* ESP Board Manager - esp32 by Espressif Systems version 2.0.17.
	* NOTE: Don't try to use newer versions (3.0.x or newer).
* Board: DOIT ESP32 DEVKIT V1
* Make sure the TFT_eSPI "User_Setup_Select.h" file selects the correct controller type (ILI9488 driver)
		and pin definitions. Use ILI9488_g2m.h file found in Misc directory as User_Setup file.
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
	
## Peripherals:
* Supports Realtime Clock chip RV3028__C7 (not required if WiFi connected it get the time via NTP).

