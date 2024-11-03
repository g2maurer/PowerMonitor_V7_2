
struct LOG_CONFIG_STRUCT {
  boolean enabled;
  int state;
  boolean eventLog;     // event logging, OR of all ampCT enable flags
  float pad;            // was Event Amps
  boolean intervalLog;  // interval logging
  int timeInterval;     // seconds
  boolean eLogCT[5];    // CT event (on/off)
  float ampCT[5];       // Amps
  boolean logTemperature;
} LogConfig;

enum LOG_STATE { LOG_IDLE, LOG_STOP, LOG_START, LOG_EVENT, LOG_INTERVAL, LOG_EVENT_N_INTERVAL };
