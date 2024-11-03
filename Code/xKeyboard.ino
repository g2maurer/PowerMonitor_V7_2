///////////////////////////////////////////////
//
//
//
//
#define NUMBER_KEYPAD 0x20
#define UC_KEYPAD 0x40
#define LC_KEYPAD 0x60

int kbCharSet = UC_KEYPAD;
bool kbUC = true;


///////////////////////////////////////////////////
//
//
//
boolean touchKeyboard(void)
{
  boolean result = false;
  int i = 0;
  int kbCol = 0;
  int kbRow = 0;
  int x = touchData.x;
  int y = touchData.y;
  //Serial.println("touchKeyboard()");
  touchData.button = 0;   // initialize to zero
  // see if touch was in right most column (button 4, 8, 12, etc)
  if((x >= b4x6.xPosS[3]) && (x <= b4x6.xPosE[3]))
  {
    touchData.button = 4;
    result = true;
  }
  if(result == true) // if right most column
  {
    result = false;
    // buttons per column (start with 2nd row, no button in 1st row)
    for(i = 1; i < b4x6.perColumn; i++)
    {
      if((y >= b4x6.yPosS[i]) && (y <= b4x6.yPosE[i]))
      {
        // found valid column button
        touchData.button += i * b4x6.perRow;
        result = true;
        break;
      }   
    }
  }
  if(result == false)
  {
    // check for buttons 21 (Clear Text) and 22 (Backspace)
    if((y >= b4x6.yPosS[5]) && (y <= b4x6.yPosE[5]))
    {
      if((x >= b4x6.xPosS[0]) && (x <= b4x6.xPosE[0]))
      {
        touchData.button = 21;
        result = true;
      }
      else if((x >= b4x6.xPosS[1]) && (x <= b4x6.xPosE[1]))
      {
        touchData.button = 22;
        result = true;
      }
    }
  }
  if(result == false) // must be keyboard touch
  {
    for( int j = 0; j < 4; j++)   /// find column
    {
      if((x >= kbColTblS[j]) && (x <= kbColTblE[j]))
      {
        kbCol = j;
        result = true;
        break;
      }
    }
    if(result)
    {
      result = false;
      for(int k = 0; k < 8; k++)
      {
        if((y >= kbRowTblS[k]) && (y <= kbRowTblE[k]))
        {
          //kbRow = k * 4;
          touchData.kbKey = kbCol + (k * 4);
          touchData.button = 25;
          result = true;
          break;
        }
      }
    }
  }
  //if(result) Serial.printf("Button = %d\n\r", touchData.button);
  //if(touchData.button == 25) Serial.printf("kbKey = %0x\r\n", touchData.kbKey);
  return(result);
}


////////////////////////////////////////////////////////////
//
//  Display Keyboard Page (enter here !!)
//
void drawKbPage(void)
{
  drawBlankPage(false);
  pushTA();
  switch (kbCharSet)
  {
    case LC_KEYPAD:
      drawKeyboard(LC_KEYPAD);
      kbUC = true;
      break;
    case UC_KEYPAD:
      drawKeyboard(UC_KEYPAD);
      kbUC = false;
      break;
    case NUMBER_KEYPAD:
      drawKeyboard(NUMBER_KEYPAD);
      break;
    default:
      break;
  }
  //drawBtn( 8, TFT_WHITE, "ABC...", "");
  drawBtn8("ABC...");
  //drawBtn( 12, TFT_WHITE, "abc...", "");
  drawBtn12("abc...");
  //drawBtn( 16, TFT_WHITE, "123...", "");
  drawBtn16("123...");
  //drawBtn( 21, TFT_WHITE, "Clear", "Text");
  drawBtn21d("Clear", "Text");
  //drawBtn( 22, TFT_WHITE, "Back", "space");
  drawBtn22d("Back", "space");
  
  drawBtn( 20, TFT_WHITE, "Cancel", "");
  //drawBtn( 24, TFT_WHITE, "Save", "");
  drawBtn24("Save");
  
  popTA();
}

//////////////////////////////////////////
//
//  Process Keyboard Input
//
bool processKbInput(void)
{
  bool results = false;
  if (touchData.button == 8)            // select upper case keypad
  {
    drawKeyboard(UC_KEYPAD);
    kbCharSet = UC_KEYPAD;
    kbUC = true;
  }
  else if (touchData.button == 12)            // select lower case keypad
  {
    drawKeyboard(LC_KEYPAD);
    kbCharSet = LC_KEYPAD;
    kbUC = false;
  }
  else if (touchData.button == 16)       // select number keypad
  {
    kbCharSet = NUMBER_KEYPAD;
    drawKeyboard(NUMBER_KEYPAD);
  }
  else if (touchData.button == 21)       // Clear Text
    kbClearString();
  else if (touchData.button == 22)       // Backspace
    kbBackspace();
  else if (touchData.button == 20)       // Cancel
    popMenu();
  else if(touchData.button == 25)         // Virtual for keypad
  {
    getKbTouch(kbCharSet);
  }
  else if (touchData.button == 24)       // Done
  {
    if (kbStringIndex)  // was anything typed ?
    {
      if(fpKeyboardPP != NULL) (*fpKeyboardPP)();
      fpKeyboardPP = NULL;  
      //strncpy(tChan.title, kbString, strlen(kbString));
      //passSelected = true;
    }
    results = true;
    popMenu();
  }
  
  //drawKbPage();
  return results;
}

/////////////////////////////////////////////////////////
//
//  Draw Keyboard (just keyboard keys) (generic)
//
void drawKeyboard( char startChar)
{
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  myTFT.setTextDatum(TC_DATUM);
  myTFT.drawString(kbTitle, 160, 15);
  myTFT.drawFastHLine(10, 40, 300, TFT_YELLOW);
  myTFT.drawFastHLine(10, 72, 300, TFT_YELLOW);
  drawKbStr();
  char buf[40];
  int xpos = 20;
  int ypos = 80;      //was 160
  int xwidth = 40;
  int yheight = 26;
  int rowHeight = 40;
  myTFT.setTextColor(TFT_WHITE, TFT_BLUE);
  myTFT.setFreeFont(FSS9);
  // Draw Buttons (four per row, eight rows)
  for ( int r = 0; r < 8; r++)    // rows
  {
    for ( int c = 0; c < 4; c++) // columns
    {
      myTFT.fillRoundRect( xpos + (c * 55) + 1, ypos + (r * 40) + 1, xwidth, yheight, 9, TFT_BLUE);
      myTFT.drawRoundRect( xpos + (c * 55), ypos + (r * 40), xwidth + 2, yheight + 2, 9, TFT_WHITE);
      //myTFT.fillRoundRect( xpos + (c * 55) + 1, ypos + (r * 40) + 1, xwidth, yheight, 9, TFT_BLUE);
      buf[0] = startChar++ ;   /// + c + (r * 0x4));
      buf[1] = 0;
      myTFT.drawString(buf, xpos + (c * 55) + 19, ypos + (r * 40) + 7);
    }
  }
}

//////////////////////////////////////////////////////////////////
//
//  Draw Keyboard input string (generic)
//
void drawKbStr(void)
{
  myTFT.setTextDatum(TC_DATUM);
  myTFT.setTextColor(TFT_WHITE, TFT_BLACK);
  myTFT.setFreeFont(FSS9);
  myTFT.drawString( kbString, 160, 50);   //10,50);
}

////////////////////////////////////////////////////
//
//  Get Keyboard Character (screen touches)
//
void getKbTouch(char basechar)
{
  char txt = basechar;
  txt += touchData.kbKey;
  if (kbStringIndex < kbMaxCharCnt)
  {
    kbString[kbStringIndex++] = txt;
    kbString[kbStringIndex] = 0;
    drawKbStr();
  }
  //Serial.println(kbStringIndex);
}

//////////////////////////////////////////////////////////
//
//  Back Space Keyboard entry
//
void kbBackspace(void)
{
  if (kbStringIndex > 0)
  {
    kbStringIndex--;
    kbString[kbStringIndex] = 0;
    myTFT.fillRect(10, 41, 300, 30, TFT_BLACK);
    drawKbStr();
  }
}

//////////////////////////////////////////////////////////
//
//
//
void kbClearString(void)
{
  kbStringIndex = 0;
  kbString[0] = 0;
  myTFT.fillRect(10, 41, 300, 30, TFT_BLACK);
}



/////////////////////////////////////
//
//    Display Key Pad
//      layout defined by KEYPAD_STRUCT
//
void drawKeypad( KEYPAD_STRUCT *sKp)
{
  int xpos = sKp->xpos;
  int ypos = sKp->ypos;
  int bsz = sKp->bSize;
  char buf[5];
  pushTA();
  myTFT.setTextDatum(CC_DATUM);
  myTFT.setTextColor(TFT_WHITE);
  myTFT.fillRoundRect( xpos, ypos, sKp->xSize, sKp->ySize, 9, TFT_DARKGREY);
  myTFT.drawRoundRect( xpos, ypos, sKp->xSize, sKp->ySize, 9, TFT_WHITE);
  myTFT.drawFastHLine( xpos, ypos+50, sKp->xSize, TFT_WHITE);
  //
  // Draw Keys
  //
//  int kxpos = 10;     // position within the above RoundRect
//  int kypos = 10;     // position within the above RoundRect

  
  for( int y = 0; y < 4; y++)
  {
    for(int x = 0; x < 3; x++)
    {
      setGfxFont(FSS12);
      myTFT.fillRoundRect( xpos+sKp->kxpos[x], ypos + sKp->kypos[y], bsz, bsz, 9, TFT_BLUE);
      myTFT.drawRoundRect( xpos + sKp->kxpos[x], ypos + sKp->kypos[y], bsz, bsz, 9, TFT_WHITE);
      if(sKp->kChar[y][x] < 10) sprintf(buf,"%d",sKp->kChar[y][x]);
      else
      {
        if(sKp->kChar[y][x] == 10) sprintf(buf,"<");
        else 
        {
          setGfxFont(FSS9); 
          sprintf(buf,"Done");
        }
      }
      myTFT.drawString(buf, xpos+sKp->kxpos[x]+bsz/2, ypos+sKp->kypos[y]+bsz/2);
    }
  }
  popTA();
  return;
}


///////////////////////////
//
//
//
void displayValueOnKeypad(KEYPAD_STRUCT *sKp, char txtValue[])
{
  pushTA();
  myTFT.setTextDatum(CC_DATUM);
  myTFT.setTextColor(TFT_BLACK);
  // Erase previous data
  myTFT.fillRect(sKp->xpos+2, sKp->ypos+2, sKp->xSize-4, 45, TFT_DARKGREY);
  // Center text on x-axis
  setGfxFont(FSS12);
  myTFT.drawString(txtValue, sKp->xpos + sKp->xSize/2, sKp->ypos + 25);
  popTA();
}

/////////////////////////////////////////
//
//    Process Keypad Touch
//      returns key number or -1 if not valid key touch
//      
//
int processKpTouch(KEYPAD_STRUCT *sKp)
{
  int xpos = sKp->xpos;
  int ypos = sKp->ypos;
  int bsz = sKp->bSize;
  int col = -1;
  int row = -1;
  //
  // Check for valid column
  //
  for( int c = 0; c < 3; c++)
  {
    if( (touchData.x > (xpos+sKp->kxpos[c])) && (touchData.x < (xpos+sKp->kxpos[c]+bsz)) )
    {
      col = c;
      break;
    }
  }
  if(col < 0) return(col);  // touch not in column
  //
  // Check for vaild row
  //
  for( int r = 0; r < 4; r++)
  {
    if( (touchData.y > (ypos+sKp->kypos[r])) && (touchData.y < (ypos+sKp->kypos[r]+bsz)) )
    {
      row = r;
      break;
    }
  }
  if(row < 0) return(row);  // touch not in row
  //Serial.printf("row %d, col %d\n\r", row, col);
  return(sKp->kChar[row][col]);
}
