
void displaySD_Menu(void)
{
  char sBuf[32];
  pushTA();
  drawPageHeader("SD Card","", false);
  if(!check4SDcard())
  {
    myTFT.setTextColor(TFT_RED);
    myTFT.drawString("SD Card Missing", 160, 100);
  }
  else if(!sdCard.mounted)
  {
    myTFT.setTextColor(TFT_RED);
    myTFT.drawString("SD Card not mounted", 160, 100);
  }
  else
  {
    myTFT.setTextColor(TFT_WHITE);
    sprintf(sBuf, "SD Type:  %s", sdCard.cType);
    myTFT.drawString(sBuf, 150, 100);
    sprintf(sBuf, "SD Size:  %.2f (GB)", sdCard.SizeGB);
    myTFT.drawString(sBuf, 150, 150);
    //sprintf(sBuf, "Capacity:  %llu bytes", sdCard.Capacity);
    sprintf(sBuf, "Capacity:  %.3f (GB)", ((float)sdCard.Capacity / 1000000000.0));
    myTFT.drawString(sBuf, 150, 200);
    //sprintf(sBuf, "Available:  %llu bytes", sdCard.Available);
    sprintf(sBuf, "Available:  %.3f (GB)", ((float)sdCard.Available / 1000000000.0));
    myTFT.drawString(sBuf, 150, 250);
    if(sdCard.Used < 1000000) sprintf(sBuf, "Used: %.3f (KB)", ((float)sdCard.Used / 1000.0));
    else if(sdCard.Used < 1000000000) sprintf(sBuf, "Used:  %.3f (MB)", ((float)sdCard.Used / 1000000.0));
    //else sprintf(sBuf, "Used:  %llu bytes", sdCard.Used);
    else sprintf(sBuf, "Used:  %.3f (GB)", ((float)sdCard.Used / 1000000000.0));
    myTFT.drawString(sBuf, 150, 300);
  }
  drawBtn21("Refresh");
  drawBtnExit();
  popTA();
}


void processSD_Menu(int button)
{
  switch(button)
  {
    case 21:              // Refresh
      if(!sdCard.mounted) init_SD();
      displaySD_Menu();
      break;
    case 24:              // Exit
      popMenu();
      break;
  }
}
