// #########################################################################
//  Meter
//      width = 240 pixels
//      height = 126 pixels  122
//
// #########################################################################


#define SHADOW_SIZE 10
#define MTR_YPOS 50
#define MTR_RADIUS 15
#define SCALE_HEIGHT 100
#define SCALE_WIDTH 100       

#define X_VERTEX 120  
#define Y_VERTEX 140   

#define MTR_SIZE 1.25       // for meter resizing. (1 for 240 X 320 screen)

float factor[5] = { 0.0, 0.0, 0.0, 0.0, 0.0};
int old_analog[5] =  {-1, -1, -1, -1, -1}; // Value last displayed
//float ltx[5] = { -1.15, -1.15, -1.15, -1.15, -1.15};   // Saved x coord of bottom of needle
float ltx[5] = { 0, 0, 0, 0, 0}; 
uint16_t osx[5] = {120, 120, 120, 120, 120};
uint16_t osy[5] = {120, 120, 120, 120, 120};   //  + anaMtr_y; // Saved x & y coords
//uint16_t mtrYpos[5] = {40, MTR_FACE_YPOS, MTR_FACE_YPOS, MTR_FACE_YPOS, MTR_FACE_YPOS};
//uint16_t mtrScale[5] = {4, 8, 16, 16, 24};   // Meter FULL Scale Value

uint16_t mWidth = 239;      // meter width including shadow
uint16_t mHeight = 126;     // meter height including shadow
uint16_t mfWidth = 230;     // meter face width
uint16_t mfHeight = 119;    // meter face height
uint16_t mX = 0;            // meter x position (upper left-hand corner)
uint16_t mY = 0;            // meter y position (upper left-hand corner)
uint16_t mfX = 5;           // meter face x offset from shadow 
uint16_t mfY = 4;           // meter face y offset from shadow
//
//
//
//

// #########################################################################
//  Draw the Ampere meter on the screen
// #########################################################################
//
//  mtrIndex is for supporting multiple meters (0 - 4).
//  x and y = screen location where the meter is to be drawn
//  fullScale = is the meter's scale (0 - fullScale)
//
//
void ampMeter(int mtrIndx, uint16_t xPos, uint16_t yPos, float fullScale)
{
  pushTA();
  char buf[8];
  float mag = MTR_SIZE;   //pChanData->mtr.mag;       // magnify 1.xx
  uint16_t mtrScale = fullScale;
  setGfxFont(FSS9);
  myTFT.setTextDatum(TC_DATUM);
  //
  //  Save meter position (needed for positioning needle)
  //
  mX = xPos;
  mY = yPos;
  factor[mtrIndx] = 100.0/fullScale;
  // Meter outline   x,y,w,h,color
  myTFT.fillRoundRect(mX, mY, mag * mWidth, mag * mHeight, MTR_RADIUS, TFT_BLUE);  //126   //Shadow
  myTFT.fillRoundRect(mX + mag * mfX, mY + mag * mfY, mag * mfWidth, mag * mfHeight, MTR_RADIUS, TFT_WHITE);  //119 // Meter Face
  
  myTFT.setTextColor(TFT_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5)     // 21 ticks
  {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = mX + sx * (mag * SCALE_WIDTH + tl) + mag * X_VERTEX;
    uint16_t y0 = mY + sy * (mag * SCALE_HEIGHT + tl) + mag * Y_VERTEX; 
    uint16_t x1 = mX + sx * (mag * SCALE_WIDTH) + mag * X_VERTEX;
    uint16_t y1 = mY + sy * (mag * SCALE_HEIGHT) + mag * Y_VERTEX;

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords in case tick lenght changed
    x0 = mX + sx * (mag * SCALE_WIDTH + tl) + mag * X_VERTEX;
    y0 = mY + sy * (mag * SCALE_HEIGHT + tl) + mag * Y_VERTEX;
    x1 = mX + sx * (mag * SCALE_WIDTH) + mag * X_VERTEX;
    y1 = mY + sy * (mag * SCALE_HEIGHT) + mag * Y_VERTEX;

    // Draw tick
    myTFT.drawLine(x0, y0, x1, y1, TFT_BLACK);

    // Check if labels should be drawn, with position tweaks
    // Five label are to be drawn
    // Full Scale MUST be a multiple of 4 
    // Label = full scale / 4
    //    Example: If full scale is 20  then labels are
    //        0 = 0 * 16/4
    //        8 = 1 * 16/4
    //        8 = 2 * 16/4
    //        12 = 3 * 16/4
    //        16 = 4 * 16/4 
    if (i % 25 == 0)   
    {
      // Calculate label positions
      x0 = mX + sx * (mag * SCALE_WIDTH + tl + 10) + mag * X_VERTEX;
      y0 = mY + sy * (mag * SCALE_HEIGHT + tl + 10) + mag * Y_VERTEX;
      switch (i / 25)
      {
        case -2: 
          myTFT.drawString("0", x0, y0 - 12); 
          break;
        case -1:
          sprintf(buf,"%d",1 * mtrScale/4); 
          myTFT.drawString(buf, x0, y0 - 9);
          //myTFT.drawCentreString("5", x0, y0 - 9, 2); 
          break;
        case 0: 
          sprintf(buf,"%d",2 * mtrScale/4); 
          myTFT.drawString(buf, x0, y0 - 6);
          //myTFT.drawCentreString("10", x0, y0 - 6, 2); 
          break;
        case 1: 
          sprintf(buf,"%d",3 * mtrScale/4);
          myTFT.drawString(buf, x0, y0 - 9); 
          //myTFT.drawCentreString("15", x0, y0 - 9, 2); 
          break;
        case 2: 
          sprintf(buf,"%d",4 * mtrScale/4); 
          myTFT.drawString(buf, x0, y0 - 12); 
          //myTFT.drawCentreString("20", x0, y0 - 12, 2); 
          break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = mX + sx * mag * SCALE_WIDTH + mag * X_VERTEX;
    y0 = mY + sy * mag * SCALE_HEIGHT + mag * Y_VERTEX;
    
    // Draw scale arc, don't draw the last part
    if (i < 50) myTFT.drawLine(x0, y0, x1, y1, TFT_BLACK);
    //Serial.printf("x0=%d, y0=%d, x1=%d, y1=%d\n\r",x0, y0, x1, y1);
  }
  //myTFT.drawCentreString("DC Volts", X_VERTEX, ypos + 65, 2); // Comment out to avoid font 4
  myTFT.drawString("Amperes", mX + mag * X_VERTEX, mY + mag * 65);
  //myTFT.drawCentreString("photovoltaic", X_VERTEX, ypos + 80, 2); // Comment out to avoid font 4
  //myTFT.drawRect(5, ypos + 3, 230, 115, TFT_BLACK); // Draw bezel line 119
  myTFT.drawRoundRect(mX + mfX, mY + mfY, mag * mfWidth, mag * mfHeight, MTR_RADIUS, TFT_BLACK); // Draw bezel
  // make previous meter value 1 so that the plotNeedle at 0 occurs
  old_analog[mtrIndx] = 1;
  plotNeedle(0, 0, mtrIndx); // Put meter needle at 0
  popTA();
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void plotNeedle(  float mA, byte ms_delay, int mtrIndx)
{
  pushTA();
  //Serial.printf("plotNeedle: %f  %d,  %d\n\r", mA, ms_delay, mtrIndx);
  int value = mA * factor[mtrIndx];
  float mag = MTR_SIZE;     //pChanData->mtr.mag;       // magnify 1.xx
  setGfxFont(FSS9);
  myTFT.setTextDatum(TC_DATUM);
  //Serial.printf("value = %d\n\r", value);
  myTFT.setTextColor(TFT_BLACK, TFT_WHITE);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle until new value reached
  while (!(value == old_analog[mtrIndx])) 
  {
    if (old_analog[mtrIndx] < value) old_analog[mtrIndx]++;
    else old_analog[mtrIndx]--;

    if (ms_delay == 0) old_analog[mtrIndx] = value; // Update immediately id delay is 0

    float sdeg = map(old_analog[mtrIndx], -10, 110, -150, -30); // Map value to angle
    //float sdeg = map(old_analog[mtrIndx], -10, 110, -160, -20); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    myTFT.drawLine(mX + mag * (X_VERTEX + 20 * ltx[mtrIndx] - 1), mY + mag * (Y_VERTEX - 20), mX + osx[mtrIndx] - 1, mY + osy[mtrIndx], TFT_WHITE);
    myTFT.drawLine(mX + mag * (X_VERTEX + 20 * ltx[mtrIndx]), mY + mag * (Y_VERTEX - 20), mX + osx[mtrIndx], mY + osy[mtrIndx], TFT_WHITE);
    myTFT.drawLine(mX + mag * (X_VERTEX + 20 * ltx[mtrIndx] + 1), mY + mag * (Y_VERTEX - 20), mX + osx[mtrIndx] + 1, mY + osy[mtrIndx], TFT_WHITE);

    // Re-plot text under needle
    myTFT.setTextColor(TFT_BLACK);
    //myTFT.drawCentreString("DC Volts", X_VERTEX, 65 + ypos, 2); // // Comment out to avoid font 4
    myTFT.drawString("Amperes", mX + mag * X_VERTEX, mY + mag * 65);
    //myTFT.drawCentreString("photovoltaic", X_VERTEX, ypos + 80, 2); // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx[mtrIndx] = tx;
    osx[mtrIndx] = mag * (sx * (SCALE_WIDTH-2) + X_VERTEX);    
    osy[mtrIndx] = mag * (sy * (SCALE_HEIGHT-2) + Y_VERTEX);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle      ypos + 116

    myTFT.drawLine(mX + mag * (X_VERTEX + 20 * ltx[mtrIndx] - 1), mY + mag * (Y_VERTEX - 20), mX + osx[mtrIndx] - 1, mY + osy[mtrIndx], TFT_RED);
    myTFT.drawLine(mX + mag * (X_VERTEX + 20 * ltx[mtrIndx]), mY + mag * (Y_VERTEX - 20), mX + osx[mtrIndx], mY + osy[mtrIndx], TFT_MAGENTA);
    myTFT.drawLine(mX + mag * (X_VERTEX + 20 * ltx[mtrIndx] + 1), mY + mag * (Y_VERTEX - 20), mX + osx[mtrIndx] + 1, mY + osy[mtrIndx], TFT_RED);
    
    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog[mtrIndx] - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
  popTA();
}
