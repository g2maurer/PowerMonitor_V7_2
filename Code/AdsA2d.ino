  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

/*     Data rates
 *      
 *      void setDataRate(uint16_t rate);
 *      uint16_t getDataRate();
 *
#define RATE_ADS1015_128SPS (0x0000)  ///< 128 samples per second
#define RATE_ADS1015_250SPS (0x0020)  ///< 250 samples per second
#define RATE_ADS1015_490SPS (0x0040)  ///< 490 samples per second
#define RATE_ADS1015_920SPS (0x0060)  ///< 920 samples per second
#define RATE_ADS1015_1600SPS (0x0080) ///< 1600 samples per second (default)
#define RATE_ADS1015_2400SPS (0x00A0) ///< 2400 samples per second
#define RATE_ADS1015_3300SPS (0x00C0) ///< 3300 samples per second

#define RATE_ADS1115_8SPS (0x0000)   ///< 8 samples per second
#define RATE_ADS1115_16SPS (0x0020)  ///< 16 samples per second
#define RATE_ADS1115_32SPS (0x0040)  ///< 32 samples per second
#define RATE_ADS1115_64SPS (0x0060)  ///< 64 samples per second
#define RATE_ADS1115_128SPS (0x0080) ///< 128 samples per second (default)
#define RATE_ADS1115_250SPS (0x00A0) ///< 250 samples per second
#define RATE_ADS1115_475SPS (0x00C0) ///< 475 samples per second
#define RATE_ADS1115_860SPS (0x00E0) ///< 860 samples per second
*/


void initADS48(void)
{
  if (!ads48.begin(0x48, &I2C_1)) {
    Serial.println("Failed to initialize ADS at 0x48.\n\r");
    //while (1);
    CT1.enabled = false;
    CT2.enabled = false;
  }
  else
  {
    ads48.setGain(GAIN_TWO);      // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
    //ads48.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
    ads48.setDataRate(RATE_ADS1015_3300SPS);
    Serial.println("\n\rADS 0x48 initialized!");
    Serial.printf("\tdata rate = %#02x\n\r", ads48.getDataRate());
    Serial.printf("\tgain = 0x%02x\n\r\n\r", ads48.getGain());
    //CT1.enabled = true;
    //CT2.enabled = true;
  }
}

void initADS49(void)
{
  if (!ads49.begin(0x49, &I2C_1)) 
  {
    Serial.println("Failed to initialize ADS at 0x49.\n\r");
    //while (1);
    CT3.enabled = false;
    CT4.enabled = false;
  }
  else
  {
    ads49.setGain(GAIN_TWO);      // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
    //ads49.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
    ads49.setDataRate(RATE_ADS1015_3300SPS);
    Serial.println("\n\rADS 0x49 initialized!");
    Serial.printf("\tdata rate = %#02x\n\r", ads49.getDataRate());
    Serial.printf("\tgain = 0x%02x\n\r\n\r", ads49.getGain());
    //CT3.enabled = true;
    //CT4.enabled = true;
  }
}
