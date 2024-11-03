////////////////////////////////////////////////////////////
//
//  Display Time Zone Menu
//
void displayTzMenu(void)
{
  //menuState = TZ_MENU;
  //
  //  Display Time Zone Setting .
  //
  // Push Text Attributes on attribute stack
  pushTA();
  drawPageHeader("Time Zone Settings","", false);
  setGfxFont(FSS9);
  myTFT.setTextDatum(CC_DATUM);
  myTFT.fillRoundRect(10, 100, 300, 60, 10, TFT_BKGND);
  myTFT.drawRoundRect(10, 100, 300, 60, 10, TFT_WHITE);
  myTFT.fillRoundRect(100, 88, 120, 24, 5, TFT_BLACK);
  myTFT.drawRoundRect(100, 88, 120, 24, 5, TFT_WHITE); 
  myTFT.drawString("Region", 160, 98);     // 20, 85
  displayTzRegion(124);

  myTFT.fillRoundRect(10, 180, 300, 60, 10, TFT_BKGND);
  myTFT.drawRoundRect(10, 180, 300, 60, 10, TFT_WHITE);
  myTFT.fillRoundRect(100, 168, 120, 24, 5, TFT_BLACK);
  myTFT.drawRoundRect(100, 168, 120, 24, 5, TFT_WHITE);
  myTFT.drawString("City", 160, 178);
  displayTzCity( 160, 204, TFT_GREEN);

  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);
  myTFT.drawRoundRect(10, 300, 300, 80, 10, TFT_BLUE);
  myTFT.drawRoundRect(12, 302, 296, 76, 10, TFT_BLUE);
  myTFT.drawString("Date / Time", 160, 315);
  strftime(chrBuf, sizeof(chrBuf), "%a, %b %d %Y   %H:%M", timeinfo);
  myTFT.drawString(chrBuf, 160, 350);
  myTFT.drawFastHLine(0,395,319,TFT_YELLOW);
  if ((regionSelected) || (citySelected))
    drawBtnExitSave();
  else
    drawBtnExit();
  drawBtnCancel();
  // Pop Text Attributes from attribute stack
  popTA();
}

void initTzTemp(void)
{
  tzTemp = tzConfig;
}

////////////////////////////////////////////////////////
//
//  Process Time Zone menu (screen touches)
//
bool processTzMenu(int button)
{
  bool results = false;
  if (button == 23)     // Cancel
  {
    regionSelected = false;
    citySelected = false;
    popMenu();
  }
  else if (button == 24)       // Done
  {
    if ((regionSelected) || (citySelected))
    {
      tzConfig.regionIndx = tzTemp.regionIndx;
      tzConfig.cityIndx = tzTemp.cityIndx;
      strncpy(tzConfig.tzInfo, tzTemp.tzInfo, 48);
      wrtFileSPIFFS(fnTimeZoneConfig, (char *)&tzConfig, sizeof(tzConfig));
      setTZ();
      printTzTemp();
    }
    popMenu();
    results = true;
  }
  else if((touchData.x >= 20) && (touchData.x <= 300))
  {
    if ((touchData.y >= 70) && (touchData.y <= 130))
    {
      // Touched "Region"
      regionSelected = false;
      startRegion = 0;
      pushMenu(REGION_MENU);
      //displayRegionMenu();
    }
    else if ((touchData.y >= 150) && (touchData.y <= 210))
    {
      // Touched "City"
      citySelected = false;
      startCity = 0;
      pushMenu(CITY_MENU);
      //displayCityMenu();
    }
  }
  //displayTzMenu();
  return results;
}

/////////////////////////////////////////////////////////
//
//  Display Time Zone Region in Time Zone Menu
//
//
void displayTzRegion(int yPos)
{
  // Push Text Attributes on attribute stack
  pushTA();

  myTFT.setTextColor(TFT_GREEN);
  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.drawString(regionName[tzTemp.regionIndx], 160, yPos);
  // Pop Text Attributes from attribute stack
  popTA();
}

////////////////////////////////////////////////////////////
//
//  Process Region (selection) Menu (screen touches)
//
bool processRegionMenu(int button)
{
  bool results = false;
  if (button == 21)     // Cancel
  {
    popMenu();
    results =  true;
  }
  else if (button == 24)     // Done
  {
    if (regionSelected)
    {
      Serial.printf("changedRegionIndx = %d\n\r", changedRegionIndx);
      tzTemp.regionIndx = changedRegionIndx;
      tzTemp.cityIndx = 0;
    }
    popMenu();
    results =  true;
  }
  else if((touchData.x >= 80) && (touchData.x <= 220))
  {
    for(int i = 0; i < 10; i++)
    {
      if ((touchData.y >= (60 + (i * 35))) && (touchData.y <= (95 + (i * 35))))
      {
        regionSelectIndex = i;
        regionSelected = true;
        displayRegionMenu();
        break;
      }
    }
  }
  return results;
}

/////////////////////////////////////////////////////////
//
//  Display Time Zone City in Time Zone Menu
//
//
void displayTzCity(int xPos, int yPos, int color)
{
  loadTzCity();
  // Push Text Attributes on attribute stack
  pushTA();

  myTFT.setTextColor(color);
  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.drawString(city.cityName, xPos, yPos);
  // pop Text Attributes from attribute stack
  popTA();
}

////////////////////////////////////////////////////////////
//
//  Process City (selection) Menu (screen touches)
//
bool processCityMenu(int button)
{
  bool results = false;
  if (button == 23)     // Cancel
  {
    popMenu();
    results =  true;
  }
  else if (button == 24)     // Done
  {
    if (citySelected)
    {
      tzTemp.cityIndx = changedCityIndx;
      strncpy(tzTemp.tzInfo, changedTzInfo, 48);
    }
    popMenu();
    results =  true;
  }
  else if (button == 22)   //  Scroll Up
  {
    if (startCity < (cityCount - 8))
    {
      citySelected = false;
      startCity += 8;
      displayCityMenu();
    }
  }
  else if (button == 21)   // Scroll Down
  {
    if (startCity >= 8)
    {
      citySelected = false;
      startCity -= 8;
      displayCityMenu();
    }
  }
  else if ((touchData.x >= 80) && (touchData.x <= 220))
  {
    for(int c = 0; c < 8; c++)
    {
      if ((touchData.y >= (75 + (c * 35))) && (touchData.y <= (110 + (c * 35))))
      {
        citySelectIndex = c;
        if ((startCity + citySelectIndex) < cityCount)
        {
          Serial.printf("index of City selected = %d\n\r", startCity + citySelectIndex);
          citySelected = true;
          changedCityIndx = startCity + c;
          //tzTemp.cityIndx = startCity + citySelectIndex;
          //printCityInfo(startCity + citySelectIndex);
          printCityInfo(changedCityIndx);
          displayCityMenu();
        }
        break;
      }
      //else Serial.println("Selected City out of range");
    //displayCityMenu();
    }
  }
  return results;
}


/////////////////////////////////////////////////////////
//
//  Display Region Menu
//
void displayRegionMenu(void)
{
  // Push Text Attributes on attribute stack
  pushTA();
  drawBlankPage(false);
  myTFT.drawFastHLine(0, 50, 320, TFT_YELLOW);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.setTextColor(TFT_WHITE);
  setGfxFont(FSS12);
  myTFT.drawString("Select a Region", 160, 15);
 
  // Draw Regions
  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  for (int i = 0; i < 10; i++)
  {
    if ((startRegion + i) < REGION_COUNT)
    {
      if (regionSelected)
      {
        if( i == regionSelectIndex)
        {
          myTFT.setTextColor(TFT_WHITE);
          changedRegionIndx = startRegion + i;
        }
        else myTFT.setTextColor(TFT_GREY);
      }
      else
        myTFT.setTextColor(TFT_GREEN);
      //if ((startRegion + i) < REGION_COUNT)
      myTFT.drawString(String(regionName[i + startRegion]), 160, 60 + (i * 35));  
    }
  }
  //if ((REGION_COUNT - startRegion) > 8) drawBtn( 22, TFT_WHITE, "Scroll", "Up");
  //if (startRegion > 0) drawBtn( 21, TFT_WHITE, "Scroll", "Down");
  //drawBtn( 21, TFT_WHITE, "Cancel", "");
  drawBtnCancel();
  //drawBtn( 24, TFT_WHITE, "Exit", "");
  drawBtnExit();
  // Pop Text Attributes from attribute stack
  popTA();
}

////////////////////////////////////////////////////////
//
//  Display City Menu
//
void displayCityMenu(void)
{
  char fnBuf[32];
  int recordCnt;
  int regionIndx = tzTemp.regionIndx;
  // Push Text Attributes on attribute stack
  pushTA();
  drawBlankPage(false);
  setGfxFont(FSS12);
  myTFT.setTextDatum(TC_DATUM);         // Center Text
  myTFT.drawString("Select a City", 160, 15);
  myTFT.setTextDatum(TL_DATUM);        // Left Justify Text (default)

  myTFT.drawFastHLine(0, 50, 320, TFT_YELLOW);
  setGfxFont(FSS12);
  Serial.printf("-------- %s --------\n\r", regionName[regionIndx]);
  sprintf(fnBuf, "/%s.txt", regionName[regionIndx]);
  fTXT = SPIFFS.open(fnBuf, "r");

  if (!fTXT) {
    Serial.println(F("loadTzCity() Failed to open file"));
    Serial.println(fnBuf);
    while (1);  // hang here
  }
  //
  //
  recordCnt = cityCount = indexFile();
  if (recordCnt != 0)
  {
    for (int c = 0; c < 8; c++)
    {
      if ((c + startCity) < cityCount)
      {
        fillCityStruct(c + startCity);
        myTFT.setTextDatum(TC_DATUM);         // Center Text
        if(citySelected)
        {
          if( c == citySelectIndex)
          {
            myTFT.setTextColor(TFT_WHITE);
            //strncpy(changedCity.cityName, city.cityName, 48);
            strncpy(changedTzInfo, city.tzInfo, 48);
            changedCityIndx = startCity + c;
          }
          else myTFT.setTextColor(TFT_GREY);
        }
        else myTFT.setTextColor(TFT_GREEN);
        myTFT.drawString(String(city.cityName), 160, 75 + (c * 35));  
      }
    }
  }
  else
  {
    Serial.println(F("displayCityMenu() no cities ? "));
  }
  if ((cityCount - startCity) > 8) drawBtn22d("Scroll", "Up");  //drawBtn( 22, TFT_WHITE, "Scroll", "Up");
  if (startCity != 0) drawBtn21d("Scroll", "Down");  //drawBtn( 21, TFT_WHITE, "Scroll", "Down");
  Serial.printf("startCity = %d\n\r", startCity);
  fTXT.close();
  //drawBtn( 23, TFT_WHITE, "Cancel", "");
  drawBtnCancel();
  //drawBtn( 24, TFT_WHITE, "Exit", "");
  drawBtnExit();
  // Pop Text Attributes from attribute stack
  popTA();
}


//////////////////////////////////////////////////////////
//
//  Load city structure
//      using tzTemp.regionIndx and tzTemp.cityIndx
//
//
void loadTzCity(void)
{
  char fnBuf[32];
  int recordCnt;
  int regionIndx = tzTemp.regionIndx;
  // Push Text Attributes on attribute stack
  pushTA();
  Serial.printf("!!----- %s ------!!\n\r", regionName[regionIndx]);
  sprintf(fnBuf, "/%s.txt", regionName[regionIndx]);
  Serial.printf("Opening file %s\n\r", fnBuf);
  fTXT = SPIFFS.open(fnBuf, "r");

  if (!fTXT) {
    Serial.println(F("loadTzCity() Failed to open file"));
    while (1);  // hang here
  }
  //
  //  Fill city struct from file
  //
  recordCnt = indexFile();
  if (recordCnt != 0)
  {
    fillCityStruct(tzTemp.cityIndx);
  }
  fTXT.close();
  // Pop Text Attributes from attribute stack
  popTA();
}


//////////////////////////////////////////////////////
//
//  get Record at offset 'recordIndx'
//    store read data in record.rData and length in record.rSize (record structure).
//    The file at handle fTXT must already be opened before calling this function.
//
bool getRecord(int recordIndx)
{
  bool result = false;
  bool done = false;
  int rdLength = 0;
  //  int recordIndx = 0;
  //  char cBuf[4];
  //Serial.println("getRecord()");
  if (recordIndxTbl[recordIndx].recordSize == 0) return false;
  while (!done)
  {
    if (recordIndxTbl[recordIndx].recordSize == 0)
    {
      done = true;
    }
    else
    {
      //Serial.printf(" %d  Start = %d, Length = %d\n\r", recordIndx,
      //              recordIndxTbl[recordIndx].recordStart, recordIndxTbl[recordIndx].recordSize);
      fTXT.seek(recordIndxTbl[recordIndx].recordStart, SeekSet);
      record.rSize = recordIndxTbl[recordIndx].recordSize;
      //rdLength = fTXT.readBytes( record.rData, recordIndxTbl[recordIndx].recordSize);
      rdLength = fTXT.readBytes( record.rData, record.rSize);
      //if (rdLength != recordIndxTbl[recordIndx].recordSize)
      if (rdLength != record.rSize)
      {
        Serial.printf("Read ERROR length Exp : %d  Act : %d\n\r", recordIndxTbl[recordIndx].recordSize, rdLength);
        while (1);
      }
      else
      {
        record.rData[record.rSize] = 0;
        done = true;
        result = true;
      }
    }
  }
  return result;
}

//////////////////////////////////////////////////////////////////////
//
//  Fill City Data Struct (global structure) from file handle (fTXT)
//    Must have first called indexFile()
//    Uses file handle fTXT. File must already be opened.
//
void fillCityStruct(int indx)
{
  // get record at indx ( must have first called indexFile()
  if (getRecord(indx) == true)
  {
    int subIndx = String(record.rData).indexOf(',');
    int z = 0;
    for ( z = 0; z < subIndx; z++)
    {
      city.cityName[z] = record.rData[z];
    }
    city.cityName[z] = 0;
    int x = 0;
    for ( x = 0; (x + subIndx + 1) < record.rSize; x++)
    {
      city.tzInfo[x] = record.rData[x + subIndx + 1];
    }
    city.tzInfo[x] = 0;
  }
  else
  {
    city.tzInfo[0] = 0;
    city.cityName[0] = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Populate Record Index Table (which is global). (text files with LF,CR,0 record delimiters)
//      For each delimited string (record) in the specified file, the record index table
//      will contain the record location (byte count from the start of the file)
//      and the length of the string (record).
//
//    Requirements: file handle fTXT - must be opened prior to callind this function.
//                  Populates recordIndxTbl[] (global structure)
//
//    Returns: Record count
//
int indexFile(void)
{
  int recordCount = 0;
  int currentRecordIndx = 0;
  recordIndxTbl[0].recordSize = 0;
  //  File fTXT;
  bool recordDone = false;
  bool endOfFile = false;
  int rdLength = 0;
  int recordLength = 0;
  char cBuf[4];
  Serial.println(F("indexFile()"));
  fTXT.seek(0, SeekSet);          // Start from begining of file
  /*
    Serial.printf("Opening file %s\n\r", fileName);
    fTXT = SPIFFS.open(fileName, "r");
    if (!fTXT) {
    Serial.println("indexFile() Failed to open file");
    while (1);  // hang here
    }
  */
  while (!endOfFile)          // end of file ?
  {
    recordLength = 0;
    recordDone = false;
    while (!recordDone)
    {
      if (recordLength == 0)      // possibly begining of record.
        recordIndxTbl[currentRecordIndx].recordStart = fTXT.position();
      // read a byte from file
      rdLength = fTXT.readBytes(cBuf, 1);
      if (rdLength != 0)
      {
        // Check for ASCII printable character,
        // non-printable are considered record delimiter(s)
        //
        if (cBuf[0] >= ' ')     // ASCII printable character
        {
          recordLength++;
        }
        // else must be record delimiter(s)
        // if consective delimiters (LF & CR) don't count as
        //  zero length record.
        else if (recordLength != 0) // don't count zero length records
        {
          recordCount++;
          recordIndxTbl[currentRecordIndx].recordSize = recordLength;
          currentRecordIndx++;
          recordDone = true;
        }
      }
      else      /// nothing left to read (end of file)
      {
        recordDone = true;    // needed to end (skip last delimiters)
        endOfFile = true;
      }
    }     // recordDone ?
  }       // End Of File ?
  // Mark the end of record index table entries
  recordIndxTbl[currentRecordIndx].recordSize = 0;
  recordIndxTbl[currentRecordIndx].recordStart = 0;
  cityCount = recordCount;
  /*
    Serial.printf("indexFile(), recordCount = %d\n\r", recordCount);
      for (int r = 0; r < recordCount; r++)
      {
      Serial.printf(" %d  Start = %d  Length = %d\n\r", r + 1 , recordIndxTbl[r].recordStart, recordIndxTbl[r].recordSize);
        }
  */
  return recordCount;
}

////////////////////////////////////////////////////////////
//
//  For debugging
//
void printCityInfo(int cityIndx)
{
  char fnBuf[32];
  sprintf(fnBuf, "/%s.txt", regionName[tzTemp.regionIndx]);
  fTXT = SPIFFS.open(fnBuf, "r");

  if (!fTXT) {
    Serial.println(F("loadTzCity() Failed to open file"));
    while (1);  // hang here
  }
  fillCityStruct(cityIndx);
  //city.tzInfo[0] = 0;
  //city.cityName[0] = 0;
  Serial.printf(" %s   %s\n\r", city.cityName, city.tzInfo);
  fTXT.close();
}

//
//
//
void printTzTemp(void)
{
  Serial.printf("tzTemp region %d : city %d : tzInfo %s\n\r", tzTemp.regionIndx, tzTemp.cityIndx, tzTemp.tzInfo);
}

#if 0
//
// Function that gets current epoch time (From NTP ?)
//
//
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
   //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}
#endif

//////////////////////////////////////////////
//
//
//
void Update_timeinfo(void)
{
#ifdef DS3231_RTC
  DateTime now = rtc.now();
  time_t rawTime = now.unixtime();
#endif
#ifdef RV3028_C7
  time_t rawTime = rtc.getUnixTimestamp();
#endif
  timeinfo = localtime(&rawTime);
}
