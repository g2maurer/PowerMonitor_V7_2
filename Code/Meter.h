// #########################################################################
// Relative Humidity Meter
//      width = 240 pixels
//      height = 126 pixels
//
// #########################################################################

//    Meter.h





#define anaMtr_y 70

#define THERMO_X  40      // was 30
#define THERMO_Y  80
#define HYDROM_X  180     //was 190
#define HYDROM_Y  80
#define THERMO2_X  180     //was 190
#define THERMO2_Y  80


//
// FunctionPrototypes
//
void analogMeter(int mtrIndx);
void plotNeedle(  float mA, byte ms_delay, int mtrIndx);
void analogVertometer(int x, int y, int color);
void drawThermometerScale(int xpos, int ypos, int location, bool scaleRight);
void UpdateThermometer(int xpos, int ypos, int temp, bool scaleRight);
void drawHydrometerScale(void);
void UpdateHydrometer(int humid);
void  RH_Fan(void);
void  rotateFan(void);
int getRunTime(void);
void displayFanRuntime(void);
void displayRuntime(int runTime);
