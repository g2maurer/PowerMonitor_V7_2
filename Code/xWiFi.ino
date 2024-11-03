/*
  Licensed as Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
  You are free to:
  Share — copy and redistribute the material in any medium or format
  Adapt — remix, transform, and build upon the material
  Under the following terms:
  Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
  NonCommercial — You may not use the material for commercial purposes.
  ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original
*/

//#ifndef DS3231_RTC

// WiFi Timer variables
unsigned long previousMillis = 0;
const long wifiWaitTime = 10000;  // interval to wait for Wi-Fi connection (milliseconds)


//////////////////////////////////////////////
//
//
//
void loadWiFiConfig(void)
{
#ifdef DELETE_WIFI_CONFIG
  deleteFileSPIFFS(fnWifiConfig);
#endif
  if (!existsFileSPIFFS(fnWifiConfig))
  {
    Serial.println("Creating WiFi configuration file");
    WiFiConfig.enabled = true;
    sprintf(WiFiConfig.ssID, "%s", DEFAULT_SSID);
    sprintf(WiFiConfig.passWord, "%s", DEFAULT_PASSWORD);
    WiFiConfig.ftpEnabled = false;
    sprintf(WiFiConfig.ftpUserName, "%s", DEFAULT_FTP_UN);
    sprintf(WiFiConfig.ftpPassWord, "%s", DEFAULT_FTP_PW);
    wrtFileSPIFFS(fnWifiConfig, (char *)&WiFiConfig, sizeof(WiFiConfig));
  }

  Serial.println("Reading WiFi configuration file");
  if (rdFileSPIFFS(fnWifiConfig, (char *)&WiFiConfig, sizeof(WiFiConfig)))
  {
#if 1
    Serial.println("\r\n=== WiFi Configuration ===");
    Serial.print("\t");
    Serial.println(WiFiConfig.ssID);
    Serial.print("\t");
    Serial.println(WiFiConfig.passWord);
#endif
  }
}


// Static IP address
IPAddress local_IP(192, 168, 86, 24);
// Gateway IP address
IPAddress gateway(192, 168, 86, 1);
IPAddress subnet(255, 255, 0, 0);

///////////////////////////////////////////////////////////////////
//
// Initialize WiFi - SSID and Password in SPIFFS "/wifi.bin" file
//
bool initWiFi(void)
{
  WiFi.mode(WIFI_MODE_NULL); 
  WiFi.setHostname(hostName);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFiConfig.ssID, WiFiConfig.passWord);
  //  localIP.fromString(ip.c_str());

  //  if (!WiFi.config(localIP, gateway, subnet)) {
  //    Serial.println("STA Failed to configure");
  //    return false;
  //  }
  //  WiFi.begin(ssid.c_str(), pass.c_str());
  WIFI_PRINTLN("Connecting to WiFi...");


  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  // wait up to 10 seconds for connection (wifiWaitTime)
  while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= wifiWaitTime) {
      WIFI_PRINTLN("Failed to connect.");
      //WiFi.disconnect();
      WIFI_PRINTLN(statusWiFi());
      WIFI_PRINTLN("WiFi failed to connect");
      return false;
    }
  }
  WIFI_PRINTLN(" CONNECTED");
  WIFI_PRINTLN(WiFi.localIP());
  return true;
}


//////////////////////////////////////////////////////////////
//
//
//
void wifiDisconnect(void)
{
  WiFi.disconnect(true);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WIFI_PRINTLN("Disconneting WiFi");
}


//////////////////////////////////////////////////////////////
//
//
//
String  statusWiFi(void)
{
  int status = WiFi.status();
  switch (status)
  {
    case WL_CONNECTED:
      return ("Connected");
    case WL_DISCONNECTED:
      return ("Disconnected");
    case WL_CONNECT_FAILED:
      return ("Connection Failed");
    case WL_CONNECTION_LOST:
      return ("Connection Lost");
    case WL_IDLE_STATUS:
      return ("Idle");
    case WL_SCAN_COMPLETED:
      return ("Scan Completed");
    case WL_NO_SSID_AVAIL:
      return ("No SSID Available");
    case WL_NO_SHIELD:
      return ("No Shield");
    default:
      return ("Unknown");
  }
}

//////////////////////////////////////////////////////////////
//
//  Get WiFi quality (debug only)
//
int getWiFiQuality(void)
{
  if (WiFi.status() != WL_CONNECTED)
    return -1;
  int dBm = WiFi.RSSI();
#ifdef WIFI_DEBUG
  Serial.print("RSSI = ");
  Serial.println(dBm);
#endif
  if (dBm <= -100)
    return 0;
  if (dBm >= -50)
    return 100;
#ifdef WIFI_DEBUG
  Serial.print("Quality = ");
  Serial.print(2 * (dBm + 100));
  Serial.println("%");
#endif
  return 2 * (dBm + 100);
}

///////////////////////////////////////////////////////////
//
//  WiFi Scan for SSIDs (networks)
//
#ifdef WIFI_DEBUG
void wifiScan(void)
{
  int nNetworkCount = WiFi.scanNetworks();
  // Display networks.
  if (nNetworkCount == 0)
  {
    // No networks found.
    Serial.println("0 networks found.");
  }
  else
  {

    char    chBuffer[128];
    char    chEncryption[64];
    char    chRSSI[64];
    char    chSSID[64];

    sprintf(chBuffer, "%d networks found:", nNetworkCount);
    Serial.println(chBuffer);

    for (int nNetwork = 0; nNetwork < nNetworkCount; nNetwork ++)
    {
      // Obtain ssid for this network.
      WiFi.SSID(nNetwork).toCharArray(chSSID, 64);
      sprintf(chRSSI, "(%d)", WiFi.RSSI(nNetwork));

      switch (WiFi.encryptionType(nNetwork))
      {
        case WIFI_AUTH_OPEN:
          sprintf(chEncryption, "%s", "Open");
          break;
        //return ENC_TYPE_NONE;
        case WIFI_AUTH_WEP:
          sprintf(chEncryption, "%s", "WEP");
          break;
        //return ENC_TYPE_WEP;
        case WIFI_AUTH_WPA_PSK:
          sprintf(chEncryption, "%s", "WPA/PSK");
          break;
        //return ENC_TYPE_TKIP;
        case WIFI_AUTH_WPA2_PSK:
          sprintf(chEncryption, "%s", "WPA2/PSK");
          break;
        //return ENC_TYPE_CCMP;
        case WIFI_AUTH_WPA_WPA2_PSK:
          sprintf(chEncryption, "%s", "WPA/WPA2/PSK");
          break;
        //return ENC_TYPE_AUTO;
        default:
          break;
          //return -1;
      }
      if (strlen(chSSID))    // Skip zero length SSIDs
      {
        // sprintf(chEncryption, "%s", WiFi.encryptionType(nNetwork) == WIFI_AUTH_OPEN ? " " : "*");
        sprintf(chBuffer, "%d: %s %s %s", nNetwork + 1, chSSID, chRSSI, chEncryption);
        //      sprintf(chBuffer, "%d: %s %s %d", nNetwork + 1, chSSID, chRSSI, WiFi.encryptionType(nNetwork));
        Serial.println(chBuffer);
      }
    }
    Serial.println("");
  }
}
#endif

/////////////////////////////////////////////////////////////
//
//  Fill structure with SSIDs found during scan (max 8)
//
void FillSsidStruct(void)
{
  WIFI_PRINTLN("FillSsidStruct");
  WIFI_PRINTLN(statusWiFi());
  //if(WiFi.status() == WL_DISCONNECTED)
  //WiFi.begin("0", "0");
  //  delay(1000);
  WiFi.mode(WIFI_OFF);
  delay(5000);

  int nNetworkCount = WiFi.scanNetworks();
  // Display networks.
  if (nNetworkCount > 0)
  {

    WIFI_PRINTF("Network count = %d\r\n", nNetworkCount);

    char    chSSID[32];
    //char    chBuffer[128];
    //char    chEncryption[32];
    //char    chRSSI[32];
#ifdef WIFI_DEBUG
    for (int nNetwork = 0; nNetwork < nNetworkCount; nNetwork ++)
    {

      // Obtain ssid for this network.
      WiFi.SSID(nNetwork).toCharArray(chSSID, 32);
      sprintf(chRSSI, "(%d)", WiFi.RSSI(nNetwork));

      switch (WiFi.encryptionType(nNetwork))
      {
        case WIFI_AUTH_OPEN:
          sprintf(chEncryption, "%s", "Open");
          break;
        case WIFI_AUTH_WEP:
          sprintf(chEncryption, "%s", "WEP");
          break;
        case WIFI_AUTH_WPA_PSK:
          sprintf(chEncryption, "%s", "WPA/PSK");
          break;
        case WIFI_AUTH_WPA2_PSK:
          sprintf(chEncryption, "%s", "WPA2/PSK");
          break;
        case WIFI_AUTH_WPA_WPA2_PSK:
          sprintf(chEncryption, "%s", "WPA/WPA2/PSK");
          break;
        default:
          break;
      }
      if (strlen(chSSID))    // Skip zero length SSIDs
      {
        // sprintf(chEncryption, "%s", WiFi.encryptionType(nNetwork) == WIFI_AUTH_OPEN ? " " : "*");
        sprintf(chBuffer, "%d: %s %s %s", nNetwork + 1, chSSID, chRSSI, chEncryption);
        //      sprintf(chBuffer, "%d: %s %s %d", nNetwork + 1, chSSID, chRSSI, WiFi.encryptionType(nNetwork));
        WIFI_PRINTLN(chBuffer);
      }
    }
    WIFI_PRINTLN("");

#endif

    //    if (nNetworkCount > MAX_NETWORK_CNT) nNetworkCount = MAX_NETWORK_CNT;
    //    WifiNetworks.count = nNetworkCount;
    int netCnt = 0;
    for (int i = 0; i < nNetworkCount; i++)
    {
      if (netCnt < MAX_NETWORK_CNT)
      {
        if (WiFi.RSSI(i) > -90)
        {
          // Obtain network ssid.
          WiFi.SSID(i).toCharArray(chSSID, 32);
          if (strlen(chSSID))    // Skip zero length SSIDs
          {
            WiFi.SSID(i).toCharArray(WifiNetworks.Tbl[netCnt].ssid, 31);
            WifiNetworks.Tbl[netCnt].rssi = WiFi.RSSI(i);
            WifiNetworks.Tbl[netCnt].encryptType = WiFi.encryptionType(i);

            //      Serial.println(WifiNetworks.Tbl[i].ssid);
            //      Serial.println(WiFi.SSID(i));
            //      Serial.println(WifiNetworks.Tbl[i].encryptType);
#ifdef WIFI_DEBUG
            sprintf(chRSSI, "(%d)", WifiNetworks.Tbl[netCnt].rssi);
            sprintf(chBuffer, "%d: %s %s %d", netCnt + 1, WifiNetworks.Tbl[netCnt].ssid, chRSSI, WifiNetworks.Tbl[netCnt].encryptType);
            Serial.println(chBuffer);
#endif
            netCnt++;
          }
        }
      }
    }
    WifiNetworks.count = netCnt;
  }
  else
  {
    if (nNetworkCount == 0) WIFI_PRINTLN("0 networks found.");
    else if (nNetworkCount == -1) WIFI_PRINTLN("WiFi scan running");
    else if (nNetworkCount == -2) WIFI_PRINTLN("WiFi scan failed");
    else WIFI_PRINTLN("WiFi.scanNetworks() ????");
  }
}

//#endif    //#ifndef DS3231_RTC
