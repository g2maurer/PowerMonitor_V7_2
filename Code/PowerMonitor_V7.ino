
#define FILE_NAME "PowerMonitor_V7.ino"

//#define DS3231_RTC
#define RV3028_C7
//#define DELETE_LOG_CONFIG
//#define DELETE_WIFI_CONFIG
//#define FTP_SRVR
//#define SIMPLE_FTP
//#define CT_LEFT_SIDE      // CT-x jacks on left side of case.

//#define REPEAT_TFT_CAL
//#define PRINT_TFT_CAL_DATA
#define TFT_ROTATION 0      // CT jacks: 0 = left side, 2 = right side

#define CORE_0_TASK       // Assigns monitoring of CT inputs to Core 0

//
//  Select SPIFFS_SUPPORT and SD_SUPPORT
//
#define SPIFFS_SUPPORT
#define SD_SUPPORT


#define TFT_320X480           // Portrait 
//#define TFT_480X320           // Landscape

#ifdef TFT_320X480            // Portrait
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#elif TFT_480X320             // Landscape
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320
#endif

#define DEFAULT_SSID "ssid"
#define DEFAULT_PASSWORD "password"
#define DEFAULT_FTP_UN "ftp"
#define DEFAULT_FTP_PW "ftp"
#define WIFI_NAME "AmpMeter"

#define RTD_ADC_SAMPLES 5         // Temperature sensor 

#include <Arduino.h>
#include "soc/soc.h"           // Disable brownout problems

#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include <TimeLib.h>

#include <Adafruit_ADS1X15.h>
Adafruit_ADS1015 ads48;  
Adafruit_ADS1015 ads49;      

#ifdef CORE_0_TASK
TaskHandle_t Task1;
#endif

//
//  Project Files
//
#include "xSPIFFS.h"
#include "xWiFi.h"
#include "Meter.h"
#include "TFT.h"
#include "RTC_NTP.h"
#include "xTimeZone.h"
#include "xKeyboard.h"
#include "Buttons.h"
#include "Log.h"


//
//  Included Library
//
#ifdef FTP_SRVR
#include <ESP8266FtpServer.h>
#endif
#ifdef SIMPLE_FTP
#include <SimpleFTPServer.h>
#endif
#include "WiFi.h"
#include <WiFiUdp.h>
#include <NTPClient.h>

#include "TFT_eSPI.h"

#include "Free_Fonts.h"

#ifdef SD_SUPPORT
#include "SD.h"
#endif

#define PAD 0
//
//  SPIFFS files
//   File names (fn.....)
//
#define CHAN_1_CONFIG_FN "/Chan1config.bin"
#define CHAN_2_CONFIG_FN "/Chan2config.bin"
#define CHAN_3_CONFIG_FN "/Chan3config.bin"
#define CHAN_4_CONFIG_FN "/Chan4config.bin"

const char* fnTftCal = "/tftcal.bin";
const char* fnWifiConfig = "/wifi.bin";
const char* fnTimeZoneConfig = "/timezone.bin";
const char* fnLogConfig = "/LogConfig.bin";
const char* fnEventLog = "/EventLog.csv";
const char* fnIntervalLog = "/IntervalLog.csv";
char fnInterval[16];
char fnEvent[16];

//
//
//
int ssidSelectIndex = 0;
bool ssidSelected = false;
//  WiFi SSID and Password
char tempSSID[32];
char tempPW[32];
bool changedSSID = false;
bool changedWiFiPW = false;
bool changedWiFiEnable = false;
//  FTP Username and Password
char tempFtpUN[32];
char tempFtpPW[32];
bool changedFtpUN = false;
bool changedFtpPW = false;
bool changedFtpEnable = false;

bool changedLogConfig = false;

//
//  NTP - Network Time Protocol
//
const char* ntpServer1 = "time.nist.gov";
const char* ntpServer2 = "ptbtime1.ptb.de";
const char* ntpServer3 = "pool.ntp.org";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "us.pool.ntp.org", 0);   //-7*3600);

#ifdef FTP_SRVR
FtpServer ftpSrv;
#endif
#ifdef SIMPLE_FTP
FtpServer ftpSrv;
#endif
TFT_eSPI myTFT = TFT_eSPI();       // Invoke custom library

const GFXfont *gfxFont = NULL;



///////////////////////////////////////
//
//  ESP32 Pin Definitions
//
#define REPEAT_CAL_PIN  39    // (39 = VN)

// ----- TFT -----             Net Name
//#define TFT_DIN 23          // MOSI & Touch_DIN
//#define TFT_SCK 18          // SCK (both TFT and Touch)
#define TFT_LED   26          // TFT_LED, control pin
#define TFT_CS    15          // TFT_CS
#define TFT_RESET 2           // TFT_RESET
#define TFT_DC    4           // TFT_DC
//#define TOUCH_INT_PIN 25    // TouchInt
//#define TOUCH_DOUT  19      // Touch_DOUT & MISO
#define TOUCH_CS_PIN    5     // Touch_CS

// ----- ADC -----
#define ADC1_0  36      // (36=VP) Temperature Sensor

// ------ RTC -----
#define RTC_INT_PIN   35      // RTC_INT

//
// Wire definitions
//
#define SDA_0 21    // SDA_0
#define SCL_0 22    // SCL_0

#define SDA_1 33    // SDA_1
#define SCL_1 32    // SCL_1

TwoWire I2C_0 = TwoWire(0);     // RTC
TwoWire I2C_1 = TwoWire(1);     // ADC's

//
// ----- SD Card -----
//
//#ifdef SD_SUPPORT
// Pin Definitions          Net Name
#define HSPI_MISO   16    // SD_MISO
#define HSPI_MOSI   17    // SD_MOSI
#define HSPI_SCLK   14    // SD_CLK
#define HSPI_SS     27    // SD_CS
#define SD_CARD_DET 34    // SD_DET

#define SD_SPI_FREQ 1000000
SPIClass hspi = SPIClass(HSPI);
//#endif

//
//  Temperature Sensor
//
#define Rref 1500     //1800

#define nominal_resistance 1093       //Nominal resistance at 25⁰C
#define nominal_temperature 25   // temperature for nominal resistance (almost always 25⁰ C)
#define beta -375   //3950  // PTC, The beta coefficient or the B value of the thermistor check the datasheet for the accurate value.


#define LINE_VOLTAGE  120.0     //230.0
#define LINE_FREQ 60.0          //50.0

//
//  NUMBER_SAMPLES multipled by sample time should be a multiple of line period (frequency).
//  Line period = 16.666ms
//
#define NUMBER_SAMPLES 10 
//#define DEBUG_SAMPLE_COUNT

#define LOOP_TIME 166        // 166 milliseconds

float multiplier = 0.001;   // 1 mV

struct CHAN_CONFIG_STRUCT {
  int index;
  boolean enabled;
  float range;             // 5, 10, 15, 20 Amp max
  int lineV;
}; 

CHAN_CONFIG_STRUCT CT1 = { 0, true, 50.0, 120};            // CT1, CT2, CT3, CT4
CHAN_CONFIG_STRUCT CT2 = { 1, true, 50.0, 120};
CHAN_CONFIG_STRUCT CT3 = { 2, true, 30.0, 120};
CHAN_CONFIG_STRUCT CT4 = { 3, true, 30.0, 120};

CHAN_CONFIG_STRUCT prevChanConfig;

String chanConfigFN[4] = {CHAN_1_CONFIG_FN, CHAN_2_CONFIG_FN, CHAN_3_CONFIG_FN, CHAN_4_CONFIG_FN};

struct CHAN_DATA_STRUCT {
  int number;
  float Irms;
  float prevIrms;
  float watts;        
  float fullScale;
  int v100;
  int v10;
  int v1;
  bool changed;
  bool load;        // true if Irms > 0.100 else false
  bool prevLoad;
}; 

CHAN_DATA_STRUCT chanData1 = {1, 0.0, 5.0, 0.0,
      8.0, 0, 0, 0, false, false, false
      };
CHAN_DATA_STRUCT chanData2 = {2, 0.0, 5.0, 0.0,
      16.0, 0, 0, 0, false, false, false
      };
CHAN_DATA_STRUCT chanData3 = {3, 0.0, 5.0, 0.0,
      16.0, 0, 0, 0, false, false, false
      };
CHAN_DATA_STRUCT chanData4 = {4, 0.0, 5.0, 0.0,
      24.0, 0, 0, 0, false, false, false
      };

//
//  TFT Brightness Control pins
//
// SPI TFT ONLY !!!
#define LED_PWM_CHANNEL    0
#define LED_PWM_FREQ       1000      // 5000Hz
#define LED_PWM_RESOLUTION 8         // 8 bits
#define TFT_LED_TIMEOUT 180

#include <driver/adc.h>

////////////////////////////////////////
//
//  Definitions
//
enum MENU_STATE { MAIN_MENU, CHAN_1_MENU, CHAN_2_MENU, CHAN_3_MENU, 
                  CHAN_4_MENU, CHAN_CONFIG_MENU, VOLTAGE_KPAD, SYSTEM_MENU,
                  KEYBOARD_MENU, TZ_MENU, REGION_MENU, CITY_MENU,
                  WIFI_MENU, SSID_MENU, FTP_MENU, LOG_MENU, ELOG_MENU,
                  ILOG_MENU, ILOG_KPAD, ELOG_KPAD, ELOG_CT_MENU,
                  SD_MENU, ABOUT_MENU };


enum TFT_LED_STATE {TFT_LED_OFF, TFT_LED_ON, TFT_LED_FADE_UP, TFT_LED_FADE_DOWN};

///////////////////////////////////////
//
//  Global Varibles
//
//
//   ----- boolean -----
bool interruptTriggered = false;
bool WiFi_Connect_Flag = false;
bool FanOn = false;
bool AugerOn = false;
bool HeaterOn = false;
bool epochTimeValid = false;
bool ftpTIP = false;          // ftp Transfer In Progress
bool SD_CardPresent = false;
//   ----- int -----
int menuState = MAIN_MENU;
int logIntervalTimer = 0;
int ledTimer = TFT_LED_TIMEOUT;
int prevTempF = 70;
int temperatureF;
int temperatureC;
int dutyCycle = 255;    // TFT LED dutycycle  (255 = FULL ON, 0 = OFF)
int fileCnt = 0;
int dirCnt = 0;
int tmpIntValue = 0;
int tmpEventValue = 5;      // actually 0.5
int eLogCTn = 1;            // only 1, 2, 3 or 4
int tmpLineV = 0;
static int currentDay = 32;
int readChan = 1;
int tftLedState = TFT_LED_ON;
//int gblV100 = 0;
//int gblV10 = 0;
//int gblV1 = 0;
//   ----- long -----
unsigned long time_now = 0;
unsigned long timePeriodStart = 0;
unsigned long ckTperiod = 2000;     // 2 seconds
unsigned long epochTime = 0;
//   ----- double -----

//   ----- float -----
float IrmsC1 = 0;
float prevIrmsC1 = 0;
float IrmsC2 = 0;
float prevIrmsC2 = 0;
float IrmsC3 = 0;
float prevIrmsC3 = 0;
float IrmsC4 = 0;
float prevIrmsC4 = 0;

// Arrays
char chrBuf[64];
char timeTxt[16];
char ideVer[64];
char logText[64];
String ipAddr;
String macAddr;
int chanPage[5] = { 0, CHAN_1_MENU, CHAN_2_MENU, CHAN_3_MENU, CHAN_4_MENU};

CHAN_CONFIG_STRUCT *pChanConfig = &CT1;
CHAN_DATA_STRUCT *pChanData = &chanData1;

struct SD_CARD_STRUCT {
  bool present;
  bool mounted;
  int Type;         // Card type
  char cType[16];
  uint64_t Size;       // Card size
  float SizeGB;
  uint64_t Capacity;   // Total bytes
  uint64_t Available;    // Used bytes
  uint64_t Used;    // Used bytes
} sdCard;

//
//  Clock Variables
//
char TOD[8];
int isdst = 0;
int offsetTZ;
byte clockhour; // Holds current hour value
byte clockminute; // Holds current minute value
byte clocksecond;
bool waiting4ZeroSecond = true;
struct tm *timeinfo;


//
//  Keypad Small global variables
//
int kpsValue = 0;
int *pDelay;
boolean beforeSun;
boolean changedMins = false;

//
//  Keyboard variables
//
#define INPUT_STR_SZ 24
int kbMaxCharCnt = INPUT_STR_SZ;
void (*fpKeyboardPP)() = NULL;
void (*fpTimeConfigPP)() = NULL;
int kbStringIndex = 0;
char kbString[INPUT_STR_SZ + 2];
char kbTitle[40];
#define NAME_MAX_LEN 14

///////////////////////////////////////////////////////////
//
//
//
//
void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector  
  pinMode(REPEAT_CAL_PIN, INPUT);

  Serial.begin(115200);
  Serial.println("");
  Serial.println(FILE_NAME);
  // Combined string in RAM
  //Serial.println( "Compiled: " __DATE__ ", " __TIME__ ", " __VERSION__);
  Serial.print( F("Compiled: "));
  Serial.print( F(__DATE__));
  Serial.print( F(", "));
  Serial.print( F(__TIME__));
  Serial.print( F(", "));
  Serial.println( F(__VERSION__));

  sprintf(ideVer, "IDE Version: %d.%d.%d", ARDUINO / 10000, (ARDUINO / 100) % 100, ARDUINO % 100); 
  Serial.print(F( "Arduino IDE version: "));
  Serial.print(ARDUINO / 10000, DEC);
  Serial.print(".");
  Serial.print((ARDUINO / 100) % 100, DEC);
  Serial.print(".");
  Serial.println(ARDUINO % 100, DEC);
  //
  //  Setup TFT
  //
  myTFT.begin();
  myTFT.setRotation(TFT_ROTATION); // 0 or 2 - Inverted to accomodate USB cable
  
  if (digitalRead(REPEAT_CAL_PIN) == 0)
  {
    Serial.println("Repeat TFT Calibration");
    calibrateTftTouch = true;
  }
  //
  //
  // Set I2c bus to 400kHz, default is 100kHz
  //
  //
  I2C_0.begin(SDA_0, SCL_0, 100000);    // RTC
  I2C_1.begin(SDA_1, SCL_1, 400000);    // ADCs
  //Wire.begin();
  //Wire.setClock(400000);
  Serial.println(I2C_0.getClock());
  Serial.println(I2C_1.getClock());
  
  initSPIFFS();           // Initialize SPIFFS file system

  pinMode(SD_CARD_DET, INPUT);
  delay(100);
  Serial.println(digitalRead(SD_CARD_DET));
  if(digitalRead(SD_CARD_DET) == 1) Serial.println("SD Card Missing");
  else Serial.println("SD CARD Present");
  
  //
  // Setup TFT LED
  //
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  
  touch_calibrate();

  myTFT.fillScreen(TFT_BLACK);
  //  myTFT.setSwapBytes(true);
  setGfxFont(NULL);
  myTFT.setTextSize(3);        // Text size multiplier = 3X
  myTFT.setTextColor(TFT_GREEN, TFT_BLACK);
  myTFT.setTextDatum(TC_DATUM);         // Center Text

  //
  //  Load Logging configuration
  //
  loadLogConfig();
  
  //
  // Load WiFi configuration
  //
  loadWiFiConfig();
  if(WiFiConfig.enabled)
  {
    // Initialize WiFi connection
    myTFT.drawString("Connecting", 160, 90);
    myTFT.drawString("to WiFi", 160, 120);
    if (initWiFi())
    {
      WiFi_Connect_Flag = true;
      Serial.println("WiFi Connected");
      myTFT.fillScreen(TFT_BLACK);
      myTFT.drawString("WiFi Connected", 160, 100);
      myTFT.drawString(WiFi.localIP().toString(),160, 140);
      delay(2000);
    }
    else
    {
      WiFi_Connect_Flag = false;
      Serial.println("WiFi Failed");
      myTFT.fillScreen(TFT_BLACK);
      myTFT.drawString("WiFi Failed", 160, 90);
      myTFT.drawString("to Connect", 160, 120);
      delay(2000);
    }
  }
  else    // Turn WiFi OFF
  {
    WiFi.mode(WIFI_OFF);
    btStop();
  } 
  
#ifdef FTP_SRVR
  if(WiFi_Connect_Flag && WiFiConfig.ftpEnabled)
  {
    Serial.println("Starting FTP Server");
    ftpSrv.begin(WiFiConfig.ftpUserName, WiFiConfig.ftpPassWord);
    Serial.printf("un: %s    pw: %s\n\r",WiFiConfig.ftpUserName, WiFiConfig.ftpPassWord);
  }
#endif


  myTFT.setTextDatum(TC_DATUM);         // Center Justify Text
  myTFT.fillScreen(TFT_BLACK);          // erase screen

  //
  // Initialize the Real Time Clock chip
  //
  if (RTC_init())
  {
    myTFT.drawString("RTC Connected", 160, 100);
    Serial.println("RTC Connected");
    delay(1000);
    if(WiFi_Connect_Flag)
    {
      
    }
  }
  else
  {
    myTFT.drawString("RTC Failed", 160, 90);
    myTFT.drawString("to Connect", 160, 120);
    delay(2000);
  }

#ifdef SD_SUPPORT
  init_SD();
#endif

#ifdef SIMPLE_FTP
  if(WiFi_Connect_Flag && WiFiConfig.ftpEnabled)
  {
    ftpSrv.setCallback(_callback);
    ftpSrv.setTransferCallback(_transferCallback);
    Serial.println("Starting Simple FTP Server");
    ftpSrv.begin(WiFiConfig.ftpUserName, WiFiConfig.ftpPassWord);
    Serial.printf("un: %s    pw: %s\n\r",WiFiConfig.ftpUserName, WiFiConfig.ftpPassWord);
  }
#endif

  //delay(60000);
  //  delay(10000)
  setGfxFont(FSS9);
  myTFT.setTextDatum(TL_DATUM);         // Left Justify Text
  myTFT.fillScreen(TFT_BLACK);          // erase screen
  //myTFT.setTextFont(4);
  myTFT.setTextSize(1);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  
  // configure the Time Zone
  configTZ();

  //Serial.print("Vcc = ");
  //Serial.println(emon1.readVcc()); 

  /* Get our time sync started */
  /* Set our position and a default timezone value */
  calcTZoffset();   // DST offset
  Serial.printf("DST offsetTZ = %d\n\r", offsetTZ);
  
  //
  //  Setup Time sync provider (NTP or RTC)
  //
  if(WiFiConfig.enabled && WiFi_Connect_Flag) 
  {
    setTime((time_t)getNtpTime());
    setSyncProvider(getNtpTime);
    setSyncInterval(60*60);       // 3600 seconds (1 hour)
  }
  else
  {
    setSyncProvider(time_provider);
    setSyncInterval(60*60);       // 3600 seconds (1 hour)
  }    

  //
  //  Initialize ADS1015 ADC's
  //
  Serial.println("Initialize ADC's");
  initChannels();
  initADS48();
  initADS49();  

  #ifdef CORE_0_TASK
  //create a task that will be executed in the readADC_Task() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    readADC_Task,   /* Task function. */
                    "ADC_Task",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 
#endif

  //
  //  Display Initial Screen
  //
  drawMainMenu();

}


///////////////////////////////////////////////////////////
//
//    Main LOOP
//
//
 int tstv = 0;
 //
void loop()
{
#ifdef DS3231_RTC
    //
    //  RTC alarm #2 interrupt (occurs every minute)
    //
    if (rtc.alarmFired(ALARM_2))  // clear RTC alarm #2 interrupt (occurs once a minute)
    {
      rtc.clearAlarm(ALARM_2);
      printLocalTime(); // Recalculate current time
    }
    //
    //  RTC alarm #1 interrupt (occurs every second)
    //
    if (rtc.alarmFired(ALARM_1))  // clear RTC alarm #1 interrupt (occurs every second)
    {
      rtc.clearAlarm(ALARM_1);
      logging();
     if(ledTimer) 
     {
       ledTimer--;
     }
     else digitalWrite(TFT_LED, LOW);
#ifdef TEMPERATURE_ENABLED
    checkTemp();
    if(temperatureF != prevTempF)
    {
      //myTFT.setCursor(5, pgLine12);   // x,y pixels
      clearLine(pgLine12);
      //myTFT.setCursor(5, pgLine12);
      //myTFT.print("Temperature = ");
      //myTFT.print(temperatureF);
      //myTFT.print("\x60""F  ");
      sprintf(chrBuf,"Temperature = %3d\x60""F  ",temperatureF);
      myTFT.drawString(chrBuf, 5, pgLine12);
      prevTempF = temperatureF;
    }
#endif

#ifdef DEBUG_SAMPLE_COUNT
    unsigned long timethen = millis();
    Irms = emon1.calcIrms(1978);
    unsigned long timenow = millis();
    Serial.print("Time ");
    Serial.println(timenow - timethen);
#endif
  }       // end of if(ALARM_1)
#endif    // DS3231_RTC

#ifdef RV3028_C7
  if (interruptTriggered) 
  {
    interruptTriggered = false;
    //
    // The following is required to get the time 
    //  display to update exactly on the minute.
    //  This code is only executed once
    //  at power-on or reset.
    //
    if(waiting4ZeroSecond)
    {
      time_t rawTime = rtc.getUnixTimestamp();
      timeinfo = localtime(&rawTime);
      if(timeinfo->tm_sec == 0)
      {
        waiting4ZeroSecond = false;
        rtc.startPeriodicCountdownTimer();    // Minutes
      }
    }
    //
    // This interrupt occurs once a Minute
    //
    if (rtc.isInterruptDetected(INTERRUPT_PERIODIC_COUNTDOWN_TIMER)) 
    {
      rtc.clearInterrupt(INTERRUPT_PERIODIC_COUNTDOWN_TIMER);
      printLocalTime(); // Recalculate current time
      if(menuState == MAIN_MENU)
      {
        displayTOD();
        displayLogStatus();
      }
    }   // end of One Minute interrupt processing
    //
    // This interrupt occurs every Second
    //
    if (rtc.isInterruptDetected(INTERRPUT_PERIODIC_TIME_UPDATE)) 
    {
      rtc.clearInterrupt(INTERRPUT_PERIODIC_TIME_UPDATE);
      logging();
      if(ledTimer)
      {
        ledTimer--;
      }
      else digitalWrite(TFT_LED, LOW);
#ifdef TEMPERATURE_ENABLED
      checkTemp();
      if(temperatureF != prevTempF)
      {
        //myTFT.setCursor(5, pgLine12);   // x,y pixels
        clearLine(pgLine12);
        //myTFT.setCursor(5, pgLine12);
        //myTFT.print("Temperature = ");
        //myTFT.print(temperatureF);
        //myTFT.print("\x60""F  ");
        sprintf(chrBuf,"Temperature = %3d\x60""F  ",temperatureF);
        myTFT.drawString(chrBuf, 5, pgLine12);
        prevTempF = temperatureF;
      }
#endif

#ifdef DEBUG_SAMPLE_COUNT
      unsigned long timethen = millis();
      Irms = emon1.calcIrms(1978);
      unsigned long timenow = millis();
      Serial.print("Time ");
      Serial.println(timenow - timethen);
#endif
    }    
    rtc.clearAllInterrupts();
  }   // end of RV3028_C7 RTC Interrupt processing
#endif

  //
  //
  //
  if(ftpTIP == false)
  {
    switch(menuState)
    {
      case MAIN_MENU:
      case CHAN_1_MENU:
      case CHAN_2_MENU:
      case CHAN_3_MENU:
      case CHAN_4_MENU:
        readNextChannel();
        break;
      default:
        break;
    }
  }
  //
  //
  //
  if(touchCheck())
  {
    digitalWrite(TFT_LED, HIGH);
    ledTimer = TFT_LED_TIMEOUT;
    processTouch(btnDecode(4,6));
    //Serial.printf("touch button %d\n\r",touchData.button);
  }
  //
  //    Display Main Menu or Channel Menu.
  //
  menuProcessor();

#ifdef FTP_SRVR
  if(WiFi_Connect_Flag)
  {
    //Serial.println("handleFTP");
    ftpSrv.handleFTP();
  }
#endif
#ifdef SIMPLE_FTP
  if(WiFi_Connect_Flag)
  {
    //Serial.println("handle_Simple_FTP");
    ftpSrv.handleFTP();
  }
#endif
}       // end of loop()

//////////////////////////////////////////////////////
//
//
//
void readNextChannel(void)
{
#ifndef CORE_0_TASK
  //
  //  Read Channel ADC
  //
  //    read one channel per Loop
  //
  switch(readChan)
  {
    case 1:
      chanData1.Irms = chan1readACcurrent();
      if(chanData1.Irms < 0.050) chanData1.Irms = 0.0;
      chanData1.watts = chanData1.Irms * (float)(CT1.lineV);
      if(abs(chanData1.prevIrms - chanData1.Irms) >= 0.050) chanData1.changed = true;
      // Logging
      if(chanData1.Irms >= 0.050) chanData1.load = true;
      else chanData1.load = false;
      //
      readChan = 2;
      break;
    case 2:
      chanData2.Irms = chan2readACcurrent();
      if(chanData2.Irms < 0.050) chanData2.Irms = 0.0;
      chanData2.watts = chanData2.Irms * (float)(CT2.lineV);
      if(abs(chanData2.prevIrms - chanData2.Irms) >= 0.050) chanData2.changed = true;
      if(chanData2.Irms >= 0.050) chanData2.load = true;
      else chanData2.load = false;
      readChan = 3;
      break;
    case 3:
      chanData3.Irms = chan3readACcurrent();
      if(chanData3.Irms < 0.050) chanData3.Irms = 0.0;
      chanData3.watts = chanData3.Irms * (float)(CT3.lineV);
      if(abs(chanData3.prevIrms - chanData3.Irms) >= 0.050) chanData3.changed = true;
      if(chanData3.Irms >= 0.050) chanData3.load = true;
      else chanData3.load = false;
      readChan = 4;
      break;
    case 4:
      chanData4.Irms = chan4readACcurrent();
      if(chanData4.Irms < 0.050) chanData4.Irms = 0.0;
      chanData4.watts = chanData4.Irms * (float)(CT4.lineV);
      if(abs(chanData4.prevIrms - chanData4.Irms) >= 0.050) chanData4.changed = true;
      if(chanData4.Irms >= 0.050) chanData4.load = true;
      else chanData4.load = false;
      readChan = 1;
      break;
  }
#endif
}

////////////////////////////////////////////////////////////
//
//  Print Local Time
//
void printLocalTime()
{
  Update_timeinfo();
  clockhour = timeinfo->tm_hour;
  clockminute = timeinfo->tm_min;
  clocksecond = timeinfo->tm_sec;
  Serial.println(timeinfo, "%A, %B %d %Y %H:%M:%S");
}

/////////////////////////////////////////////////////////
//
//  Calculate Timezone offset 
//    if tm_isdst is true (non-zero) add 1 hour to offset
//    otherwise use offest based on timezone for location.
//
//    Only called at startup or when tm_isdst changes.
//
void calcTZoffset(void)
{
  isdst = timeinfo->tm_isdst;     // Update global isdst with current value
  if(timeinfo->tm_isdst)
  {
    offsetTZ = tzConfig.tzOffset + 1;
  }
  else 
  {
    offsetTZ = tzConfig.tzOffset;
  }
}

////////////////////////////////////////////////////////
//
//  Configure the Time Zone - reads time zone configuration from SPIFFS.
//
void configTZ(void)
{
  if (!existsFileSPIFFS(fnTimeZoneConfig))
  {
    Serial.println("Creating TimeZone configuration file");
    // Americas, Los Angeles
    tzConfig.regionIndx = 1;    // Americas
    tzConfig.cityIndx = 74;     // Irvine, CA
    sprintf(tzConfig.tzInfo, "PST8PDT,M3.2.0,M11.1.0");
    wrtFileSPIFFS(fnTimeZoneConfig, (char *)&tzConfig, sizeof(tzConfig));
  }
  else
  {
    Serial.println("Reading TimeZone configuration file");
    rdFileSPIFFS(fnTimeZoneConfig, (char *)&tzConfig, sizeof(tzConfig));
    Serial.printf("RegionIndx = %d, CityIndx = %d\n\r",tzConfig.regionIndx, tzConfig.cityIndx);
    Serial.printf("TimeZone = %s\n\r", tzConfig.tzInfo);
  }
  setTZ();
}

///////////////////////////////////////////////////////////
//
//
//
void setTZ(void)
{
  Serial.println(tzConfig.tzInfo);
  setenv("TZ", tzConfig.tzInfo, 1);
  tzset();
  printLocalTime();
}

#ifdef TEMPERATURE_ENABLED
/////////////////////////////////////////
//
//    checkTemp()  --  Resistance Temperature Detector (RTD)
//
void checkTemp(void)
{
  //return;
  if( (millis() - time_now) > ckTperiod)
  {
    //
    //  Calculatione required to convert ADC value to temperature
    //
    //  1. Determine the average ADC value by reading multiple times.
    int samples = 0;
    for (int i = 0; i < RTD_ADC_SAMPLES; i++) 
    {
      samples += analogRead(ADC1_0);
      delay(10);
    }
    float average = samples / RTD_ADC_SAMPLES;
    Serial.print("ADC1_0 average = ");
    Serial.println(average);
    
    //  2. Calculate the ratio of the fixed resistor ADC_value to the 
    //      Thermistor ADC_value
    //          Ratio = ADC_value/(4096 - ADC_value)
    float Ratio = average/(4096.0 - average);
    
    //  3. Using the Ratio, calculate the Thermistor resistance 
    //        Where Rfixed = 1500 ohms 
    //          Rtherm = Rfixed * Ratio
    float Rtd = Ratio * 1500.0;
    Serial.print("Rtd = ");
    Serial.println(Rtd);
    
    //  4. Using the known Thermistor resistance at a benchmark temperature
    //          940 ohms at 25 degrees C
    //          3.9 ohms per degree C
    //      Calculate the Thermistor resistance delta from the benchmark
    //          Rdelta = Rtherm - 940
    float Rdelta = (Rtd - 940.0);
    Serial.print("Rdelta = ");
    Serial.println(Rdelta);
    
    //      Calculate the Thermistor temperature delta
    //          Tdelta = Rdelta / 3.9
    float Tdelta = Rdelta / 3.9;
    Serial.print("Tdelta = ");
    Serial.println(Tdelta);
    
    //  5.  Finally calculate the temperature by adding the calculated 
    //        temperature delta to the benchmark temperature
    //          TemperatureC = Tdelta + 25
    // 
    //
    temperatureC = Tdelta + 25;
    Serial.print("TemperatureC = ");
    Serial.println(temperatureC);
    temperatureF = temperatureC * 9/5 + 32;
    Serial.print("TemperatureF = ");
    Serial.println(temperatureF);
    if(temperatureF != prevTempF)
    {  

    }
    time_now = millis();
  }
  //if((temperatureF < 30) || (temperatureF > 500)) ErrorState(1);
}
#endif

/////////////////////////////////////////
//
//
time_t getNtpTime()
{
  timeClient.update();
  epochTime = timeClient.getEpochTime();    //-946684800UL;
  epochTimeValid = true;
  Serial.print("timeClient.getEpochTime = ");
  Serial.println(epochTime);
#ifdef DS3231_RTC
  rtc.adjust(epochTime);
  DateTime now = rtc.now();
  Serial.print("rtc.now = ");
  Serial.println(now.unixtime());
  unsigned long secsSince1900 = now.unixtime();
  return(secsSince1900);
#endif
#ifdef RV3028_C7
  rtc.setUnixTimestamp(epochTime,true);
  //rtc.synchronize();
  unsigned long secsSince1900 = rtc.getUnixTimestamp();
  Serial.print("rtc.now = ");
  Serial.println(secsSince1900);
  return (secsSince1900);
#endif
}

void logData(void)
{
  Update_timeinfo();
  clockhour = timeinfo->tm_hour;
  clockminute = timeinfo->tm_min;
  clocksecond = timeinfo->tm_sec;
  //Serial.println(timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.printf("%0.2d:%0.2d:%0.2d ", clockhour, clockminute, clocksecond);
  if(FanOn) Serial.print("Fan=ON ");
  else Serial.print("Fan=OFF ");
  if(AugerOn) Serial.print("Auger=ON ");
  else Serial.print("Auger=OFF ");
  if(HeaterOn) Serial.print("Heater=ON ");
  else Serial.print("Heater=OFF ");
  Serial.print("temp=");
  Serial.print(temperatureF);
  Serial.print("°F ");
  Serial.println("");
}
