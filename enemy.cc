
#include "enemy.h"
#include "player.h"
#include <memory>
#include <cstdlib>
#include <cmath>
#include <sstream>

using namespace std;


Enemy::Enemy(int HP,int Atk,int Def,char sym,std::string race,int row,int col,int maxHP,int goldamt,bool ishostile):Character{HP,Atk,Def,sym,race,row,col,maxHP},goldamt{goldamt},ishostile{ishostile}{}

Enemy::~Enemy(){}

int Enemy::getamount(){
    return goldamt;
}

bool Enemy::gethostile(){
    return ishostile;
}

void Enemy::sethostile(){
    ishostile=true;
}

void Enemy::attack(shared_ptr<Player> p){
    if(ishostile){ // if the Enemty is hostile
        int posibility = rand() % 2;
        if(p->getRace()=="Student" && getRace()=="Midterm"){ //!!!!!
            p->setHP(0); // students will immediately die when confront with midterm
            p->addAction("PC "+ p->getRace() + "fails the " + getRace());
        }
        if(posibility == 0){ // 0, then the enemy missed
            p->addAction(getRace() +" missed the target.");
            
        }
        else{ // posibility == 1;
            int Damage = (int) ceil((100 * getAtk())/(100 + p->getDef()));
            ostringstream ss;
            ss << Damage;
            int newHP = p->getHP()-Damage;
            if(newHP>0){
                p->setHP(newHP);
                p->addAction(getRace() +" deals " + ss.str() +" damage to PC."); 
            }
            else{
                p->setHP(0); // PC dies.???
            }
        }
    }
}

void Enemy::moveEnemy(){ // move randomly CHECK VALID!!! // enemy can stay the same
    int posibility = rand() % 9;
    if(posibility == 0){  //0 for north
        addRow(-1);
    }
    else if(posibility == 1){  //1 for south
        addRow(1);
    }
    else if(posibility == 2){  //2 for east
        addCol(1);
    }
    else if(posibility == 3){  //3 for west
        addCol(-1);
    }
    else if(posibility == 4){  //4 for northeast
        addRow(-1);
        addCol(1);
    }
    else if(posibility == 5){  //5 for southeast
        addRow(1);
        addCol(1);
    }
    else if(posibility == 6){  //6 for southwest
        addRow(1);
        addCol(-1);
    }
    else if(posibility == 7){  //7 for northwest
        addRow(-1);
        addCol(-1);
    }
    else {}  //(posibility == 8)  //8 for stay the same
}

void Enemy::setHoardPickable() {}

std::shared_ptr<Gold> Enemy::getHoard() {}
 































