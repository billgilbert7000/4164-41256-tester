//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Types.hpp"

#ifndef _MENU_HPP_
#define _MENU_HPP_

class Menu {

public:
     Menu();

     void toggle();

     u8 get() const;

private:
     u8 pos;
     u8 max;
};
#endif // _MENU_HPP_
