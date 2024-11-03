///////////////////////////////////////////////
//
//    320 x 480 (portrait)
//
int kbColTblS[4] = {18, 73, 128, 183};    // Start
int kbColTblE[4] = {62, 117, 172, 227};   // End
int kbRowTblS[8] = {88, 128, 168, 208, 248, 288, 328, 368};   // Start
int kbRowTblE[8] = {118, 158, 198, 238, 278, 318, 358, 398};  // End

//
//  480 x 320 (Landscape)
//
//int kbRowTblS[8] = {168, 208, 248, 288, 328, 368, 408, 448};  //Start
//int kbRowTblE[8] = {198, 238, 278, 318, 358, 398, 438, 478};  // End

///////////////////////////////////////////////////////
//
//    Key Pad definitions
//
//
struct KEYPAD_STRUCT {
  int bSize;      // Key button size (both x & y (square))
  int xSize;      // Keypad screen width
  int ySize;      // Keypad screen height
  int xpos;       // Keypad screen x position (upper left corner)
  int ypos;       // Keypad screen y position (upper left corner)
  int kxpos[3];  // Key x positions
  int kypos[4];  // Key y positions
  byte kChar[4][3];  // Value of Keys [row][col]
};

KEYPAD_STRUCT iKp = { 66, 246, 380, 37, 70, { 10, 90, 170}, { 64, 144, 224, 304}, 
                    {{1,2,3},{4,5,6},{7,8,9},{10,0,11}} };
