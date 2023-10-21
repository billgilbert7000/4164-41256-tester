//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "OkButton.hpp"
#include "SelButton.hpp"

#ifndef _BUTTONS_HPP_
#define _BUTTONS_HPP_

class Buttons {

public:
     Button* poll();

     void wait_ok();

private:
     SelButton sel;
     OkButton ok;
};
#endif // _BUTTONS_HPP_
