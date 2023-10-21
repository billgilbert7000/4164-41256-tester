//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Out.hpp"
#include "MenuItem.hpp"

#ifndef _MENU_DRAWER_HPP_
#define _MENU_DRAWER_HPP_

class MenuDrawer {

public:
     MenuDrawer(Out&);

     void draw(MenuItem::item_t) const;

private:
     Out& o;
};
#endif // _MENU_DRAWER_HPP_
