///////////////////////////////////////////////
//
// used by setSyncProvider()
//
time_t time_provider()
{
#ifdef DS3231_RTC
  return rtc.now().unixtime(); 
#endif
#ifdef RV3028_C7
  return rtc.getUnixTimestamp();
#endif
}


/////////////////////////////////////////////////////
//
//
//
long syncTime(void)
{
  int timeOffset = 0;
  long actualTime = 0;
  //Connect to Wifi
  //  WiFi.disconnect();
  //  WiFi.reconnect();
  if(WiFi_Connect_Flag)
  {
    timeClient.begin();
    timeClient.setTimeOffset(timeOffset);
    //  while (!timeClient.update()) {
    timeClient.forceUpdate();
    //  }
    //  timeClient.update();
    actualTime = timeClient.getEpochTime();
#ifdef DS3231_RTC  
    rtc.adjust(DateTime(actualTime));
#endif
#ifdef RV3028_C7
    rtc.setUnixTimestamp(actualTime);
    rtc.synchronize();
#endif
    Serial.print("Internet Epoch Time: ");
    Serial.println(actualTime);
  }
#ifdef DS3231_RTC
  DateTime now = rtc.now();
  Serial.print("RTC Epoch Time: ");
  Serial.println(now.unixtime());
#endif
#ifdef RV3028_C7
  Serial.print("RTC Epoch Time: ");
  Serial.println(rtc.getUnixTimestamp());
#endif
  //disconnect WiFi after update
  //  disconnectWiFi();

  return (actualTime);
}

///////////////////////////////////////////////
//
//
//
bool RTC_init(void)
{
  //  Serial.println("Initializing RTC");
  if (!rtc.begin(I2C_0)) {
    Serial.println("Couldn't find RTC");
    delay(5000);
    return false;
  }
  Serial.println("Initializing RTC");
#ifdef DS3231_RTC
#ifdef RTC_INT_PIN 
  pinMode(RTC_INT_PIN, INPUT_PULLUP);
#endif
  rtc.disableAlarm(ALARM_1);      //rtc.alarmInterrupt(ALARM_1, false);
  rtc.disableAlarm(ALARM_2);      //rtc.alarmInterrupt(ALARM_2, false);
  rtc.writeSqwPinMode(DS3231_OFF );    //rtc.squareWave(SQWAVE_NONE);
  rtc.clearAlarm(ALARM_1);
  rtc.clearAlarm(ALARM_2);
  // set alarm 1 to occur every second
  rtc.setAlarm1( dt, DS3231_A1_PerSecond);     //    rtc.setAlarm(ALM1_EVERY_SECOND, 0, 0, 0, 0);
  // set alarm 2 to occur every minute
  rtc.setAlarm2( dt, DS3231_A2_PerMinute);

  //  Serial.println("RTC: Waiting to Start....");
  delay(1000);

  DateTime now = rtc.now();
  Serial.print("rtc.now = ");
  Serial.println(now.unixtime());
#endif
#ifdef RV3028_C7
  pinMode(RTC_INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(RTC_INT_PIN), rtcInterruptHandler, FALLING);
  //
  // To interrupt every Minute use:
  //        PeriodicCountdownTimer
  //
  //  Interrupt every Minute
  //
  rtc.setPeriodicCountdownTimer(1, TIMER_MINUTE, true);
  rtc.enableInterrupt(INTERRUPT_PERIODIC_COUNTDOWN_TIMER);
  //rtc.startPeriodicCountdownTimer();
  
  //
  // To interrupt every Second use;
  //        PeriodicTimeUpdate
  //
  //  Interrupt every Second
  //
  rtc.setPeriodicTimeUpdate(USEL_SECOND);
  rtc.enableInterrupt(INTERRPUT_PERIODIC_TIME_UPDATE);
  //rtc.startPeriodicTimeUpdate();

//
//
//  Backup Power Switchover Modes
//
#define SW_OVER_MASK 0x0C
#define SW_OVER_MASK_INVERT 0xf3
#define DSM 0x04      // Direct Switching Mode, when Vdd < Vbackup
#define LSM 0x0C      // Level Switching Mode, when Vdd < 2.0V and Vbackup > 2.0V
//
  Serial.print(" EEPROM 37h = ");
  uint8_t EEPROM37 = rtc.readByteFromEEPROM(0x37);
  Serial.println(EEPROM37,HEX);
#if 1
  if( (EEPROM37 & SW_OVER_MASK) != DSM)
  {
    Serial.println("Changing RTC backup to DSM");
    rtc.writeByteToEEPROM(0x37, (EEPROM37 & SW_OVER_MASK_INVERT) | DSM);
  }
#else
  if( (EEPROM37 & SW_OVER_MASK) != LSM)
  {
    Serial.println("Changing RTC backup to LSM");
    rtc.writeByteToEEPROM(0x37, (EEPROM37 & SW_OVER_MASK_INVERT) | DSM);
  } 
#endif
  Serial.print(" EEPROM 37h = ");
  EEPROM37 = rtc.readByteFromEEPROM(0x37);
  Serial.println(EEPROM37,HEX);
#endif

  syncTime();
  
#ifdef RV3028_C7
  rtc.startPeriodicTimeUpdate();        // Seconds
  waiting4ZeroSecond = true;
  //rtc.startPeriodicCountdownTimer();    // Minutes
#endif
  return true;
}


#ifdef RV3028_C7
//////////////////////////////////////////////
//
//
//
void rtcInterruptHandler() 
{ 
  interruptTriggered = true; 
}
#endif
