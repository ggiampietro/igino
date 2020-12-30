#include "Arduino.h"
#include "IGINO_Config.h"
#include "IGINO_BlynkClient.h"
#include "IGINO_SmartClockClient.h"
#include "IGINO_StepperMotor.h"
#include "IGINO_Scheduler.h"
#include "IGINO_Wifi.h"

IGINO_Wifi wifi = IGINO_Wifi();
IGINO_BlynkClient blynkClient = IGINO_BlynkClient(IGINO_BLINK_AUTH_TOKEN, IGINO_BLINK_URL, IGINO_BLINK_PORT);
IGINO_SmartClockClient clockClient = IGINO_SmartClockClient(IGINO_SMART_CLOCK_URL, IGINO_SMART_CLOCK_PORT);
IGINO_Scheduler scheduler = IGINO_Scheduler(IGINO_RTC_IO_PIN, IGINO_RTC_CLK_PIN, IGINO_RTC_CE_PIN);
IGINO_StepperMotor stepper = IGINO_StepperMotor(STEPS_PER_REVOLUTION, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4);

static void addTestAlarms();

void setup()
{
  Serial.begin(IGINO_SERIAL_BAUD_RATE);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // speed must match with BAUDRATE_COMMUNICATION setting in firmware config.h (WiFiLink)
  Serial2.begin(IGINO_WIFI_SERIAL_BAUD_RATE);
  scheduler.init();
  wifi.init(&Serial2);
  addTestAlarms();
}

void loop()
{
  scheduler.run();
  if (scheduler.isTimeToDispatchPill())
  {
    Serial.println("-> IS TIME TO DISPATCH PILL");
    clockClient.notify("");
    blynkClient.notify("Es hora de tomar la pastilla :)");
    stepper.dispatchPill();
  }
  delay(1000);
}

void addTestAlarms()
{
  scheduler.addAlarm(2020, 12, 10, 15, 0, 0);
  scheduler.addAlarm(2020, 12, 10, 14, 59, 0);
  scheduler.addAlarm(2020, 12, 10, 15, 5, 0);
}