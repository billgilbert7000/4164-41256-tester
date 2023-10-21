//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Out.hpp"
#include "MenuItem.hpp"

#ifndef _EXECUTOR_HPP_
#define _EXECUTOR_HPP_

class Executor {

public:
     Executor(Out&);

     void go(MenuItem::item_t);
};
#endif // _EXECUTOR_HPP_
