#include <iostream>
#include <string>
#include "item.h"
using namespace std;

Item::Item(int row, int col, string type, char symbol):
  row{row}, col{col}, type{type}, symbol{symbol} {}

Item::~Item() {}

int Item::getRow() {return row;}

int Item::getCol() {return col;}

void Item::setRow(int num) {
  row = num;
}

void Item::setCol(int num) {
  col = num;
}

string Item::getType() {return type;}

char Item::getSymbol() {return symbol;}







