
////////////////////////////////////////
//
//  drawMenu - ONLY called from pushMenu() and popMenu()
//
void drawMenu(int d_menu)
{
  switch(d_menu)
  {
    case MAIN_MENU:
      drawMainMenu();
      break;
    case CHAN_1_MENU:
      pChanData = &chanData1;
      pChanConfig = &CT1;
      drawChanInfo(1);
      break;
    case CHAN_2_MENU:
      pChanData = &chanData2;
      pChanConfig = &CT2;
      drawChanInfo(2);
      break;
    case CHAN_3_MENU:
      pChanData = &chanData3;
      pChanConfig = &CT3;
      drawChanInfo(3);
      break;
    case CHAN_4_MENU:
      pChanData = &chanData4;
      pChanConfig = &CT4;
      drawChanInfo(4);
      break;
    case CHAN_CONFIG_MENU:
      drawChanConfigInfo();
      break;
    case VOLTAGE_KPAD:
      displayVoltageKeypad();
      break;
    case KEYBOARD_MENU:
      drawKbPage();
      break;
    case TZ_MENU:
      displayTzMenu();
      break;
    case REGION_MENU:
      displayRegionMenu();
      break;
    case CITY_MENU:
      displayCityMenu();
      break;
    case WIFI_MENU:
      displayWiFiMenu();
      break;
    case SSID_MENU:
      displaySsidMenu();
      break;
    case FTP_MENU:
      displayFtpMenu();
      break;
    case LOG_MENU:
      displayLogMenu();
      break;
    case ELOG_MENU:
      displayEventMenu();
      break;
    case ELOG_CT_MENU:
      displayCTneLog();
      break;
    case ILOG_MENU:
      displayIntervalMenu();
      break;
    case ILOG_KPAD:
      displayIntervalKeypad();
      break;
    case ELOG_KPAD:
      displayEventKeypad();
      break;
    case SD_MENU:
      displaySD_Menu();
      break;
    case ABOUT_MENU:
      displayAbout();
      break;
    case SYSTEM_MENU:
      drawSysInfo();
      break;
  }
}



///////////////////////////////////////////
//
//
void drawBlankPage(boolean option)
{
  //  setup TFT
  setGfxFont(FSS9);
  myTFT.setTextDatum(TL_DATUM);         // Left Justify Text
  myTFT.setTextSize(1);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  // clear screen
  myTFT.fillScreen(TFT_BLACK);          // erase screen
  //  draw outline
  //if(option)myTFT.drawRoundRect(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, 2, TFT_YELLOW);
  //delay(2000);
}

////////////////////////////////////////
//
//
//
void drawPageHeader(String title1, String title2, bool includeTOD)
{
  drawBlankPage(false);
  myTFT.drawFastHLine(0, 70, 319, TFT_YELLOW);
  myTFT.drawFastHLine(0, 73, 319, TFT_YELLOW);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  myTFT.setTextDatum(MC_DATUM);
  setGfxFont(FSS12);
  if(title2.length() != 0)
  {
    //setGfxFont(FSS12); 
    myTFT.drawString(title1, 160, 15);
    myTFT.drawString(title2, 160, 45);
  }
  else
  {
    //setGfxFont(FSS18);
    myTFT.drawString(title1, 160, 30);
  }
  if(includeTOD)
  {
    displayTOD();
    displayLogStatus();
  }
}

///////////////////////////////////////////////////////
//
//    Called from setup() for initial screen.
//    Called from drawMenu() as a result of a pushMenu() or popMenu()
//
void drawMainMenu(void)
{
  pushTA();
  drawPageHeader("AC Amp Meter","4 Channel", true);

  drawBtn5("CT-1");    
  drawBtn9("CT-2");
  drawBtn13("CT-3");
  drawBtn17("CT-4");
  
  setGfxFont(FSS12);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  myTFT.setTextDatum(MC_DATUM); 
  
  displayMainCTx(1);
  displayMainCTx(2);
  displayMainCTx(3);
  displayMainCTx(4);

  myTFT.drawFastHLine(0,395,319,TFT_YELLOW);   // 410  413

  drawBtn21d("System", "Setup");
  popTA();
}

///////////////////////////////////////////////
//
//    121, 199, 277, 355,
//
void displayMainCTx(int CTx)
{
  char charBuf[16];
  pushTA();
  //setGfxFont(FSS18);
  setGfxFont(FSS12);
  myTFT.setTextDatum(MC_DATUM);         // Middle-Center Text
  switch(CTx)
  {
    case 1:
      myTFT.fillRoundRect(88, 89, 220, 67, 10, TFT_BLACK);
      myTFT.drawRoundRect(88, 89, 220, 67, 10, TFT_LIGHTGREY);
      if(!CT1.enabled) 
      {
        myTFT.setTextColor(TFT_RED, TFT_BLACK);
        myTFT.drawString("OFF", 200, 121);
      }
      else 
      {
        myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
        //sprintf(charBuf,"%3.1fA %3.1fW",chanData1.Irms, chanData1.watts);
        //myTFT.drawString(charBuf, 200, 121);
        sprintf(charBuf,"%3.2f Amps", chanData1.Irms);
        myTFT.drawString(charBuf, 200, 107);
        sprintf(charBuf,"%4.1f Watts", chanData1.watts);
        myTFT.drawString(charBuf, 200, 135);
      }
      break;
    case 2:
      myTFT.fillRoundRect(88, 167, 220, 67, 10, TFT_BLACK);
      myTFT.drawRoundRect(88, 167, 220, 67, 10, TFT_LIGHTGREY);
      if(!CT2.enabled) 
      {
        myTFT.setTextColor(TFT_RED, TFT_BLACK);
        myTFT.drawString("OFF", 200, 199);
      }
      else 
      {
        myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
        //sprintf(charBuf,"%3.2f A",chanData2.Irms);
        //myTFT.drawString(charBuf, 200, 199);
        sprintf(charBuf,"%3.2f Amps", chanData2.Irms);
        myTFT.drawString(charBuf, 200, 185);
        sprintf(charBuf,"%4.1f Watts", chanData2.watts);
        myTFT.drawString(charBuf, 200, 213);
      }
      break;
    case 3:
      myTFT.fillRoundRect(88, 245, 220, 67, 10, TFT_BLACK);
      myTFT.drawRoundRect(88, 245, 220, 67, 10, TFT_LIGHTGREY);
      if(!CT3.enabled) 
      {
        myTFT.setTextColor(TFT_RED, TFT_BLACK);
        myTFT.drawString("OFF", 200, 277);
      }
      else 
      {
        myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
        //sprintf(charBuf,"%3.2f A",chanData3.Irms);
        //myTFT.drawString(charBuf, 200, 277);
        sprintf(charBuf,"%3.2f Amps", chanData3.Irms);
        myTFT.drawString(charBuf, 200, 263);
        sprintf(charBuf,"%4.1f Watts", chanData3.watts);
        myTFT.drawString(charBuf, 200, 291);
      }
      break;
    case 4:
      myTFT.fillRoundRect(88, 323, 220, 67, 10, TFT_BLACK);
      myTFT.drawRoundRect(88, 323, 220, 67, 10, TFT_LIGHTGREY);
      if(!CT4.enabled) 
      {
        myTFT.setTextColor(TFT_RED, TFT_BLACK);
        myTFT.drawString("OFF", 200, 355);
      }
      else 
      {
        myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
        //sprintf(charBuf,"%3.2f A",chanData4.Irms);
        //myTFT.drawString(charBuf, 200, 355);
        sprintf(charBuf,"%3.2f Amps", chanData4.Irms);
        myTFT.drawString(charBuf, 200, 341);
        sprintf(charBuf,"%4.1f Watts", chanData4.watts);
        myTFT.drawString(charBuf, 200, 369);
      }
      break;
  }
  popTA();
}

////////////////////////////////////////////////
//
//  Display Time-Of-Day
//        for display on MAIN_MENU only !!!
//
void displayTOD(void)
{
  sprintf(TOD,"%0.2d:%0.2d ", clockhour, clockminute);
  pushTA();
  setGfxFont(FSS9);
  myTFT.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  myTFT.setTextDatum(MC_DATUM);
  myTFT.drawString(TOD, 286, 56);
  popTA();
}

////////////////////////////////////////////////
//
//  Display Logging Status
//        for display on MAIN_MENU only !!!
//
void displayLogStatus(void)
{
  if(LogConfig.state > LOG_STOP)
  {
    pushTA();
    setGfxFont(FSS9);
    myTFT.setTextColor(TFT_SKYBLUE, TFT_BLACK);
    myTFT.setTextDatum(MC_DATUM);
    myTFT.drawString("Logging", 35, 56);
    popTA();
  }
}

/////////////////////////////////////////////////
//
//
//
void drawChanInfo(int chanNum)
{
  char charBuf[16];
  pushTA();
  sprintf(charBuf, "Channel %d",pChanConfig->index+1);
  drawPageHeader(charBuf,"", false);
  ampMeter(chanNum, 10, 100, pChanData->fullScale);

  //myTFT.setTextSize(2);
  setGfxFont(FSS18);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  myTFT.setTextDatum(MC_DATUM);         // Middle-Center Text
  myTFT.fillRect(10,255,290,100, TFT_BLACK);   // clear text area
  sprintf(charBuf,"%3.2f Amps",pChanData->Irms);
  myTFT.drawString(charBuf, 160, 280);
  sprintf(charBuf,"%3.1f Watts",pChanData->Irms * (float)(pChanConfig->lineV));
  myTFT.drawString(charBuf, 160, 330);

  drawBtn21("Setup");
  drawBtnExit();
  popTA();
}

//
//  Channel ON/OFF Switch
//
SWITCH_STRUCT chanSw = {
  0,
  true,         // bool horiz; 
  80,          // int xPos;       
  420,          // int yPos;      
  80,           // int xSize;
  35,           // int ySize;
  15,           // int swRadius;
  SW_TXT_BOTH,  // int textPos;   
};

//////////////////////////////////////////
//
//    Requires that pChanConfig point to the appropriate channel config struct.
//
//
void drawChanConfigInfo()
{
  char charBuf[32];
  pushTA();
  sprintf(charBuf, "Channel %d",pChanConfig->index+1);
  drawPageHeader(charBuf,"", false);
  setGfxFont(FSS12);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  myTFT.setTextDatum(TC_DATUM);  

  drawSwitch( chanSw, pChanConfig->enabled);
  myTFT.drawString("Current Transformer (CT)", 160, 245);
  drawBtn5d("5", "Amp");
  drawBtn6d("10", "Amp");
  drawBtn7d("15", "Amp");
  drawBtn8d("20", "Amp"); 
  drawBtn9d("25", "Amp");
  drawBtn10d("30", "Amp");
  drawBtn11d("50", "Amp");
  drawBtn12d("100", "Amp");
  switch((int)pChanConfig->range)
  {
    case 5: 
      drawBtn(5, TFT_SKYBLUE, "5", "Amp");
      break;
    case 10: 
      drawBtn(6, TFT_SKYBLUE, "10", "Amp");
      break;
    case 15: 
      drawBtn(7, TFT_SKYBLUE, "15", "Amp");
      break;
    case 20: 
      drawBtn(8, TFT_SKYBLUE, "20", "Amp");
      break;
    case 25: 
      drawBtn(9, TFT_SKYBLUE, "25", "Amp");
      break;
    case 30: 
      drawBtn(10, TFT_SKYBLUE, "30", "Amp");
      break;
    case 50: 
      drawBtn(11, TFT_SKYBLUE, "50", "Amp");
      break;
    case 100: 
      drawBtn(12, TFT_SKYBLUE, "100", "Amp");
      break;
  }
  myTFT.drawFastHLine(0,275,319,TFT_YELLOW);
  setGfxFont(FSS12);

  myTFT.fillRoundRect(50, 310, 220, 67, 10, TFT_BLACK);
  myTFT.drawRoundRect(50, 310, 220, 67, 10, TFT_YELLOW);
  myTFT.fillRoundRect(90, 300, 140, 20, 5, TFT_BLACK); 
  myTFT.drawRoundRect(90, 300, 140, 20, 5, TFT_WHITE);
  setGfxFont(FM9);     //FSS9
  myTFT.setTextDatum(CC_DATUM);
  myTFT.drawString("Line Voltage", 160, 307, GFXFF);
  
  setGfxFont(FSS18);
  myTFT.setTextColor(TFT_GREEN, TFT_BLACK); 
  sprintf(charBuf, "%d Vac", pChanConfig->lineV);
  myTFT.drawString(charBuf, 160, 350);
  
  drawSwitch( chanSw, pChanConfig->enabled);
  drawBtnExit();
  popTA();
}

////////////////////////////////////////////////
//
//  Line Voltage
//
void drawLineVInfo(void)
{
  char charBuf[32];
  int voltage = pChanConfig->lineV;
  pushTA();
  drawBlankPage(true);
  setGfxFont(FSS18);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  myTFT.setTextDatum(TC_DATUM);  
  sprintf(charBuf, "Channel %d",pChanConfig->index+1);
  myTFT.drawString(charBuf, 160, 25);
  myTFT.drawFastHLine(0,80,319,TFT_YELLOW);
  myTFT.drawFastHLine(0,83,319,TFT_YELLOW);
  setGfxFont(FSS12);
  myTFT.drawString("Line Voltage", 160, 120); 
  setGfxFont(FSS18);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  myTFT.drawRect( 55, 200, 70, 70, TFT_YELLOW);
  myTFT.drawRect( 125, 200, 70, 70, TFT_YELLOW);
  myTFT.drawRect( 195, 200, 70, 70, TFT_YELLOW);
  myTFT.fillTriangle( 90, 160, 70, 190, 110, 190, TFT_GREEN);
  myTFT.fillTriangle( 160, 160, 140, 190, 180, 190, TFT_GREEN);
  myTFT.fillTriangle( 230, 160, 210, 190, 250, 190, TFT_GREEN);

  myTFT.fillTriangle( 90, 310, 70, 280, 110, 280, TFT_GREEN);
  myTFT.fillTriangle( 160, 310, 140, 280, 180, 280, TFT_GREEN);
  myTFT.fillTriangle( 230, 310, 210, 280, 250, 280, TFT_GREEN);

  myTFT.drawNumber( voltage / 100, 90, 218);
  myTFT.drawNumber( (voltage / 10) % 10, 160, 218);
  myTFT.drawNumber( voltage % 10, 230, 218); 

  myTFT.drawFastHLine(0,380,319,TFT_YELLOW);
  myTFT.drawFastHLine(0,383,319,TFT_YELLOW);
  //drawBtn(23, TFT_GREEN, "Cancel", "");
  drawBtnCancel();
  //drawBtn(24, TFT_GREEN, "EXIT", "");
  drawBtnExit();
  popTA();
}

//////////////////////////////////
//
//
//
void displayVoltageKeypad(void)
{
  char vbuf[16];
  pushTA();
  drawKeypad( &iKp);
  sprintf(vbuf, "%d Vac", tmpLineV);
  displayValueOnKeypad(&iKp, vbuf);
  popTA();
}


////////////////////////////////////////////////////////
//
//
//
void displayAbout(void)
{
  char aBuf[48];
  pushTA();
  drawBlankPage(false);
  myTFT.setTextDatum(TC_DATUM);
  setGfxFont(FSS12);
  myTFT.drawRoundRect(2, 0, 318, 110, 10, TFT_BLUE);
  myTFT.drawRoundRect(4, 2, 314, 106, 10, TFT_BLUE);
  myTFT.drawString(FILE_NAME, 160, 15);
  myTFT.drawString(F(__DATE__), 160, 45);
  myTFT.drawString(ideVer, 160, 75);
  myTFT.drawRoundRect(2, 120, 318, 170, 10, TFT_BLUE);
  myTFT.drawRoundRect(4, 122, 314, 166, 10, TFT_BLUE);
  myTFT.drawString("File system", 160, 135);
  myTFT.setTextDatum(TL_DATUM);
  sprintf(aBuf, "File Count:  %d", spiffsInfo.entryCount);
  myTFT.drawString(aBuf, 15, 165);
  sprintf(aBuf, "Total space:  %d", spiffsInfo.totalBytes);
  myTFT.drawString(aBuf, 15, 195);
  sprintf(aBuf, "Used space:  %d", spiffsInfo.usedBytes);
  myTFT.drawString(aBuf, 15, 225);
  sprintf(aBuf, "Available:  %d", spiffsInfo.availBytes);
  myTFT.drawString(aBuf, 15, 255);
  myTFT.setTextDatum(TC_DATUM);
  //myTFT.drawRect(2, 300, 318, 80, TFT_BLUE);
  myTFT.drawRoundRect(2, 300, 318, 80, 10, TFT_BLUE);
  myTFT.drawRoundRect(4, 302, 314, 76, 10, TFT_BLUE);
  myTFT.drawString("Date / Time", 160, 315);
  strftime(chrBuf, sizeof(chrBuf), "%a, %b %d %Y   %H:%M", timeinfo);
  myTFT.drawString(chrBuf, 160, 350);
  //drawBtn(21, TFT_GREEN, "Restart", "");
  drawBtn21("Restart");
  //drawBtn(24, TFT_GREEN, "Exit", "");
  drawBtnExit();
  popTA();
}

///////////////////////////////////////////
//
//
//
void drawSysInfo(void)
{ 
  pushTA();
  drawPageHeader("System Settings","", false);
  setGfxFont(FSS12);
  drawBtn5("WiFi");
  myTFT.fillRoundRect(88, 89, 220, 67, 10, TFT_BLACK);
  myTFT.drawRoundRect(88, 89, 220, 67, 10, TFT_LIGHTGREY);
  myTFT.drawString("WiFi & FTP", 200, 105); 
  myTFT.drawString("Settings", 200, 135); 
  drawBtn9("Log");
  myTFT.fillRoundRect(88, 167, 220, 67, 10, TFT_BLACK);
  myTFT.drawRoundRect(88, 167, 220, 67, 10, TFT_LIGHTGREY);
  myTFT.drawString("Logging", 200, 183);  
  myTFT.drawString("Configuration", 200, 213);
  //drawBtn(13, TFT_GREEN, "Clock", "");
  drawBtn13("Clock");
  myTFT.fillRoundRect(88, 245, 220, 67, 10, TFT_BLACK);
  myTFT.drawRoundRect(88, 245, 220, 67, 10, TFT_LIGHTGREY);
  myTFT.drawString("Clock Time Zone", 200, 261);  
  myTFT.drawString("Settings", 200, 291);
  drawBtn17d("SD","Card");
  myTFT.fillRoundRect(88, 323, 220, 67, 10, TFT_BLACK);
  myTFT.drawRoundRect(88, 323, 220, 67, 10, TFT_LIGHTGREY);
  myTFT.drawString("SD Card", 200, 339);  
  myTFT.drawString("Settings", 200, 369);  
  drawBtn21("About");
  myTFT.drawFastHLine(0,395,319,TFT_YELLOW);
  drawBtnExit();
  popTA();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////
//
//  menuProcessor - called from main loop()
//          Each menu processor updates any changing data
//          for the current Menu. 
//
void menuProcessor(void)
{
  switch(menuState)
  {
    case MAIN_MENU:
      MainPageProcessor();
      break;
    case CHAN_1_MENU:
      ChanPageProcessor(1);
      break;
    case CHAN_2_MENU:
      ChanPageProcessor(2);
      break;
    case CHAN_3_MENU:
      ChanPageProcessor(3);
      break;
    case CHAN_4_MENU:
      ChanPageProcessor(4);
      break;
    case CHAN_CONFIG_MENU:
      ChanConfigProcessor();
      break;
    case SYSTEM_MENU:
      SysPageProcessor();
      break;
  }
}

/////////////////////////////////////
//
//
void MainPageProcessor(void)
{
  pushTA();
  //if(chanData1.prevIrms != chanData1.Irms)
  if(chanData1.changed)
  {
    displayMainCTx(1);
    chanData1.prevIrms = chanData1.Irms;
    chanData1.changed = false;
  }
  //if(chanData2.prevIrms != chanData2.Irms)
  if(chanData2.changed)
  {
    displayMainCTx(2);
    chanData2.prevIrms = chanData2.Irms;
    chanData2.changed = false;
  }
  //if(chanData3.prevIrms != chanData3.Irms)
  if(chanData3.changed)
  { 
    displayMainCTx(3);
    chanData3.prevIrms = chanData3.Irms;
    chanData3.changed = false;
  }
  //if(chanData4.prevIrms != chanData4.Irms)
  if(chanData4.changed)
  {
    displayMainCTx(4);
    chanData4.prevIrms = chanData4.Irms;
    chanData4.changed = false;
  }
  popTA(); 
}


///////////////////////////////////
//
//
//
void ChanPageProcessor(int chan)
{
  char charBuf[16];
  pushTA();
  //plotNeedle((float)(pChanConfig->range), 10, chan);
  //pChanData->Irms = pChanConfig->range;
  //Serial.printf("range = %d  \n\r", pChanConfig->range);
  if(pChanData->prevIrms != pChanData->Irms)
  if(pChanData->changed)
  {
    pChanData->changed = false;
    plotNeedle(pChanData->Irms, 10, chan);    // 40mA steps
    pChanData->prevIrms = pChanData->Irms;
    //plotNeedle((float)pChanConfig->range * 1000.0, 10, chan);
    setGfxFont(FSS18);
    myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
    myTFT.setTextDatum(MC_DATUM);         // Middle-Center Text
    //myTFT.drawRect(10,280,290,100, TFT_BLUE); 
    myTFT.fillRect(10,280,290,100, TFT_BLACK);   // clear text area
    sprintf(charBuf,"%3.2f Amps",pChanData->Irms);
    myTFT.drawString(charBuf, 160, 280);
    sprintf(charBuf,"%3.1f Watts",pChanData->Irms * (float)(pChanConfig->lineV));
    myTFT.drawString(charBuf, 160, 330);
  }
  popTA();
}

////////////////
//
//
//
void ChanConfigProcessor(void)
{
  pushTA();

  popTA();
}

////////////////////////////////////////
//
//
void SysPageProcessor(void)
{
  
}
