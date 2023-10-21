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
     set_mode(item);
     is_error = false;
     test();
     btns.wait_ok();
}

void Executor::test() {
     init_dram();

     out.clear();
     out.cursor(20);
     out.println("Тест № 1");
     out.display();

     noInterrupts();
     fillx(0);
     interrupts();
     //
     // TODO
     //
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

void Executor::init_dram() {
     _delay_us(250); // Initial DRAM startup delay 250us
     for (u8 i = 0; i < 8; i++) digitalWrite(a_bus[i], LOW);

     for (u8 i = 0; i < 8; i++)  {
	  digitalWrite(RAS, LOW);
	  digitalWrite(RAS, HIGH);
     }
}

void Executor::fillx(int v) {
     int r, c, g = 0;
     int nocol = 0;
     if (mode > 1) nocol = 1;
     v %= 1;
     for (c = 0; c < (1 << bus_size - nocol); c++) {
	  for (r = 0; r < (1 << bus_size); r++) {
	       write_address(r, c, v);
	       if (v != read_address(r, c)) {
		    error(r, c);
		    return;
	       }
	       v ^= 1;
	  }
	  g ^= 1;
     }
}

void Executor::error(int r, int c) {
     unsigned long a = ((unsigned long)c << bus_size) + r;
     String mhex = String(a, HEX);

     out.clear();
     out.font(Regular);
     out.cursor(15);
     out.print("Ошибка");
     out.font(Small);
     out.cursor(25);
     out.print(mhex.c_str());
     out.display();

     is_error = true;
     btns.wait_ok();
}
