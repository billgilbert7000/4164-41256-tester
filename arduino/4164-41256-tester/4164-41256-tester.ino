//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#include "Out.hpp"
#include "Congratulation.hpp"
#include "Types.hpp"
#include "Buttons.hpp"
#include "Menu.hpp"
#include "MenuDrawer.hpp"
#include "Executor.hpp"

Out out;
Congratulation<Out> cong(out);
Buttons btns;
Menu menu;
MenuDrawer menu_drawer(out);
Executor executor(out, btns);

void setup() {
     out.init();
		 executor.init();
     cong.display();
     out.clear();
     out.display();
     menu_drawer.draw(menu.get());
}

void handle_ok() {
     executor.go(menu.get());
		 menu_drawer.draw(menu.get());
}

void handle_select() {
     menu.toggle();
     menu_drawer.draw(menu.get());
}

void handle_buttons(Button* b) {
     switch (b->get_type()) {

     case Button::Ok:
					handle_ok();
					break;

     case Button::Select:
					handle_select();
					break;
     }
}

void loop() {
     Button* btn = btns.poll();
     if (btn != NULL) handle_buttons(btn);
     delay(100);
}
