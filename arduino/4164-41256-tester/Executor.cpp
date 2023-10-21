//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Executor.hpp"
#include <Arduino.h>

Executor::Executor(Out& o):
     out(o)
{
     return;
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
