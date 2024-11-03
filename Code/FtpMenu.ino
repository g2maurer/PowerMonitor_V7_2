#if 0
void initFtpFlags(void)
{
  changedFtpPW = false;
  changedFtpUN = false;
  changedFtpEnable = false;
}
#endif


SWITCH_STRUCT ftpSw = {
  0,
  true,         // bool horiz; 
  160,           // int xPos;       
  112,          // int yPos;      
  80,           // int xSize;
  35,           // int ySize;
  15,           // int swRadius;
  SW_TXT_RIGHT,  // int textPos;   
};

//
//
//
//
void displayFtpMenu(void)
{
//  int ypos = 0;
  pushTA();
  drawPageHeader("FTP Settings","", false);
  myTFT.setTextColor(TFT_WHITE);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
    // Draw FTP enable/disable switch
  myTFT.fillRoundRect(10, 100, 300, 60, 10, TFT_BKGND);
  myTFT.drawRoundRect(10, 100, 300, 60, 10, TFT_WHITE);
  setGfxFont(FSS12);
  myTFT.drawString("FTP", 60, 122);
  drawSwitch( ftpSw, WiFiConfig.ftpEnabled);
  myTFT.setTextDatum(TL_DATUM);
  setGfxFont(FSS9);
  if(WiFiConfig.ftpEnabled)
  {
    displaySSID_PW_UN("username", 180); 
    displayFtpUN(215, TFT_GREEN);   // 255
    displaySSID_PW_UN("password", 260);
    displayFtpPW(295, TFT_GREEN);   // 340
  }
  myTFT.drawFastHLine(0,395,319,TFT_YELLOW);
  drawBtnExit();
  popTA();  
}

//
//
//
void processFtpMenu(int button)
{
  bool refresh = false;
  if(button == 24)
  {
    if (changedFtpUN == true)       // if changed/selected Username
    {
      strncpy(WiFiConfig.ftpUserName, tempFtpUN, 32);
    }
    if (changedFtpPW == true)       // if changed/selected Password
    {
      strncpy(WiFiConfig.ftpPassWord, tempFtpPW, 32);
    }
    if ((changedFtpUN == true) || (changedFtpPW == true) || changedFtpEnable)
    {
      // Update WiFi configuration in SPIFFS.
      Serial.println("FTP configuration has changed - Saving");
      wrtFileSPIFFS(fnWifiConfig, (char *)&WiFiConfig, sizeof(WiFiConfig));
      // Reset ESP32 to restart WiFi
      delay(500);
      //if(WiFiConfig.enabled == true) initWiFi();
      //else wifiDisconnect();
      //restart();
    }
    popMenu();    // Exit & Save
  }
  else if((touchData.x >= 20) && (touchData.x <= 300))
  {
    // Username or Password
    if ((touchData.y >= 150) && (touchData.y <= 210))   // Username
    {
      // FTP Username
      // setup for processing of keyboard input
      sprintf(kbTitle,"FTP Username");
      kbMaxCharCnt = NAME_MAX_LEN;
      changedFtpUN = false;
      kbClearString();
      //kbStringIndex = 0;
      //kbString[0] = 0;
      // post processing of keyboard input
      fpKeyboardPP = &ppFtpUsername;    
      pushMenu(KEYBOARD_MENU);
    }
    else if ((touchData.y >= 230) && (touchData.y <= 300))    // Password
    {
      // FTP PASSWORD
      // setup for processing of keyboard input
      sprintf(kbTitle,"FTP Password");
      kbMaxCharCnt = NAME_MAX_LEN;
      changedFtpPW = false;
      kbClearString();
      //kbStringIndex = 0;
      //kbString[0] = 0;
      // post processing of keyboard input
      fpKeyboardPP = &ppFtpPassword;    
      pushMenu(KEYBOARD_MENU);
    }
  }
  switch(swTouchChk(ftpSw))
  {
      case SW_NONE:
        break;
      case SW_LEFT:
        WiFiConfig.ftpEnabled = false;
        changedFtpEnable = true;
        refresh = true;
        break;
      case SW_RIGHT:
        WiFiConfig.ftpEnabled = true;
        changedFtpEnable = true;
        refresh = true;
        break;
  }
  if(refresh) displayFtpMenu();
}


///////////////////////////////////////////////////////////
//
//  Display FTP Username in FTP Menu
//
//
void displayFtpUN(int yPos, int fontColor)
{
  // Push Text Attributes on attribute stack
  pushTA();
  myTFT.setTextColor(fontColor);
  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.drawString(tempFtpUN, 160, yPos, GFXFF);
  // Pop Text Attributes from attribute stack
  popTA();
}

/////////////////////////////////////////////////////////
//
//  Display FTP Password in FTP Menu
//
//
void displayFtpPW(int yPos, int fontColor)
{
  // Push Text Attributes on attribute stack
  pushTA();

  myTFT.setTextColor(fontColor);
  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.drawString(tempFtpPW, 160, yPos, GFXFF);
  //if (changedFtpPW) myTFT.drawString(tempFtpPW, 160, yPos, GFXFF);
  //else
    //myTFT.drawString("*********", 160, yPos, GFXFF);
  // pop Text Attributes from attribute stack
  popTA();
}


//
//  Post Processor for: FTP Username input from Keyboaard
//
void ppFtpUsername(void)
{
  Serial.println("ppFtpUsername()");
  strcpy(tempFtpUN, kbString);  //
  changedFtpUN = true;
  Serial.println(strlen(kbString));
  Serial.println(kbString);
  Serial.println(tempFtpUN);
}


//
//  Post Processor for: FTP Password input from Keyboaard
//
void ppFtpPassword(void)
{
  Serial.println("ppFtpPassword()");
  strcpy(tempFtpPW, kbString);  //
  changedFtpPW = true;
  Serial.println(strlen(kbString));
  Serial.println(kbString);
  Serial.println(tempFtpPW);
}

#ifdef SIMPLE_FTP
void _callback(FtpOperation ftpOperation, unsigned int freeSpace, unsigned int totalSpace){
  switch (ftpOperation) {
    case FTP_CONNECT:
      Serial.println(F("FTP: Connected!"));
      break;
    case FTP_DISCONNECT:
      Serial.println(F("FTP: Disconnected!"));
      ftpTIP = false;
      break;
    case FTP_FREE_SPACE_CHANGE:
      Serial.printf("FTP: Free space change, free %u of %u!\n", freeSpace, totalSpace);
      break;
    default:
      break;
  }
};

void _transferCallback(FtpTransferOperation ftpOperation, const char* name, unsigned int transferredSize){
  switch (ftpOperation) {
    case FTP_UPLOAD_START:
      Serial.println(F("FTP: Upload start!"));
      ftpTIP = true;
      break;
    case FTP_UPLOAD:
      //Serial.printf("FTP: Upload of file %s byte %u\n", name, transferredSize);
      Serial.print(".");
      ftpTIP = true;
      break;
    case FTP_DOWNLOAD_START:
      Serial.println(F("FTP: Download start!"));
      ftpTIP = true;
      break;
    case FTP_DOWNLOAD:
      //Serial.printf("FTP: Download of file %s byte %u\n", name, transferredSize);
      Serial.print(".");
      ftpTIP = true;
      break;
    case FTP_TRANSFER_STOP:     // Upload or Download
      Serial.println(F("\r\nFTP: Finish transfer!"));
      ftpTIP = false;
      break;
    case FTP_TRANSFER_ERROR:    // Upload or Download
      Serial.println(F("\r\nFTP: Transfer error!"));
      ftpTIP = false;
      break;
    default:
      Serial.println(F("\r\nFTP: Undefined FTP Operation!"));
      ftpTIP = false;
      break;
  }
}
#endif
