
#ifdef SD_SUPPORT
/////////////////////////////////////
//
//  Initialize SD Card Interface
//    called just once from setup().
//
void init_SD(void)
{
  hspi.begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);
  pinMode(HSPI_SS, OUTPUT);
  digitalWrite(HSPI_SS, HIGH);
  mountSD();
}

///////////////////////////////////
//
//    Mount SD Card.
//
void mountSD(void)
{
  //
  // Detect if SD card is present
  //
  pinMode(SD_CARD_DET, INPUT);
  sdCard.present = false;
  //delay(100);
  if(check4SDcard())
  {
    //
    // Initialize SD card 
    //
    if(!SD.begin(HSPI_SS, hspi, SD_SPI_FREQ)) 
    {
      Serial.println("Card Mount Failed !!!");
      sdCard.mounted = false;
      return;
    }
    sdCard.Type = SD.cardType();
    if(determineSDCardType() == false)
    {
      Serial.println("Invalid SD card attached");
      return;
    }
    sdCard.mounted = true;
    sdCard.Size = SD.cardSize();
    sdCard.SizeGB = float(SD.cardSize() / (1000.0 * 1000.0 * 1000.0));
    Serial.printf("SD Card Size: %llu bytes\n", SD.cardSize());
    Serial.printf("SD Card Size: %llu MB\n", SD.cardSize() / (1000*1000));
    Serial.printf("SD Card Size: %.2f GB\n",sdCard.SizeGB);

    sdCard.Capacity = SD.totalBytes();
    Serial.printf("Capacity: %llu bytes\n", SD.totalBytes());

    Serial.printf("Available: %llu bytes\n", SD.totalBytes()-SD.usedBytes()); 
    sdCard.Available = SD.totalBytes()-SD.usedBytes();
    sdCard.Used = SD.usedBytes();
    Serial.printf("Used: %llu bytes\n", SD.usedBytes());
  
    Serial.println("");

    fileCnt = 0;
    dirCnt = 0;
    File dir =  SD.open("/");
    listDir(SD, "/", 1);
    Serial.println("");
  }
}
#endif

//////////////////////////////////
//
//  Check to see if SD Card is present (inserted)
//
boolean check4SDcard(void)
{
  //Serial.println(digitalRead(SD_CARD_DET));
  if(digitalRead(SD_CARD_DET) == 1) 
  {
    Serial.println("SD Card Missing");
    //SD_CardPresent = false;
    sdCard.present = false;
    if(sdCard.mounted)
    {
      sdCard.mounted = false;
      SD.end();
    }  
  }
  else
  {
    Serial.println("SD Card Present");
    //SD_CardPresent =  true;
    sdCard.present = true;
  }
  return(sdCard.present);
}

//////////////////////////////////
//
//    Determine SD Card Type
//        returns false is card type indeterminate.
//
boolean determineSDCardType(void)
{
  boolean result = true;
  sdCard.Type = SD.cardType();
  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (sdCard.Type) 
  {
    case CARD_NONE:
      //Serial.println("NONE");
      sprintf(sdCard.cType, "NONE");
      result = false;
      break;
    case CARD_MMC:
      //Serial.println("MMC");
      sprintf(sdCard.cType, "MMC");
      break;
    case CARD_SD:
      //Serial.println("SD");
      sprintf(sdCard.cType, "SD");
      break;
    case CARD_SDHC:
      //Serial.println("SDHC");
      sprintf(sdCard.cType, "SDHC");
      break;
    default:
      //Serial.println("Unknown");
      sprintf(sdCard.cType, "Unknown");
      result = false;
  }
  Serial.println(sdCard.cType);
  Serial.println("");
  return(result);
}
