#ifndef _GOLD_H_
#define _GOLD_H_
#include "../item.h"

#include <string>

class Gold: public Item {
   int quantity;
   bool pickable;
  public:
   Gold(int row, int col, std::string type, char symbol, int quantity, bool pickable);
    ~Gold();
    //Gold(Gold&&) = default;
    //Gold& operator=(Gold&&) = default;
   int getQuantity();
   bool isPickable();
   void setQuantity(int num);
   void setPickable(bool pick);
};

#endif



