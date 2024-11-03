/*
  Licensed as Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
  You are free to:
  Share — copy and redistribute the material in any medium or format
  Adapt — remix, transform, and build upon the material
  Under the following terms:
  Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
  NonCommercial — You may not use the material for commercial purposes.
  ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original
*/
// #############################################################
//
//      TTTTTTT   OOOOO    U     U    CCCCC    H     H
//         T     O     O   U     U   C     C   H     H
//         T     O     O   U     U   C         HHHHHHH
//         T     O     O   U     U   C     C   H     H
//         T      ooooo     UUUUU     CCCCC    H     H
//
// #############################################################

//
//  TFT SPI only
//  Read Touch Screen position (x,y)
//
#define TOUCH_THRESHOLD 400   //400
//
bool touchCheck(void)
{
  uint16_t x, y;
  // See if there's any new touch data
  //if (myTFT.getTouch(&x, &y, TOUCH_THRESHOLD))
  if (myTFT.getTouch(&x, &y))
  {
    touchData.x = x;
    touchData.y = y;
    touchData.row = 0;
    touchData.column = 0;
    touchData.button = 0;
    delay(200);
    return (true);
  }
  return (false);
}

////////////////////////////////////////////////////////////////////////
//
//    Button Decode: returns button number based on the following;
//                touchData.x and touchData.y (global struct)
//                SCREEN_WIDTH & SCREEN_HEIGHT
//        Input:  rows - number of buttons per column
//                columns - number of buttons per row
//        Output: Button number (1 to n), also found in touchData.button
//

int btnDecode( int columns, int rows)
{
    touchData.column = (touchData.x + 1) / (SCREEN_WIDTH/columns);    // 80 = 320/4
    touchData.row = (touchData.y + 1) / (SCREEN_HEIGHT/rows);     // 80 = 480/6
    touchData.button = (touchData.column + 1) + (touchData.row * 4);
    //Serial.printf("Button = %d,  x = %d, y = %d\n\r", touchData.button, touchData.x, touchData.y);
    return(touchData.button);
}

/////////////////////////////////////////////
//
//
//
int swTouchChk( SWITCH_STRUCT sw)
{
  int result = 0;
  if( (touchData.y >= sw.yPos) && (touchData.y <= (sw.yPos + sw.ySize)) ) 
  {
    //Serial.printf("x=%d  y=%d \n\r", touchData.x, touchData.y);
    if( (touchData.x >= sw.xPos) && (touchData.x <= (sw.xPos + sw.xSize)) )
    {
      if( touchData.x <= (sw.xPos + sw.xSize/2) ) result = SW_LEFT;
      else result = SW_RIGHT;
    } 
  }
  //Serial.println(result);
  return(result);
}

////////////////////////////////////////////
//
//
//
void setGfxFont(const GFXfont *font)
{
  gfxFont = font;
  myTFT.setFreeFont(font);
}

typedef struct ATTR_STRUCT {
  uint8_t textSize;
  uint8_t textFont;
  uint8_t textDatum;
  uint32_t textColor;
  uint32_t textBgColor;
  const GFXfont *freeFont;
} TEXT_ATTR;

#define ATTR_STACK_SIZE 8
TEXT_ATTR *textAttr;
TEXT_ATTR attrStack[ATTR_STACK_SIZE];
int attrStkPtr = 0;

/////////////////////////////////////////////////////////
//
//  Push Text Attributes
//
void pushTA(void)
{
  if (attrStkPtr < ATTR_STACK_SIZE)
  {
#ifdef PUSH_POP_DEBUG
    Serial.printf("pre-PUSH %x\n\r", attrStkPtr);

    Serial.printf("textfont = %d\n\r", myTFT.textfont);
    Serial.printf("textsize = %d\n\r", myTFT.textsize);
    Serial.printf("textdatum = %d\n\r", myTFT.textdatum);
    Serial.printf("freeFont = %x\n\r", gfxFont);
#endif
    attrStack[attrStkPtr].textFont = myTFT.textfont;
    attrStack[attrStkPtr].textSize = myTFT.textsize;
    attrStack[attrStkPtr].textDatum = myTFT.textdatum;
    attrStack[attrStkPtr].freeFont = gfxFont;
    attrStack[attrStkPtr].textColor = myTFT.textcolor;
    attrStack[attrStkPtr].textBgColor = myTFT.textbgcolor;
    attrStkPtr++;
#ifdef PUSH_POP_DEBUG
    Serial.printf("post-PUSH %x\n\r", attrStkPtr);
#endif
  }
  else
  {
    Serial.println("Attribute stack overflow");
    //sysLog("Attribute stack overflow");
    // Dump Stack
    for (int i = 0; i < ATTR_STACK_SIZE; i++)
    {
      Serial.printf("%d = %d\r\n", i, attrStack[i].textFont);
    }
    delay(2000);
    ESP.restart();
    while (1);
  }
}

///////////////////////////////////////////
//
//  Pop Text Attributes
//
void popTA(void)
{
  if (attrStkPtr > 0)
  {
#ifdef PUSH_POP_DEBUG
    Serial.printf("pre-POP %x\n\r", attrStkPtr);
#endif
    --attrStkPtr;
#ifdef PUSH_POP_DEBUG
    Serial.printf("post-POP %x\n\r", attrStkPtr);
    Serial.printf("textfont = %d\n\r", attrStack[attrStkPtr].textFont);
    Serial.printf("textsize = %d\n\r", attrStack[attrStkPtr].textSize);
    Serial.printf("textdatum = %d\n\r", attrStack[attrStkPtr].textDatum);
    Serial.printf("freeFont = %x\n\r", attrStack[attrStkPtr].freeFont);
#endif
    myTFT.setTextDatum(attrStack[attrStkPtr].textDatum);
    myTFT.setTextSize(attrStack[attrStkPtr].textSize);
    myTFT.setTextFont(attrStack[attrStkPtr].textFont);
    gfxFont = attrStack[attrStkPtr].freeFont;
    myTFT.setFreeFont(gfxFont);
    //myTFT.setTextColor(attrStack[attrStkPtr].textColor);
    myTFT.textcolor = attrStack[attrStkPtr].textColor;
    myTFT.textbgcolor = attrStack[attrStkPtr].textBgColor;
  }
  else
  {
    Serial.println("Attribute stack underflow");
    //sysLog("Attribute stack underflow");
    // Dump Stack
    for (int i = 0; i < ATTR_STACK_SIZE; i++)
    {
      Serial.printf("%d = %d\r\n", i, attrStack[i].textFont);
    }
    delay(2000);
    ESP.restart();
    while (1);
  }

}


///////////////////////////////////////////////
//
//  Touch Calibrate, TFT SPI only
//
//
uint16_t calData[8];
//
void touch_calibrate()
{
  bool calDataOK = false;

  // check file system exists

  //  myTFTLedOn();
  // Open dir folder
  File dir = SPIFFS.open("/");
  // List file at root
  //  listFilesInDir(dir, 1);


  // check if calibration file exists and size is correct
  //
#ifdef REPEAT_TFT_CAL
  deleteFileSPIFFS(fnTftCal);
#endif
  if (existsFileSPIFFS(fnTftCal))
  {
    if (rdFileSPIFFS(fnTftCal, (char *)calData, 16))
      calDataOK = true;
#ifdef PRINT_TFT_CAL_DATA
      printTftCalData();
#endif
  }
  else calibrateTftTouch = true;
  if (calDataOK && !calibrateTftTouch)
  {
    // calibration data valid
    myTFT.setTouch(calData);
  }
  else
  {
    Serial.println("Calibrate Touch!");
    // data not valid, calibrate TFT Touch
    myTFT.fillScreen(TFT_BLACK);
    myTFT.setCursor(20, 0);
    myTFT.setTextFont(2);
    myTFT.setTextSize(1);
    myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
    myTFT.println("Touch corners as indicated");
    myTFT.setTextFont(1);
    myTFT.println();
    myTFT.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
#ifdef PRINT_TFT_CAL_DATA
      printTftCalData();
#endif
    // Save TFT Touch calibration data
    wrtFileSPIFFS(fnTftCal, (char *)calData, 16);
    calibrateTftTouch = false;
    myTFT.fillScreen(TFT_BLACK);
    myTFT.setTextSize(3);
    myTFT.setTextColor(TFT_GREEN, TFT_BLACK);
    myTFT.setTextDatum(TC_DATUM);         // Center Text
    myTFT.drawString("Calibration", 160, 90);
    myTFT.drawString("complete!", 160, 120);
    delay(1000);
  }
}

#ifdef PRINT_TFT_CAL_DATA
void printTftCalData(void)
{
  Serial.println(F("\r\n=== TFT Touch Calibration Data ==="));
  for (int z = 0; z < 5; z++)
  {
    Serial.print("\t");
    Serial.println(calData[z]);
  }
}
#endif
