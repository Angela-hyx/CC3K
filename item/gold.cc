#include <iostream>
#include <string>

#include "gold.h"
using namespace std;

Gold::Gold(int row, int col, string type, char symbol, int quantity, bool pickable):
  Item{row, col, type, symbol}, quantity{quantity}, pickable{pickable} {}

Gold::~Gold() {}

int Gold::getQuantity() {return quantity;}

bool Gold::isPickable() {return pickable;}

void Gold::setQuantity(int num) {quantity = num;}

void Gold::setPickable(bool pick) {pickable = pick;}



