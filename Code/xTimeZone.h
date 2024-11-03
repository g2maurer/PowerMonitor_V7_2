

bool regionSelected = false;
int regionSelectIndex = 0;
int startRegion = 0;
int startCity = 0;

struct RECORD_STRUCT {
  int rSize;
  char rData[66];
} record;


//
//  Time Zone Configuration data, saved in SPIFFS, restored on boot/reboot
//
struct TZ_CONFIG_STRUCT {
  int regionIndx;
  int cityIndx;
  char tzInfo[48];
  int tzOffset;
//  double latitude;         // East / West
//  double longitude;        // North / South
} tzConfig, tzTemp;




#define REGION_COUNT 10

const char* regionName[REGION_COUNT] = { "Africa", "Americas", "Antarctica", "Asia",
                                         "Atlantic", "Australia", "Etc", "Europe",
                                         "Indian", "Pacific" };
 
struct CITY_STRUCT {
  char cityName[48];
  char tzInfo[48];
} city, changedCity;

int cityCount = 0;
int cityPage = 0;
int citySelectIndex = 0;
bool citySelected = false;
int changedCityIndx = 0;
int changedRegionIndx = 0;
char changedTzInfo[48];

File fTXT;

struct FILE_INDEX_STRUCT {
  int recordStart;
  int recordSize;
} recordIndxTbl[160];


bool getRecord(int recordIndx);
int indexFile(void);
//int getRecordCount(char *fileName);

int fileSize = 0;
int recordNbr = 0;
