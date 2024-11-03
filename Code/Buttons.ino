//
//  Draw Button (1 - 24)
//
//    Four ROWS by Three COLUMNS (12 Buttons)
//      Top row (left to right) is Buttons #1 #2 #3 #4
//      Second row (left to right) is Buttons #5 #6 #7 #8
//      Third row (left to right) is Buttons  #9 #10 #11 #12
//      Forth row (left to right) is Buttons #13 #14 #15 #16
//      Fifth row (left to right) is Buttons #17 #18 #19 #20
//      Bottom row (left to right) is Buttons #21 #22 #23 #24
//
//      There is no Button #0 (ZERO)
//
#define BUTTON_CNT  24
#define B_RADIUS 10
#define B_HEIGHT 67
#define B_WIDTH 68
#define B_PER_ROW 6
#define B_PER_COL 4
//
//  Location of Button
//
int Button_xPos[6] = {10, 88, 166, 244, 322, 400};
int Button_yPos[6] = {11, 89, 167, 245, 323, 401};
//
//    Location of text within Button (x and y axis)(x = center of button)
//      use with MC_DATUM
//
int xPosTblText[6] = {43, 121, 199, 277, 355, 433};    // index = (buttonNbr - 1) % B_PER_COL
int yPosTblText1[6] = {43, 121, 199, 277, 355, 433};   // index = (buttonNbr - 1) / B_PER_COL
#ifdef TFT_320X480
int yPosTblText2[6] = {32, 110, 188, 266, 344, 422};    // index = (buttonNbr - 1) / B_PER_COL
#else
//int yPosTblText2[6] = {22, 74, 126, 178, 230, 282};   // index = (buttonNbr - 1) / B_PER_COL
#endif
//
//    Draw Button
//        Input:  buttonNbr = Button Number
//                color = Color of Button Text
//                text = Button Text (first line)
//                text2 = Second of Button Text (if not blank, "")
//
void drawBtn(int buttonNbr, int color, String text, String text2)
{
  int yPos1 = 0;
  int yPos2 = 0;
  int xButPos = Button_xPos[(buttonNbr - 1) % B_PER_COL];
  int yButPos = Button_yPos[(buttonNbr - 1) / B_PER_COL];
  //  First validate Button Number
  if ((buttonNbr < 1) || (buttonNbr > BUTTON_CNT)) return;
  // Push Text Attributes on attribute stack
  pushTA();
  int xPos = xPosTblText[(buttonNbr - 1) % B_PER_COL];
  setGfxFont(FSS9);
  myTFT.setTextSize(1);
  myTFT.setTextColor(color, TFT_BLACK);
  myTFT.setTextDatum(MC_DATUM);         // Middle-Center Text
  //  Determine if Button contains one or two lines of text
  if (text2.length() == 0)  // if one line of text use table #1
  {
    yPos1 = yPosTblText1[(buttonNbr - 1) / B_PER_COL];
  }
  else  // if two lines of text use table #2 for first line
  {
    yPos1 = yPosTblText2[(buttonNbr - 1) / B_PER_COL];
    yPos2 = yPos1 + 16;             // Second line of text is at +16
  }
  //  Draw blank Button
  myTFT.fillRoundRect(xButPos , yButPos , B_WIDTH  , B_HEIGHT  , B_RADIUS , TFT_BLACK);
  myTFT.drawRoundRect(xButPos , yButPos , B_WIDTH  , B_HEIGHT  , B_RADIUS , TFT_YELLOW);

  // Put text into Button
  myTFT.drawString(text, xPos, yPos1);
  if (yPos2) myTFT.drawString(text2, xPos, yPos2);
  // Pop Text Attributes from attribute stack
  popTA();
}

void drawBtn5(String text) {drawBtn( 5, TFT_GREEN, text, "");}
void drawBtn5d(String text, String text2) {drawBtn( 5, TFT_GREEN, text, text2);}
void drawBtn6d(String text, String text2) {drawBtn( 6, TFT_GREEN, text, text2);}
void drawBtn7d(String text, String text2) {drawBtn( 7, TFT_GREEN, text, text2);}
void drawBtn8(String text) {drawBtn( 8, TFT_GREEN, text, "");}
void drawBtn8d(String text, String text2) {drawBtn( 8, TFT_GREEN, text, text2);}
void drawBtn9(String text) {drawBtn( 9, TFT_GREEN, text, "");}
void drawBtn9d(String text, String text2) {drawBtn( 9, TFT_GREEN, text, text2);}
void drawBtn10d(String text, String text2) {drawBtn( 10, TFT_GREEN, text, text2);}
void drawBtn11d(String text, String text2) {drawBtn( 11, TFT_GREEN, text, text2);}
void drawBtn12(String text) {drawBtn( 12, TFT_GREEN, text, "");}
void drawBtn12d(String text, String text2) {drawBtn( 12, TFT_GREEN, text, text2);}
void drawBtn13(String text) {drawBtn( 13, TFT_GREEN, text, "");}
void drawBtn13d(String text, String text2) {drawBtn( 13, TFT_GREEN, text, text2);}
void drawBtn14d(String text, String text2) {drawBtn( 14, TFT_GREEN, text, text2);}
void drawBtn15d(String text, String text2) {drawBtn( 15, TFT_GREEN, text, text2);}
void drawBtn16(String text) {drawBtn( 16, TFT_GREEN, text, "");}
void drawBtn16d(String text, String text2) {drawBtn( 16, TFT_GREEN, text, text2);}
void drawBtn17(String text) {drawBtn( 17, TFT_GREEN, text, "");}
void drawBtn17d(String text, String text2) {drawBtn( 17, TFT_GREEN, text, text2);}
void drawBtn20(String text) {drawBtn( 20, TFT_GREEN, text, "");}
void drawBtn21(String text) {drawBtn( 21, TFT_GREEN, text, "");}
void drawBtn21d(String text, String text2) {drawBtn( 21, TFT_GREEN, text, text2);}
void drawBtn22d(String text, String text2) {drawBtn( 22, TFT_GREEN, text, text2);}
void drawBtn23d(String text, String text2) {drawBtn( 23, TFT_GREEN, text, text2);}
void drawBtn24(String text) {drawBtn( 24, TFT_GREEN, text, "");}

void drawBtnCancel(void) {drawBtn( 23, TFT_GREEN, "Cancel", "");}
void drawBtnExit(void) {drawBtn( 24, TFT_GREEN, "Exit", "");}
void drawBtnExitSave(void) {drawBtn( 24, TFT_GREEN, "Exit", "& Save");}





////////////////////////////////////////////////////////////
//
//  Draw switch 
//      xPos = left most pixel, yPos = top most pixel
//      switch position is ON = true, OFF = false (ON is right, OFF is left)
//
void drawSwitch(SWITCH_STRUCT sw, boolean swPosition)
{
  pushTA();
  int xPos = sw.xPos;
  int yPos = sw.yPos;
  int xSize = sw.xSize;
  int ySize = sw.ySize;
  int radius = sw.radius;
  int xLeftStrPos = xPos - 25;
  int xRightStrPos = xPos + xSize + 20;
  int yMidStrPos = yPos + ySize/2;
  
  setGfxFont(FSS9);
  myTFT.setTextSize(1);          // Text size multiplier
  myTFT.setTextColor(TFT_WHITE);
  myTFT.setTextDatum(MC_DATUM);         // Middle-Center Text
  if (swPosition == true)   // ON
  { 
    myTFT.fillRoundRect(xPos+1, yPos+1, xSize-2, ySize-2, radius, 0x014); // 0x14 == Blue
    myTFT.drawRoundRect(xPos, yPos, xSize, ySize, radius, TFT_WHITE);
    myTFT.drawRoundRect(xPos+1, yPos+1, xSize-2, ySize-2, radius, TFT_WHITE);
    myTFT.fillCircle(xPos + xSize - 20, yPos + ySize/2, radius-3, TFT_WHITE);  
    myTFT.drawCircle(xPos + xSize - 20, yPos + ySize/2, radius-3, TFT_BLACK);
    if(sw.textPos == SW_TXT_RIGHT) myTFT.drawString("ON", xRightStrPos, yMidStrPos);
    if(sw.textPos == SW_TXT_LEFT) myTFT.drawString("ON", xLeftStrPos, yMidStrPos);
  }
  else    // OFF
  {
    myTFT.fillRoundRect(xPos+1, yPos+1, xSize-2, ySize-2, radius, TFT_BLACK); 
    myTFT.drawRoundRect(xPos, yPos, xSize, ySize, radius, TFT_WHITE);
    myTFT.drawRoundRect(xPos+1, yPos+1, xSize-2, ySize-2, radius, TFT_WHITE);    
    myTFT.fillCircle(xPos + 20, yPos + ySize/2, radius-3, TFT_DARKGREY);
    myTFT.drawCircle(xPos + 20, yPos + ySize/2, radius-3, TFT_WHITE);
    if(sw.textPos == SW_TXT_RIGHT) myTFT.drawString("OFF", xRightStrPos, yMidStrPos);
    if(sw.textPos == SW_TXT_LEFT) myTFT.drawString("OFF", xLeftStrPos, yMidStrPos);
  }
  if(sw.textPos == SW_TXT_BOTH)
  {
    myTFT.drawString("OFF", xLeftStrPos, yMidStrPos);
    myTFT.drawString("ON", xRightStrPos, yMidStrPos);
  }
  popTA();
}

#if 0
//////////////////////////////////////
//
//
//
void drawDelaySlider(int baDelay, int yPos)
{
  myTFT.fillRoundRect(0, yPos-2, 319, 116, 3, TFT_BKGND);
  myTFT.drawRoundRect(0, yPos-2, 319, 116, 3, TFT_GRAY); 
  int xPosDly = 159 + baDelay;     /// Delay  Slider position
  char buf[8];
  pushTA();
  myTFT.setTextDatum(TC_DATUM);
  myTFT.setTextColor(TFT_WHITE);
  setGfxFont(FSS12);
  myTFT.drawString("Minutes", 160, yPos+4);
  
  setGfxFont(FSS9);
  myTFT.drawString("0", 160, yPos+29);
  myTFT.fillRoundRect(10, yPos+49, 300, 25, 3, TFT_DARKGREEN);
  myTFT.drawRoundRect(10, yPos+49, 300, 25, 3, TFT_WHITE); 
  myTFT.drawString("before", 35, yPos+29);
  myTFT.drawString("after", 285, yPos+29);
  // draw ticks
  for(int i = 20; i < 320; i += 20)
  {
    myTFT.drawFastVLine(i, yPos+75, 10, TFT_GRAY);
  }
  if((baDelay >= -120) && (baDelay <= 120))
  {
    myTFT.fillRect(xPosDly-5, yPos+47, 11, 29, TFT_GREEN);
    myTFT.fillRect(xPosDly-1, yPos+49, 3, 25, TFT_BLACK);
    //myTFT.drawFastVLine(xPosDly, yPos, 25, TFT_BLACK);
    sprintf(buf,"%d",abs(baDelay));
    myTFT.drawString(buf, xPosDly, yPos + 90);
  }
  popTA(); 
}
#endif
