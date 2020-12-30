#ifndef IGINO_Scheduler_H
#define IGINO_Scheduler_H

#include <Arduino.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

typedef struct IGINO_Alarm
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
}; 

class IGINO_Scheduler
{
private:
    ThreeWire *_wire;
    RtcDS1302<ThreeWire> *_rtc;
    RtcDateTime _lastValue;
    IGINO_Alarm *_alarms;
    int *_alarmsLastDay;
    uint8_t _alarmsLength;
    bool sameDay(IGINO_Alarm alarm);

public:
    IGINO_Scheduler(uint8_t ioPin, uint8_t clkPin, uint8_t cePin);
    ~IGINO_Scheduler();
    void init();
    void run();
    IGINO_Alarm IGINO_Scheduler::newAlarm(uint16_t year,
                                          uint8_t month,
                                          uint8_t day,
                                          uint8_t hour,
                                          uint8_t minutes,
                                          uint8_t seconds);
    bool addAlarm(uint16_t year,
                  uint8_t month,
                  uint8_t day,
                  uint8_t hour,
                  uint8_t minutes,
                  uint8_t seconds);
    bool addAlarm(IGINO_Alarm alarm);
    bool isTimeToDispatchPill();
};

#endif