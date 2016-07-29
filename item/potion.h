#ifndef _POTION_H_
#define _POTION_H_
#include "../item.h"

class Potion: public Item {
   int value;
  public:
   Potion(int row, int col, std::string type, char symbol, int value);
    ~Potion();
    //Potion(Potion&&) = default;
    //Potion& operator=(Potion&&) = default;
   int getvalue();
};

#endif



