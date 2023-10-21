//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Executor.hpp"
#include <Arduino.h>

Executor::Executor(Out& o, Buttons& b):
     out(o),
     btns(b)
{
     return;
}

void Executor::go(MenuItem::item_t item) {
     if (item == MenuItem::_about) return about();
     bus_size = BUS_SIZE;
     if (item != MenuItem::_256k) --bus_size;
     //
     // TODO
     //
     btns.wait_ok();
}

void Executor::about() {
     out.clear();
     out.font(Small);
     out.cursor(0);
     out.println(NAME);
     out.println(VERSION);
     out.display();
     btns.wait_ok();
}

void Executor::init() {
     for (u8 i = 0; i < BUS_SIZE; i++)
	  pinMode(a_bus[i], OUTPUT);

     pinMode(CAS, OUTPUT);
     pinMode(RAS, OUTPUT);
     pinMode(WE, OUTPUT);
     pinMode(DI, OUTPUT);
     pinMode(M_START, INPUT);
     pinMode(DO, INPUT);

     digitalWrite(WE, HIGH);
     digitalWrite(RAS, HIGH);
     digitalWrite(CAS, HIGH);
}
