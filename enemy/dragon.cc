
#include "dragon.h"
#include "../item/gold.h"
#include <memory>
#include <utility>
using namespace std;

Dragon::Dragon(int row,int col,shared_ptr<Gold> dragon_hoard):Enemy{150,20,20,'D',"Dragon",row,col,150,0,false},dragon_hoard{dragon_hoard}{}

Dragon::~Dragon(){}

void Dragon::setHoardPickable() {
    dragon_hoard->setPickable(true);
}

shared_ptr<Gold> Dragon::getHoard() {
    return dragon_hoard;
}



