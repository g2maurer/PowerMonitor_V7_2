

unsigned long loopStart = 0;
unsigned long loopEnd = 0;

int sampleI;
double filteredI;
double sqV,sumV,sqI,sumI,instP,sumP;

double Irms;

void initChannels()
{
  getChanConfig(&CT1);
  //dumpCT1();

  getChanConfig(&CT2);
  //dumpCT2();

  getChanConfig(&CT3);
  //dumpCT3();

  getChanConfig(&CT4);
  //dumpCT4();
}

//
//
//
//boolean getChanConfig( CHAN_CONFIG_STRUCT *chan, const char *fn)
void getChanConfig( CHAN_CONFIG_STRUCT *chan)
{
  String fn = chanConfigFN[chan->index];
  //deleteFile(fn);
  if (!existsFileSPIFFS(fn))
  {
    //Serial.printf("Creating channel config file %c\n\r", fn);
    wrtFileSPIFFS(fn, (char *)chan, sizeof(CHAN_CONFIG_STRUCT));
  }
  else
  {
    //Serial.println("Reading channel config file");
    if (rdFileSPIFFS(fn, (char *)chan, sizeof(CHAN_CONFIG_STRUCT)))
    {
      //Serial.printf("%d: enabled: %d, range: %f, lineV: %d\n\r", 
      //    chan->index, chan->enabled, chan->range, chan->lineV);
      //Serial.printf("\r\n=== Channel %d Config successfully loaded ===", chan->index+1);
    }
  }
}

//
//
//
void saveChanConfig(void)
{
  //  Check for changes to Channel Configuration
  if((prevChanConfig.enabled != pChanConfig->enabled) ||
    (prevChanConfig.range != pChanConfig->range) ||
    (prevChanConfig.lineV != pChanConfig->lineV))
  {
    //Serial.print("\n\rChannel Configuration has Changed = ");
    //Serial.println(chanConfigFN[pChanConfig->index]);
    //Serial.printf("%d: enabled: %d, range: %f, lineV: %d\n\r", 
    //      pChanConfig->index,pChanConfig->enabled, pChanConfig->range, pChanConfig->lineV);
    wrtFileSPIFFS(chanConfigFN[pChanConfig->index], (char *)pChanConfig, sizeof(CHAN_CONFIG_STRUCT));
  } 
}

#ifdef CORE_0_TASK
///////////////////////////////////////////////////////////////
//
//
//
//
void readADC_Task( void * pvParameters )
{
  Serial.print("readADC_Task running on core ");
  Serial.println(xPortGetCoreID());
  while(1)
  {
    //
    //  Read Channel 1 ADC
    //
      chanData1.Irms = chan1readACcurrent();
      if(abs(chanData1.prevIrms - chanData1.Irms) >= 0.100) 
      {
        chanData1.watts = chanData1.Irms * (float)(CT1.lineV);
        chanData1.changed = true;
      }
      // Channel 1 Logging
      if(chanData1.Irms >= 0.100) chanData1.load = true;
      else chanData1.load = false;
      //readChan = 2;
    //
    //  Read Channel 2 ADC
    //
      chanData2.Irms = chan2readACcurrent();
      if(abs(chanData2.prevIrms - chanData2.Irms) >= 0.100) 
      {
        chanData2.watts = chanData2.Irms * (float)(CT2.lineV);
        chanData2.changed = true;
      }
      // Channel 2 Logging
      if(chanData2.Irms >= 0.100) chanData2.load = true;
      else chanData2.load = false;
      //readChan = 3;
    //
    //  Read Channel 3 ADC
    //      
      chanData3.Irms = chan3readACcurrent();
      if(abs(chanData3.prevIrms - chanData3.Irms) >= 0.100) 
      {
        chanData3.watts = chanData3.Irms * (float)(CT3.lineV);
        chanData3.changed = true;
      }
      // Channel 3 Logging
      if(chanData3.Irms >= 0.100) chanData3.load = true;
      else chanData3.load = false;
      //readChan = 4;
    //
    //  Read Channel 4 ADC
    //
      chanData4.Irms = chan4readACcurrent();
      if(abs(chanData4.prevIrms - chanData4.Irms) >= 0.100) 
      {
        chanData4.watts = chanData4.Irms * (float)(CT4.lineV);
        chanData4.changed = true;
      }
      // Channel 4 Logging
      if(chanData4.Irms >= 0.100) chanData4.load = true;
      else chanData4.load = false;
      //readChan = 1;
  }
}
#endif


//////////////////////////////////////////////////////////////////////////////////
//
//  chanXreadACcurrent - reads the appropriate ADC returning the result in milliamps.
//                The following are the steps to get to result
//                1. Zero loop counter and sum.
//                2. Repeats steps 3 through 6 for LOOP_TIME
//                3. converts each reading to milliamps
//                4. squaring the result of step 2.
//                5. adds to the sum the result of step 4.
//                6. increment loop counter.
//                7. divides the sum by the loop count
//                8. take the square root of the result of step 7. 
//                9. returns the result of step 8 (milliamps).
//                 
//

//---------------------------
//
//
float chan1readACcurrent(void)
{
  float current = 0;
#ifndef CORE_0_TASK
  if(CT1.enabled)
  {
#endif
    float voltage;
    float sum = 0;
    float factor = CT1.range;    //(float)channel->range;
    unsigned long time_check = millis();
    int counter = 0;
    while ((millis() - time_check) < LOOP_TIME)  
    {
      // voltage = ADC count * mVolts per count
#ifdef CT_LEFT_SIDE
      voltage = ads48.readADC_Differential_2_3() * multiplier;    // left side
#else
      voltage = ads49.readADC_Differential_0_1() * multiplier;    // right side
#endif
      // current = voltage * amps per volt   
      current = voltage * factor;
      // sum = sum + current * current  // (current squared)
      sum += sq(current);
      // increment loop count         
      counter++;    // = counter + 1;            
    }
    // result = square_root of the sum divided by the loop count 
    current = sqrt(sum / counter);
#ifndef CORE_0_TASK
  }
#endif
  return (current);
}

//---------------------------
//
//
float chan2readACcurrent(void)
{
  float current = 0;
#ifndef CORE_0_TASK
  if(CT2.enabled)
  {
#endif
    float voltage;
    float sum = 0;
    float factor = CT2.range;    //(float)channel->range;
    unsigned long time_check = millis();
    int counter = 0;
    while ((millis() - time_check) < LOOP_TIME)  
    {
      // voltage = ADC count * mVolts per count
#ifdef CT_LEFT_SIDE
      voltage = ads48.readADC_Differential_0_1() * multiplier;    // left side
#else
      voltage = ads49.readADC_Differential_2_3() * multiplier;    // right side
#endif
      // current = voltage * amps per volt   
      current = voltage * factor;
      // sum = sum + current * current  // (current squared)
      sum += sq(current);
      // increment loop count         
      counter++;  // = counter + 1;            
    }
    // result = square_root of the sum divided by the loop count 
    current = sqrt(sum / counter);
#ifndef CORE_0_TASK
  }
#endif
  return (current);
}

//---------------------------
//
//
float chan3readACcurrent(void)
{
  float current = 0;
#ifndef CORE_0_TASK
  if(CT3.enabled)
  {
#endif
    float voltage;
    float sum = 0;
    float factor = CT3.range;    //(float)channel->range;
    unsigned long time_check = millis();
    int counter = 0;
    while ((millis() - time_check) < LOOP_TIME)  
    {
      // voltage = ADC count * mVolts per count
#ifdef CT_LEFT_SIDE
      voltage = ads49.readADC_Differential_2_3() * multiplier;    // left side
#else
      voltage = ads48.readADC_Differential_0_1() * multiplier;    // right side
#endif
      // current = voltage * amps per volt   
      current = voltage * factor;
      // sum = sum + current * current  // (current squared)
      sum += sq(current);
      // increment loop count         
      counter++;  // = counter + 1;            
    }
    // result = square_root of the sum divided by the loop count 
    current = sqrt(sum / counter);
#ifndef CORE_0_TASK
  }
#endif
  return (current);
}

//---------------------------
//
//
float chan4readACcurrent(void)
{
  float current = 0;
  //dumpCT4();
#ifndef CORE_0_TASK
  if(CT4.enabled == true)
  {
#endif
    float voltage;
    float sum = 0;
    float factor = CT4.range;    //(float)channel->range;
    unsigned long time_check = millis();
    int counter = 0;
    while ((millis() - time_check) < LOOP_TIME)  
    {
      // voltage = ADC count * mVolts per count
#ifdef CT_LEFT_SIDE
      voltage = ads49.readADC_Differential_0_1() * multiplier;    // left side
#else
      voltage = ads48.readADC_Differential_2_3() * multiplier;    // right side
#endif
      // current = voltage * amps per volt   
      current = voltage * factor;
      // sum = sum + current * current  // (current squared)
      sum += sq(current);
      // increment loop count         
      counter++;  // = counter + 1;            
    }
    // result = square_root of the sum divided by the loop count 
    current = sqrt(sum / counter);
#ifndef CORE_0_TASK
  }
#endif
  return (current);
}



#if 0
void dumpCT1(void)
{
  Serial.printf("CT1: enabled: %d, range: %f, lineV: %d\n\r",
        CT1.enabled, CT1.range, CT1.lineV);
}

void dumpCT2(void)
{
  Serial.printf("CT2: enabled: %d, range: %f, lineV: %d\n\r",
        CT2.enabled, CT2.range, CT2.lineV);
}

void dumpCT3(void)
{
  Serial.printf("CT3: enabled: %d, range: %f, lineV: %d\n\r",
        CT3.enabled, CT3.range, CT3.lineV);
}

void dumpCT4(void)
{
  Serial.printf("CT4: enabled: %d, range: %f, lineV: %d\n\r",
        CT4.enabled, CT4.range, CT4.lineV);
}
#endif
