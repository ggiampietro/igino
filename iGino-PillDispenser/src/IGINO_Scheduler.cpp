#include "IGINO_Scheduler.h"

#define countof(a) (sizeof(a) / sizeof(a[0]))
#define MAX 10

IGINO_Scheduler::IGINO_Scheduler(uint8_t ioPin, uint8_t clkPin, uint8_t cePin)
{
    this->_wire = new ThreeWire(ioPin, clkPin, cePin);
    this->_rtc = new RtcDS1302<ThreeWire>(*this->_wire);
    this->_alarms = new IGINO_Alarm[MAX];
    this->_alarmsLastDay = new int[MAX];
    for (uint8_t i = 0; i < this->_alarmsLength; i++)
    {
        // this->_alarms[i] = NULL;
        this->_alarmsLastDay[i] = 0;
    }
    this->_alarmsLength = 0;
}

IGINO_Scheduler::~IGINO_Scheduler()
{
    free(this->_rtc);
    this->_rtc = NULL;
    free(this->_alarms);
    free(this->_wire);
    this->_wire = NULL;
}

void printDateTime(const RtcDateTime &dt)
{
    char datestring[20];
    snprintf_P(datestring,
               countof(datestring),
               PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
               dt.Month(),
               dt.Day(),
               dt.Year(),
               dt.Hour(),
               dt.Minute(),
               dt.Second());
    Serial.print(datestring);
}

void printAlarm(const IGINO_Alarm &alarm)
{
    char datestring[20];
    snprintf_P(datestring,
               countof(datestring),
               PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
               alarm.month,
               alarm.day,
               alarm.year,
               alarm.hour,
               alarm.minutes,
               alarm.seconds);
    Serial.print(datestring);
}

void IGINO_Scheduler::init()
{
    this->_rtc->Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Serial.print("compiled at: ");
    printDateTime(compiled);
    Serial.println();

    if (!this->_rtc->IsDateTimeValid())
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        this->_rtc->SetDateTime(compiled);
    }

    if (this->_rtc->GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        this->_rtc->SetIsWriteProtected(false);
    }

    if (!this->_rtc->GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        this->_rtc->SetIsRunning(true);
    }

    this->_lastValue = this->_rtc->GetDateTime();
    if (this->_lastValue < compiled)
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        this->_rtc->SetDateTime(compiled);
        this->_lastValue = compiled;
    }
}

void IGINO_Scheduler::run()
{
    this->_lastValue = this->_rtc->GetDateTime();

#if IGINO_DEBUG_RTC
    printDateTime(this->_lastValue);
    Serial.println();
#endif

    if (!this->_lastValue.IsValid())
    {
        // Common Causes: the battery on the device is low or
        // even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }
}

bool IGINO_Scheduler::sameDay(IGINO_Alarm alarm)
{
    return this->_lastValue.Year() == alarm.year &&
           this->_lastValue.Month() == alarm.month &&
           this->_lastValue.Day() == alarm.day;
}

bool IGINO_Scheduler::isTimeToDispatchPill()
{
    IGINO_Alarm alarm;
    for (uint8_t i = 0; i < this->_alarmsLength; i++)
    {
        alarm = this->_alarms[i];
        printAlarm(alarm);
        Serial.println();
        if (this->sameDay(alarm) &&
            this->_lastValue.Minute() == alarm.minutes &&
            // to trigger the alarm one per day
            this->_alarmsLastDay[i] != alarm.day)
        {
            this->_alarmsLastDay[i] = alarm.day;
            return true;
        }
    }
    return false;
}

IGINO_Alarm IGINO_Scheduler::newAlarm(uint16_t year,
                                      uint8_t month,
                                      uint8_t day,
                                      uint8_t hour,
                                      uint8_t minutes,
                                      uint8_t seconds)
{
    IGINO_Alarm alarm;
    alarm.year = year;
    alarm.month = month;
    alarm.day = day;
    alarm.hour = hour;
    alarm.minutes = minutes;
    alarm.seconds = seconds;
    return alarm;
}

bool IGINO_Scheduler::addAlarm(IGINO_Alarm alarm)
{
    if (this->_alarmsLength + 1 <= MAX)
    {
        this->_alarms[this->_alarmsLength] = alarm;
        this->_alarmsLength++;
        return true;
    }

    Serial.println("Reached max number alowed alarms");
    return false;
}

bool IGINO_Scheduler::addAlarm(uint16_t year,
                               uint8_t month,
                               uint8_t day,
                               uint8_t hour,
                               uint8_t minutes,
                               uint8_t seconds)
{
    IGINO_Alarm alarm = this->newAlarm(year, month, day, hour, minutes, seconds);
    return this->addAlarm(alarm);
}