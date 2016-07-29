#include "player.h"
#include "enemy.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <cmath>

using namespace std;

Player::Player(int HP,int Atk,int Def,std::string race,int row,int col,int maxHP,int chamberId,const int deAtk,const int deDef):Character{HP,Atk,Def,'@',race,row,col,maxHP},goldamt{0},chamberId{chamberId},deAtk{deAtk},deDef{deDef}{
    action="Player character has spawned.";
}

Player::~Player() {}

int Player::getAmt(){
    return goldamt;
}


int Player::getChamberId(){
    return chamberId;
}

string Player::getAction(){
    return action;
}

int Player::getdeAtk(){
	return deAtk;
}

int Player::getdeDef(){
	return deDef;
}

void Player::setChamberId(const int i){
    chamberId = i;
}

void Player::setAction(const string a){
    action = a;
}

void Player::addAction(const std::string a){
    action += (" " + a);
}

void Player::addGold(int amount){
    goldamt += amount;
}

void Player::attack(shared_ptr <Enemy> e){ // Character *e is an Enemy ptr
    int Damage = (int) ceil((100*getAtk())/(100+e->getDef())); 
    ostringstream ss,s1;
    ss << Damage; //
    int newHP = e->getHP() - Damage;
    if(newHP > 0){
        e->setHP(newHP);
	s1 << e->getHP(); //
        action = "PC deals " + ss.str() +" damage to " + e->getRace() + " ("+ s1.str()+" HP).";
    }
    else{ // new
        e->setHP(0);
        action = e->getRace() + " is slain.";
        goldamt += e->getamount();
	if (e->getRace() == "Dragon") {
	  e->setHoardPickable();
	 }
    }

    if (e->getRace() == "Merchant") {
      e->sethostile();
    }
}

/* void Player::beStuckBy(std::unique_ptr<Enemy> e){
    unique_ptr<Player> theplayer = static_cast<unique_ptr<Player>> (move(this));
    e->attack(theplayer);
} */

void Player::movePos(string direction){
    if(direction == "no"){
        addRow(-1);
        action = "PC moves to the North.";
    }
    else if(direction == "so"){
        addRow(1);
        action = "PC moves to the South.";
    }
    else if(direction == "ea"){
        addCol(1);
        action = "PC moves to the East.";
    }
    else if(direction == "we"){
        addCol(-1);
        action = "PC moves to the West.";
    }
    else if(direction == "ne"){
        addRow(-1);
        addCol(1);
        action = "PC moves to the NorthEast.";
    }
    else if(direction == "se"){
        addRow(1);
        addCol(1);
        action = "PC moves to the SouthEast.";
    }
    else if(direction == "sw"){
        addRow(1);
        addCol(-1);
        action = "PC moves to the SouthWest.";
    }
    else if(direction == "nw"){
        addRow(-1);
        addCol(-1);
        action = "PC moves to the NorthWest.";
        
        
    }
}


void Player::usePotion(shared_ptr <Potion> p){
    int quantity=p->getvalue();
    if(getRace()=="Elves"){
        if(quantity<0){
            quantity*=-1; // negative becomes positive
        }
    }
    if(p->getType()=="RH"){
        if(getHP()+quantity < getmaxHP()){ // we check the max HP
            addHP(quantity);
            action = "PC uses RH.";
        }
        else {
            action = "Ops! You exceed your max HP. Can't use RH.";
        }
    }
    else if(p->getType()=="BA"){
        addAtk(quantity);
        action = "PC uses BA.";
    }
    else if(p->getType()=="BD"){
        addDef(quantity);
        action = "PC uses BD.";
    }
    else if(p->getType()=="PH"){
        if(getHP()+quantity >= 0){
            addHP(quantity);
            action = "PC uses PH.";
        }
        else{ // then we can't use "PH"
            action="Ops! You are below 0. Can't use PH.";
        }
    }
    else if(p->getType()=="WA"){
        if(getAtk()+quantity >= 0){  //we check the min Atk
            addAtk(quantity);
            action = "PC uses WA.";
        }
        else{ // then we can't use "WA"
            action="Ops! You are below 0. Can't use WA.";
        }
    }
    else if(p->getType()=="WD"){
        if(getDef()+quantity >= 0){ // we check the min Def
            addDef(quantity);
            action = "PC uses WD.";
        }
        else{ // then we can't use "WD"
            action="Ops! You are below 0. Can't use WD.";
        }
    }
}

void Player::useGold(shared_ptr<Gold> g){ // no merchant hoard
    if(g->isPickable()){
    goldamt += g->getQuantity();
    }
    if(g->getType()=="normal"){
        action = "PC gets a normal gold(1).";
    }
    else if(g->getType()=="small"){
        action = "PC gets a small gold(2).";
    }
    else if(g->getType()=="dragon hoard"){
        action = "PC gets a dragon hoard(6).";
    }
    
}






