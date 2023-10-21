//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Out.hpp"
#include "MenuItem.hpp"
#include "Config.hpp"

#ifndef _EXECUTOR_HPP_
#define _EXECUTOR_HPP_

class Executor {

public:
     Executor(Out&);

     void init();
     void go(MenuItem::item_t);

private:
     Out& out;

private:
     static const u8 BUS_SIZE = 9;
      u8 a_bus[BUS_SIZE] = {
	  XA0, XA1, XA2, XA3, XA4, XA5, XA6, XA7, XA8,
     };
};
#endif // _EXECUTOR_HPP_
