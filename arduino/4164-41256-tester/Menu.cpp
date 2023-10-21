//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Menu.hpp"

Menu::Menu():
     pos(0),
     max(5)
{
     return;
}

u8 Menu::get() const {
     return pos;
}

void Menu::toggle() {
     ++pos;
     if (pos == max) pos = 0;
}
