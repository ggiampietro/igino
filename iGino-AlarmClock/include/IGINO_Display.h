#ifndef IGINO_Display_h
#define IGINO_Display_h

#include "LiquidCrystal_I2C.h"

class IGINO_Display
{
private:
    LiquidCrystal_I2C *_lcd;

public:
    IGINO_Display();
    ~IGINO_Display();
    void init();
    void print(const char *line1, const char *line2);
    void clear();
};

#endif