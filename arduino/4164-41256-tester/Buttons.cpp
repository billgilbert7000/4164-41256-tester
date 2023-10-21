//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Buttons.hpp"
#include <stddef.h>

Button* Buttons::poll() {
     if (sel.status() == Button::Release) return &sel;
     if (ok.status() == Button::Release) return &ok;
     return NULL;
}
