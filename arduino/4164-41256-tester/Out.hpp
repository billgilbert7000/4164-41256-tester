//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Types.hpp"
#include "Font.hpp"
#include <Adafruit_SSD1306.h>

#ifndef _OUT_HPP_
#define _OUT_HPP_

class Out {

public:
     Out();

     void init();

     void clear();

     void cursor(u16 y);
     void cursor(u16 x, u16 y);

     void font(font_t);

     void println(const char*);
     void println(u8);
     void print(const char*);
     void print(u8);

     void println_w_yo(const char*);

     void display();

private:
     Adafruit_SSD1306 oled;
};
#endif // _OUT_HPP_
