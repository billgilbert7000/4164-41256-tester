//
// Copyright (c) 2023 Boris Popov <popov@whitekefir.ru>
//

#ifndef _CONGRATULATION_HPP_
#define _CONGRATULATION_HPP_

///////////////////////////////////////////////////////////////////
template<class O>
class Congratulation {

public:
     Congratulation(O&);

     void display();

private:
     O& o;

private:
     void _display();
};
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
template<class O>
Congratulation<O>::Congratulation(O& _o):
     o(_o)
{
     return;
}

template<class O>
void Congratulation<O>::display() {
     for (u8 i = 0; i < 3; i++) {
	  _display();
     }
     o.clear();
     o.display();
}

template<class O>
void Congratulation<O>::_display() {
     o.clear();
     o.font(Regular);

     o.cursor(20);
     o.print("Поздравляю");
     o.display();
     delay(750);

     o.clear();
     o.cursor(20);
     o.print("Протодеда");
     o.display();
     delay(750);

     o.clear();
     o.cursor(20);
     o.print("@Mikkaa_A!");
     o.display();
     delay(750);

     o.clear();
     o.cursor(20);
     o.print("Желаю");
     o.display();
     delay(750);

     o.clear();
     o.cursor(20);
     o.print("здоровья и");
     o.display();
     delay(750);

     o.clear();
     o.cursor(20);
     o.print("долгих лет!");
     o.display();
     delay(750);
}
///////////////////////////////////////////////////////////////////
#endif // _CONGRATULATION_HPP_
