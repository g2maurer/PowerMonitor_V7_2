/////////////////////////////////////////////
//
//  Structure that defines button layout
//
struct BUTTON_STRUCT {
  //int cnt;            // number of buttons
  //int radius;         // button corner radius        
  //int height;         // size, height
  //int width;          // size, width
  int perRow;         // buttons per row, horizontal
  int perColumn;      // buttons per column, vertical
  //int butColor;
  //int shadowColor;
  int xPosS[4];       // left most pixel of each button in row
  int xPosE[4];       // right most pixel of each button in row
  int yPosS[6];       // top pixel of each button in column 
  int yPosE[6];       // bottom pixel of each button in column
  //int xPosText[4];    // horiz text position in each button (center of button)
  //int yPosText[6];    // vertical text position in each button (center of button)
  //int yPosText2[6];   // vertical text position in each button (two lines of text)
};



////////////////////////////////////////////////////////////////
//
//    Four Columns by Six Rows (24 Buttons) (Portrait)
//      Top row (left to right) is Buttons #1 #2 #3 #4
//      Second row (left to right) is Buttons #5 #6 #7 #8
//      Third row (left to right) is Buttons #9 #10 #11 #12
//      Forth row (left to right) is Buttons #13 #14 #15 #16
//      Fifth row (left to right) is Buttons #17 #18 #19 #20
//      Bottom row (left to right) is Buttons #21 #22 #23 #24
//
//      There is no Button #0 (ZERO)
//

//
//  Button Layout 4X6  (w x h)
//
#define B4X6_CNT  24
#define B4X6_RADIUS 15
#define B4X6_HEIGHT 61    //67
#define B4X6_WIDTH 68
#define B4X6_PER_ROW 4
#define B4X6_PER_COL 6

BUTTON_STRUCT b4x6 = {
  //B4X6_CNT,  
  //B4X6_RADIUS, 
  //B4X6_HEIGHT, 
  //B4X6_WIDTH, 
  B4X6_PER_ROW, 
  B4X6_PER_COL, 
  //TFT_BLUEBTN,    //TFT_DRKGREEN,       /* button color, was 0x0013 (blue) */
  //TFT_BLUESHDOW,    //TFT_BTNSHDOW,   //TFT_GREEN,   //TFT_DARKGREEN,      /* button shadow color, was 0x001f */
  {10, 88, 166, 244},   /* xPos start */
  {10+B4X6_WIDTH, 88+B4X6_WIDTH, 166+B4X6_WIDTH, 244+B4X6_WIDTH},  /* xPos end */
  {14, 92, 170, 248, 326, 404},   /* yPos start +3 */
  {14+B4X6_HEIGHT, 92+B4X6_HEIGHT, 170+B4X6_HEIGHT, 248+B4X6_HEIGHT, 326+B4X6_HEIGHT, 404+B4X6_HEIGHT},
  //{43, 121, 199, 277},            // xPos for text
  //{43, 121, 199, 277, 355, 433},  // yPos for text (single line)
  //{31, 109, 187, 265, 343, 421}   // yPos for 1st line of two lines of text
};


/////////////////////////////////////////
//
//  drawSwitch() Definitions
//
#define SW_RADIUS 15
#define SW_HEIGHT 35
#define SW_WIDTH 80
#define SW_TXT_NONE 0
#define SW_TXT_RIGHT 1
#define SW_TXT_LEFT 2
#define SW_TXT_BOTH 3

#define SW_RIGHT 2
#define SW_LEFT 1
#define SW_NONE 0


struct SWITCH_STRUCT {
  int state;      // On or Off or ?
  bool horiz;     // direction: true = horizantal, false = vertical
  int xPos;       // left most position
  int yPos;       // top most position
  int xSize;
  int ySize;
  int radius;    
  int textPos;    // 
};
