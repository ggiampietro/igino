#include "IGINO_Display.h"

/*
ref.: http://www.esp8266learning.com/wemos-mini-i2c-lcd-example.php
*/

IGINO_Display::IGINO_Display()
{
    this->_lcd = new LiquidCrystal_I2C(0x27, 16, 2);
}

IGINO_Display::~IGINO_Display()
{
    free(this->_lcd);
    this->_lcd = NULL;
}

void IGINO_Display::init()
{
    this->_lcd->init();
    this->_lcd->clear();
    this->_lcd->backlight();
}

void IGINO_Display::print(const char *line1, const char *line2)
{
    this->_lcd->clear();
    if (line1 != NULL)
    {
        this->_lcd->setCursor(0, 0);
        this->_lcd->print(line1);
    }
    if (line2 != NULL)
    {
        this->_lcd->setCursor(0, 1);
        this->_lcd->print(line2);
    }
}

void IGINO_Display::clear()
{
    this->_lcd->clear();
}
