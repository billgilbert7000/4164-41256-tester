//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Types.hpp"

#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

class Button {

public:
     enum status_t {
	  None,
	  Press,
	  Release,
     };

     enum type_t {
	  Ok,
	  Select,
     };

public:
     Button(type_t, u8);

     status_t status();
     type_t get_type() const;

private:
     type_t type;
     u8 pin;
     u8 st;
};
#endif // _BUTTON_HPP_
