

/////////////////////////////////////////////////////////////////
//
//  Called from main polling loop() if touch detected.
//
//  touchData struct contains latest touch info
//
void processTouch(int button)
{
  //  Serial.println("processTouch");
  switch(menuState)
  {
    case MAIN_MENU:
      processMainInput(button);
      break;
    case CHAN_1_MENU:
      pChanConfig = &CT1;
      pChanData = &chanData1;
      processChannel(1, button);
      break;
    case CHAN_2_MENU:
      pChanConfig = &CT2;
      pChanData = &chanData2;
      processChannel(2, button);
      break;
    case CHAN_3_MENU:
      pChanConfig = &CT3;
      pChanData = &chanData3;
      processChannel(3, button);
      break;
    case CHAN_4_MENU:
      pChanConfig = &CT4;
      pChanData = &chanData4;
      processChannel(4, button);
      break;
    case CHAN_CONFIG_MENU:
      processChanConfig(button);
      break;
    //case VOLTAGE_MENU:
      //processLineVPage(button);
      //break;
    case VOLTAGE_KPAD:
      processVoltageKeypad();
      break;
    case KEYBOARD_MENU:
      if(touchKeyboard())
      {
        processKbInput();
      }
      break;
    case TZ_MENU:
      processTzMenu(button);
      break;
    case REGION_MENU:
      processRegionMenu(button);
      break;
    case CITY_MENU:
      processCityMenu(button);
      break;
    case WIFI_MENU:
      processWiFiMenu(button);
      break;
    case SSID_MENU:
      processSsidMenu(button);
      break;
   //case PW_MENU:
      //processPwMenu(button);
      //break;
    case FTP_MENU:
      processFtpMenu(button);
      break;
    case LOG_MENU:
      processLogMenu(button);
      break;
    case ELOG_MENU:
      processEventMenu(button);
      break;
    case ELOG_CT_MENU:
      processEventCTMenu(button);
      break;
    case ELOG_KPAD:
      processEventKeypad();
      break;
    case ILOG_MENU:
      processIntervalMenu(button);
      break;
    case ILOG_KPAD:
      processIntervalKeypad();
      break;
    case SD_MENU:
      processSD_Menu(button);
      break;
    case ABOUT_MENU:
      processAboutMenu(button);
      break;
    case SYSTEM_MENU:
      processSystemMenu(button);
      break;
    default:
      Serial.printf("UNKNOWN_MENU %d\n\r", menuState);
      break;
  }

}

/////////////////////////////////
//
//
//
void processMainInput(int button)
{
  switch(button)
  {
    case 5:
      pushMenu(CHAN_1_MENU);
      pChanConfig = &CT1;
      pChanData = &chanData1;
      pChanData->changed = true;
      break;
    case 9:
      pushMenu(CHAN_2_MENU);
      pChanConfig = &CT2;
      pChanData = &chanData2;
      pChanData->changed = true;
      break;
    case 13:
      pushMenu(CHAN_3_MENU);
      pChanConfig = &CT3;
      pChanData = &chanData3;
      pChanData->changed = true;
      break;
    case 17:
      pushMenu(CHAN_4_MENU);
      pChanConfig = &CT4;
      pChanData = &chanData4;
      pChanData->changed = true;
      break;
    case 21:
      pushMenu(SYSTEM_MENU);
      break;
  }
}

void processChannel(int chan, int button)
{
  switch(button)
  {
    case 21:        // Setup
      prevChanConfig = *pChanConfig;
      pushMenu(CHAN_CONFIG_MENU);
      break;
    case 24:        // Exit
      popMenu();
      break;
  }
}

void processChanConfig(int button)
{
  boolean change = true;
  Serial.printf("x=%d  y=%d \n\r", touchData.x, touchData.y);
  switch(button)
  {
    case 5:     // 5 Amp CT
      pChanConfig->range = 5.0;
      pChanData->fullScale = 8.0;
      break;
    case 6:     // 10 Amp CT
      pChanConfig->range = 10.0;
      pChanData->fullScale = 16.0;
      break;
    case 7:     // 15 Amp CT
      pChanConfig->range = 15.0;
      pChanData->fullScale = 16.0;
      break;
    case 8:     // 20 Amp CT
      pChanConfig->range = 20.0;
      pChanData->fullScale = 24.0;
      break;
    case 9:     // 25 Amp CT
      pChanConfig->range = 25.0;
      pChanData->fullScale = 32.0;
      break;
    case 10:     // 30 Amp CT
      pChanConfig->range = 30.0;
      pChanData->fullScale = 32.0;
      break;
    case 11:     // 50 Amp CT
      pChanConfig->range = 50.0;
      pChanData->fullScale = 56.0;
      break;
    case 12:     // 100 Amp CT
      pChanConfig->range = 100.0;
      pChanData->fullScale = 104.0;
      break;
    case 18:
    case 19:
      tmpLineV = pChanConfig->lineV;
      pushMenu(VOLTAGE_KPAD);
      change = false;
      break;
    case 21:          // enabled = false
      pChanConfig->enabled = false;
      break;
    case 22:          // enabled  = true
      pChanConfig-> enabled = true;
      break;
    case 24:          // Exit
      saveChanConfig();
      popMenu();
      change = false;
      break;
    default:
      change = false;
      break;
  }
  if(change == true) 
  {
    drawChanConfigInfo();
  }
}



////////////////////////////////
//
//
//
void processVoltageKeypad(void)
{
  char vbuf[16];
  //Serial.println("processVoltageKeypad");
  int key = processKpTouch(&iKp);
  //Serial.printf("Key = %d\n\r", key);
  if(key == 11) 
  {
    if( (tmpLineV > 80) && (tmpIntValue < 300) )
    {
      pChanConfig->lineV = tmpLineV;
      //changedLogConfig = true;
    }
    popMenu();
  }
  else
  {
    if(key == 10) tmpLineV = tmpLineV / 10; // deletes right-most digit
    else if((key >= 0) && (key < 10))
    {
      tmpLineV = tmpLineV * 10 + key;
    }
    //Serial.printf("Value = %d\n\r", tmpLineV);
    sprintf(vbuf, "%d Vac", tmpLineV);
    displayValueOnKeypad(&iKp, vbuf);
    // redisplay value
  }
}

///////////////////////////////////////////
//
//
//
void processAboutMenu(int button)
{
  switch(button)
  {
    case 21:        // Restart
      restart();
      break;
    case 23:        // Cancel
      popMenu();
      //change = false;
      break;
    case 24:
      popMenu();    // Exit & Save
      break;
  }
}

void processSystemMenu(int button)
{
  switch(button)
  {
    case 5:
      strncpy(tempSSID, WiFiConfig.ssID, strlen(WiFiConfig.ssID) + 1);    //32);
      pushMenu(WIFI_MENU);
      break;
    case 9:             // Logging
      changedLogConfig = false;
      pushMenu(LOG_MENU);
      break;
    case 13:
      initTzTemp();
      pushMenu(TZ_MENU);
      break;
    case 17:
      pushMenu(SD_MENU);
      break;
    case 21:
      pushMenu(ABOUT_MENU);
      break;
    case 24:
      popMenu();    // Exit & Save
      break;
  }
}
