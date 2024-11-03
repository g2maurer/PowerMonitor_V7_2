// #############################################################
//
//      TTTTTTT   FFFFFFF   TTTTTTT 
//         T      F            T   
//         T      FFFF         T
//         T      F            T
//         T      F            T
//
// #############################################################
//
//  TFT Screen
//
//

#define lineHeight  25


////////////////////////////////////////////////////////////////
//
//  Additional TFT Screen Colors
//
//
//        RRRR RGGG GGGB BBBB
//
#define TFT_GREY 0x5AEB
#define TFT_BLUEBTN 0x0013
#define TFT_BLUESHDOW ((75 / 8) << 11) | ((75 / 4) << 5) | (130 / 8)
#define TFT_BKGND ((75 / 8) << 11) | ((75 / 4) << 5) | (75 / 8)   // Dark Gray
#define TFT_GRAY ((155 / 8) << 11) | ((155 / 4) << 5) | (155 / 8)   // Gray
#define TFT_DRKGREEN ((50 / 8) << 11) | ((135 / 4) << 5) | (0 / 8)   // Dark Green
#define TFT_BTNSHDOW ((70 / 8) << 11) | ((200 / 4) << 5) | (0 / 8)   // Dark Green Yellow


// #############################################################
//
//      TTTTTTT   OOOOO    U     U    CCCCC    H     H
//         T     O     O   U     U   C     C   H     H
//         T     O     O   U     U   C         HHHHHHH
//         T     O     O   U     U   C     C   H     H
//         T      ooooo     UUUUU     CCCCC    H     H
//
// #############################################################

//#define DEBUG_TOUCH
#ifdef DEBUG_TOUCH
#define TOUCH_PRINT(x) Serial.print(x)
#define TOUCH_PRINTLN(x) Serial.println(x)
#define TOUCH_PRINTF(x,y) Serial.printf(x,y)
#else
#define TOUCH_PRINT(x)
#define TOUCH_PRINTLN(x)
#define TOUCH_PRINTF(x,y)
#endif

struct touchTFT {
  int x;
  int y;
  //int frame;
  int column;
  int row;        // row is only valid if frame==PAGE_FRAME
  int button;
  int keypad;     // keypad key (number)
  int kbKey;      // keyboard key
} touchData;


bool calibrateTftTouch = false;

//
//          Buttons - Screen Layout 4X6  (320 X 480)
//
//  |------------|    |------------|    |------------|    |------------|
//  | Button #1  |    | Button #2  |    | Button #3  |    | Button #4  |
//  |------------|    |------------|    |------------|    |------------|
//
//  |------------|    |------------|    |------------|    |------------|
//  | Button #5  |    | Button #6  |    | Button #7  |    | Button #8  |
//  |------------|    |------------|    |------------|    |------------|
//
//  |------------|    |------------|    |------------|    |------------|
//  | Button #9  |    | Button #10 |    | Button #11 |    | Button #12 |
//  |------------|    |------------|    |------------|    |------------|
//
//  |------------|    |------------|    |------------|    |------------|
//  | Button #13 |    | Button #14 |    | Button #15 |    | Button #16 |
//  |------------|    |------------|    |------------|    |------------|
//
//  |------------|    |------------|    |------------|    |------------|
//  | Button #17 |    | Button #18 |    | Button #19 |    | Button #20 |
//  |------------|    |------------|    |------------|    |------------|
//
//  |------------|    |------------|    |------------|    |------------|
//  | Button #21 |    | Button #22 |    | Button #23 |    | Button #24 |
//  |------------|    |------------|    |------------|    |------------|
//
//
