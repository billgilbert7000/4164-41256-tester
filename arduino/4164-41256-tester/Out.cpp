//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Out.hpp"
#include "fonts/FreeSans9.h"
#include <Adafruit_GFX.h>

extern char *utf8rus2(char *source);

Out::Out():
     oled(Adafruit_SSD1306(128, 32, &Wire))
{
     return;
}

void Out::init() {
     oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
     delay(1000);
     oled.clearDisplay();
     oled.display();
     oled.setTextSize(1);
     oled.setTextColor(WHITE);
     oled.setFont(&FreeSans9pt8b);
}

void Out::font(font_t f) {
     if (f == Regular)
	  oled.setFont(&FreeSans9pt8b);
     else
	  oled.setFont();
}

void Out::clear() {
     oled.clearDisplay();
}

void Out::cursor(u16 y) {
     oled.setCursor(0, y);
}

void Out::cursor(u16 x, u16 y) {
     oled.setCursor(x, y);
}

void Out::display() {
     oled.display();
}

void Out::println_w_yo(const char* s) {
     oled.println(utf8rus2(s));
}

void Out::print(const char* s) {
     oled.print(s);
}

void Out::println(u8 n) {
     oled.println(n);
}

void Out::println(const char* n) {
     oled.println(n);
}
