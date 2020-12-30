#ifndef IGINO_Config_h
#define IGINO_Config_h

#define IGINO_SERIAL_BAUD_RATE 115200

// Wifi
#define IGINO_WIFI_SERIAL_BAUD_RATE 9600
#define IGINO_WIFI_SSID "treehouse_2.4"
#define IGINO_WIFI_PASSWORD ""

// Blynk
#define IGINO_BLINK_AUTH_TOKEN "lciJtSmCdejuzz21nwM1drUl-xH6nJKl"
#define IGINO_BLINK_URL "blynk-cloud.com"
#define IGINO_BLINK_PORT (80)

// Smart Clock
#define IGINO_SMART_CLOCK_URL "igino-alarmclock.local"
#define IGINO_SMART_CLOCK_PORT (80)

//Stepper
#define STEPS_PER_REVOLUTION 200
#define MOTOR_PIN_1 11
#define MOTOR_PIN_2 10
#define MOTOR_PIN_3 9
#define MOTOR_PIN_4 8

//RTC
#define IGINO_RTC_IO_PIN 4
#define IGINO_RTC_CLK_PIN 5
#define IGINO_RTC_CE_PIN 2

#endif
