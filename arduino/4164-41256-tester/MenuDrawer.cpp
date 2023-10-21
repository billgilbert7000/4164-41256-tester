//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "MenuDrawer.hpp"

MenuDrawer::MenuDrawer(Out& _o):
     o(_o)
{
     return;
}

void MenuDrawer::draw(MenuItem::item_t i) const {
     o.clear();
     o.font(Regular);
     o.cursor(15);
     o.print("> ");

     switch (i) {

     case MenuItem::_64k:
	  o.print("64k");
	  break;

     case MenuItem::_256k:
	  o.print("256k");
	  break;

     case MenuItem::_32k_low:
	  o.print("32k low");
	  break;

     case MenuItem::_32k_high:
	  o.print("32k high");
	  break;

     case MenuItem::_about:
	  o.print("About");
	  break;
     }

     o.display();
}
