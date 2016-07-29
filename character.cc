
#include "character.h"
#include "item/gold.h"
#include "item/potion.h"
using namespace std;

Character::Character(int HP,int Atk,int Def,char sym,std::string race,int row,int col,int maxHP):HP{HP},Atk{Atk},Def{Def},sym{sym},race{race},row{row},col{col},maxHP{maxHP}{}

Character::~Character(){}

int Character::getHP(){
    return HP;
}

int Character::getAtk(){
    return Atk;
}

int Character::getDef(){
    return Def;
}

char Character::getSym(){
    return sym;
}

int Character::getCol(){
    return col;
}

int Character::getRow(){
    return row;
}

int Character::getmaxHP(){
    return maxHP;
}

string Character::getRace(){
    return race;
}

void Character::setHP(int amt){
    HP=amt;
}

void Character::addHP(int amt){ 
    HP+=amt;
}

void Character::setAtk(int amt){
    Atk=amt;
}

void Character::addAtk(int amt){
    Atk+=amt;
}

void Character::setDef(int amt){
    Def=amt;
}

void Character::addDef(int amt){
    Def+=amt;
}

void Character::setRow(int amt){
    row=amt;
}
void Character::addRow(int amt){
    row+=amt;
}
void Character::setCol(int amt){
    col=amt;
}
void Character::addCol(int amt){
    col+=amt;
}













