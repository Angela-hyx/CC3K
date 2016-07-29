#ifndef _ITEMS_H_
#define _ITEMS_H_

#include <string>

class Item {
  protected:
   int row;
   int col;
   std::string type;
   char symbol;
  public:
   Item(int row, int col, std::string type, char symbol);
   virtual ~Item() = 0;
   virtual int getRow();
   virtual int getCol();
   virtual void setRow(int num);
   virtual void setCol(int num);
   virtual std::string getType();
   virtual char getSymbol();
};

#endif






