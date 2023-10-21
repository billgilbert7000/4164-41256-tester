//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Out.hpp"
#include "Buttons.hpp"
#include "MenuItem.hpp"
#include "Config.hpp"

#ifndef _EXECUTOR_HPP_
#define _EXECUTOR_HPP_

class Executor {

public:
     Executor(Out&, Buttons&);

     void init();
     void go(MenuItem::item_t);

private:
     Out& out;
     Buttons& btns;

private:
     u8 bus_size;

     static const u8 BUS_SIZE = 9;
      u8 a_bus[BUS_SIZE] = {
	  XA0, XA1, XA2, XA3, XA4, XA5, XA6, XA7, XA8,
     };

     u8 mode;
     bool is_error;

private:
     void set_mode(MenuItem::item_t);
     void about();
     void test();
     void init_dram();
     void fillx(int);
     void write_address(unsigned int, unsigned int, int);
     int read_address(unsigned int, unsigned int);
     void set_bus(unsigned int);
     void error(int, int);
};
#endif // _EXECUTOR_HPP_
