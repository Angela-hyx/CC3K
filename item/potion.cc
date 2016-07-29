#include <iostream>
#include <string>

#include "potion.h"
using namespace std;

Potion::Potion(int row, int col, string type, char symbol, int value):
  Item{row, col, type, symbol}, value{value} {}

Potion::~Potion() {}

int Potion::getvalue() {return value;}




