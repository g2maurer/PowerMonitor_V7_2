SWITCH_STRUCT wifiSw = {
  0,
  true,         // bool horiz; 
  160,           // int xPos;       
  92,          // int yPos;      
  80,           // int xSize;
  35,           // int ySize;
  15,           // int swRadius;
  SW_TXT_RIGHT,  // int textPos;   
};

////////////////////////////////////////////////////////////
//
//  Display WiFi Menu
//
void displayWiFiMenu(void)
{
  // Push Text Attributes on attribute stack
  pushTA();
  drawPageHeader("WiFi Settings","", false);
  myTFT.setTextColor(TFT_WHITE);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  // Draw WiFi enable/disable switch
  myTFT.fillRoundRect(10, 80, 300, 60, 10, TFT_BKGND);
  myTFT.drawRoundRect(10, 80, 300, 60, 10, TFT_WHITE);
  setGfxFont(FSS12);
  myTFT.drawString("WiFi", 60, 102);
  drawSwitch( wifiSw, WiFiConfig.enabled);
  if(WiFiConfig.enabled)
  {
    // Display MAC and IP addresses
    myTFT.setTextDatum(TL_DATUM);
    setGfxFont(FSS9);
    myTFT.fillRoundRect(10, 150, 300, 60, 10, TFT_BKGND);
    myTFT.drawRoundRect(10, 150, 300, 60, 10, TFT_WHITE);
    myTFT.drawString("MAC Address:", 20, 160);
    myTFT.drawString(WiFi.macAddress(), 145, 160);
    myTFT.drawString("IP Address:", 20, 185);
    myTFT.drawString(WiFi.localIP().toString(), 145, 185);
    // Display SSID
    displaySSID_PW_UN("ssid", 220); 
    displayWiFiSSID(255, TFT_GREEN);
    // Display IP
    displaySSID_PW_UN("password", 300);
    displayWiFiPW(340, TFT_GREEN);
    myTFT.drawFastHLine(0,395,319,TFT_YELLOW);
    drawBtn21d("FTP", "Setup");
  }
  if ((changedSSID == true) || (changedWiFiPW == true) || changedWiFiEnable)
    drawBtnExitSave();
  else
    drawBtnExit();
  drawBtnCancel();
  // Pop Text Attributes from attribute stack
  popTA();
}

//
//
//
void displaySSID_PW_UN(String desc, int ypos)
{
  pushTA();
  setGfxFont(FM9);     //FSS9
  myTFT.setTextDatum(CC_DATUM);
  myTFT.fillRoundRect(10, ypos+10, 300, 60, 10, TFT_BKGND);   // 230
  myTFT.drawRoundRect(10, ypos+10, 300, 60, 10, TFT_WHITE); 
  myTFT.drawRoundRect(100, ypos, 120, 20, 5, TFT_WHITE);
  myTFT.fillRoundRect(101, ypos+1, 118, 18, 5, TFT_BLACK); 
  myTFT.drawString(desc, 160, ypos+7, GFXFF);
  popTA();

}

#if 0
//
//
//
void initWiFiFlags(void)
{
  changedWiFiPW = false;
  changedSSID = false;
  changedWiFiEnable = false;
}
#endif

////////////////////////////////////////////////////////////
//
//  Process WiFi Menu (screen touches)
//
void processWiFiMenu(int button)
{
  bool refresh = false;
  if (button == 24)        // Save & Exit
  {
    if (changedSSID == true)       // if changed/selected SSID
    {
      strncpy(WiFiConfig.ssID, tempSSID, 32);
    }
    if (changedWiFiPW == true)       // if changed/selected Password
    {
      strncpy(WiFiConfig.passWord, tempPW, 32);
    }
    if ((changedSSID == true) || (changedWiFiPW == true) || changedWiFiEnable)
    {
      // Update WiFi configuration in SPIFFS.
      Serial.println("WiFi configuration has changed - Saving");
      wrtFileSPIFFS(fnWifiConfig, (char *)&WiFiConfig, sizeof(WiFiConfig));
      // Reset ESP32 to restart WiFi
      delay(500);
      if(WiFiConfig.enabled == true) initWiFi();
      else wifiDisconnect();
      //restart();
    }
    popMenu();
    //refresh = true;
  }
  else if (button == 23)   // Cancel
  {
    popMenu();
  }
  else if (button == 21)  // FTP
  {
    strncpy(tempFtpUN, WiFiConfig.ftpUserName, strlen(WiFiConfig.ftpUserName) + 1);
    strncpy(tempFtpPW, WiFiConfig.ftpPassWord, strlen(WiFiConfig.ftpPassWord) + 1);
    pushMenu(FTP_MENU);
  }
  else if((touchData.x >= 20) && (touchData.x <= 300))
  {
    // SSID or Password
    if ((touchData.y >= 250) && (touchData.y <= 310))   // SSID
    {
      // SSID
      //strncpy(tempSSID, WiFiConfig.ssID, 32);
      displayScanning();
      pushMenu(SSID_MENU);
      //displaySsidMenu();
    }
    else if ((touchData.y >= 340) && (touchData.y <= 400))    // Password
    {
      // WiFi PASSWORD
      // setup for processing of keyboard input
      sprintf(kbTitle,"WiFi Password");
      kbMaxCharCnt = NAME_MAX_LEN;
      changedWiFiPW = false;
      kbClearString();
      //kbStringIndex = 0;
      // post processing of keyboard input
      fpKeyboardPP = &ppWiFiPassword;    
      pushMenu(KEYBOARD_MENU);
    }
  }
  switch(swTouchChk(wifiSw))
  {
    case SW_NONE:
      break;
    case SW_LEFT:
      WiFiConfig.enabled = false;
      changedWiFiEnable = true;
      refresh = true;
      break;
    case SW_RIGHT:
      WiFiConfig.enabled = true;
      changedWiFiEnable = true;
      refresh = true;
      break;
  }
  if(refresh) displayWiFiMenu();
}

///////////////////////////////////////////////////////////
//
//  Display WiFi SSID in WiFi Menu
//
//
void displayWiFiSSID(int yPos, int fontColor)
{
  // Push Text Attributes on attribute stack
  pushTA();
  myTFT.setTextColor(fontColor);
  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.drawString(tempSSID, 160, yPos, GFXFF);
  // Pop Text Attributes from attribute stack
  popTA();
}

/////////////////////////////////////////////////////////
//
//  Display WiFi Password in WiFi Menu
//
//
void displayWiFiPW(int yPos, int fontColor)
{
  // Push Text Attributes on attribute stack
  pushTA();
  myTFT.setTextColor(fontColor);
  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  if (changedWiFiPW) myTFT.drawString(tempPW, 160, yPos, GFXFF);
  else
    myTFT.drawString("*********", 160, yPos, GFXFF);
  // pop Text Attributes from attribute stack
  popTA();
}

/////////////////////////////////////////
//
//
//
void displayScanning(void)
{
  pushTA();
  setGfxFont(FSS12);
  myTFT.setTextColor(TFT_YELLOW);
  myTFT.setTextDatum(TC_DATUM);
  myTFT.fillRoundRect(80, 220, 160, 80, 5, TFT_BLACK);
  myTFT.drawRoundRect(80, 220, 160, 80, 5, TFT_WHITE);
  //myTFT.drawRoundRect(120, 220, 100, 80, TFT_GREY);
  myTFT.drawString("Scanning", 160, 230);
  myTFT.drawString("WiFi Network", 160, 260);
  FillSsidStruct();
  popTA();
}
/////////////////////////////////////////////////////////////
//
//  Display WiFi SSID Menu (available networks)
//
void displaySsidMenu(void)
{
  ssidSelected = false;
  //drawBtn( 12, TFT_ORANGE, "Scanning", "");

  //FillSsidStruct();
  displayWifiSSIDtbl();
  //drawBtn(6, TFT_WHITE, "Scan", "");
}

///////////////////////////////////////////////////////////
//
//  Process SSID Menu (screen touches)
//    returns:  TRUE if "Cancel" or "Save" button touched
//              indicating exit of SSID menu.
//              FALSE if continuing in SSID Menu.
//
bool processSsidMenu(int button)
{
  bool results = false;
  if (button == 23)            // Cancel
  {
    ssidSelected = false;
    changedSSID = false;
    popMenu();
    results = true;
  }
  else if (button == 21)       // Scan
  {
    displayScanning();
    ssidSelected = false;
    changedSSID = false;

    //FillSsidStruct();
    displayWifiSSIDtbl();

  }
  else if (button == 24)       // Save & Exit
  {
    //if (ssidSelected)
    if (changedSSID)
    {
      strncpy(tempSSID, WifiNetworks.Tbl[ssidSelectIndex].ssid, 32);
      //tempSSID = String(WifiNetworks.Tbl[ssidSelectIndex].ssid);
      //ssid = String(WifiNetworks.Tbl[ssidSelectIndex].ssid);
      //wifiSsidChanged = true;
      //changedSSID = true;
      //updateSSID = true;
    }
    popMenu();
    results = true;
  }
  else if ((touchData.x >= 80) && (touchData.x <= 220))
  {
    for(int i = 0; i < WifiNetworks.count; i++)
    {
      if ((touchData.y >= (75 + (i * 35))) && (touchData.y <= (110 + (i * 35))))
      {
        Serial.printf("SSID index = %d\n\r", i);
        ssidSelectIndex = i;
        ssidSelected = true;
        changedSSID = true;
        displayWifiSSIDtbl();
        break;
      }
    }
  }
  return results;
}

//////////////////////////////////////////////////////////
//
//  Display WiFi SSID Table (available networks)
//
void displayWifiSSIDtbl(void)
{
  // Push Text Attributes on attribute stack
  pushTA();
  drawBlankPage(false);
 
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.setTextColor(TFT_WHITE);
  setGfxFont(FSS12);
  myTFT.drawString("Available Networks", 160, 15, GFXFF);
  myTFT.drawFastHLine(0, 50, 320, TFT_YELLOW);

  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  for (int i = 0; i < WifiNetworks.count; i++)
  {
    if (ssidSelected) 
    {
      if( i == ssidSelectIndex)
        myTFT.setTextColor(TFT_WHITE);
      else
        myTFT.setTextColor(TFT_GREY);
    }
    else myTFT.setTextColor(TFT_GREEN);
      
    myTFT.drawString(String(WifiNetworks.Tbl[i].ssid), 160, 75 + (i * 35));
  }
  myTFT.drawFastHLine(0, 390, 320, TFT_YELLOW);
  //drawBtn( 21, TFT_WHITE, "Scan", "");
  drawBtn21("Scan");
  if (ssidSelected == true)
  {
    //drawBtn( 24, TFT_WHITE, "Save", "& Exit");
    drawBtnExitSave();
    //drawBtn( 23, TFT_WHITE, "Cancel", "");
    drawBtnCancel();
  }
  else
    //drawBtn( 24, TFT_WHITE, "Exit", "");
    drawBtnExit();

  // Pop Text Attributes from attribute stack
  popTA();
}

////////////////////////////////////////////
//
//  Post Processor for: WiFi Password input from Keyboaard
//
void ppWiFiPassword(void)
{
  Serial.println("ppWiFiPassword()");
  strcpy(tempPW, kbString);  //
  changedWiFiPW = true;
  //strncpy(tempPW, inputStr, 32);
  Serial.println(strlen(kbString));
  Serial.println(kbString);
  Serial.println(tempPW);
}

//
//
//
void restart(void)
{
  myTFT.fillScreen(TFT_BLACK);
  setGfxFont(NULL);
  myTFT.setTextSize(3);        // Text size multiplier = 3X
  myTFT.setTextColor(TFT_GREEN, TFT_BLACK);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.drawString("- Restarting -", 160, 100);
  delay(1000);
  ESP.restart();
}
