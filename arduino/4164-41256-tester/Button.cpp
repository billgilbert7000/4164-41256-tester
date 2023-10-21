//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Button.hpp"
#include <Arduino.h>

Button::Button(type_t t, u8 p):
     type(t),
     pin(p),
     st(HIGH)
{
     pinMode(p, INPUT);
}

Button::status_t Button::status() {
     auto i = digitalRead(pin);

     if (i == st) return None;

     if (i == HIGH) {
	  if (st == LOW) {
	       st = i;
	       return Release;
	  }
     }

     st = i;
     return Press;
}

Button::type_t Button::get_type() const {
     return type;
}
