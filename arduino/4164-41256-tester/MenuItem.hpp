//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#ifndef _MENU_ITEM_HPP_
#define _MENU_ITEM_HPP_

class MenuItem {

public:
     enum item_t {
	  _64k      = 0,
	  _256k     = 1,
	  _32k_low  = 2,
	  _32k_high = 3,
	  _about    = 4,
     };
};
#endif // _MENU_ITEM_HPP_
