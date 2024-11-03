#ifdef DS3231_RTC
#include <RTClib.h>
RTC_DS3231 rtc;
DateTime dt;
#endif

#ifdef RV3028_C7
#include <RV3028C7.h>
RV3028C7 rtc;
#endif

#define GMT_TIME_ZONE 0

#define ALARM_1 1
#define ALARM_2 2
