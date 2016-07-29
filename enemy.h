
#ifndef Enemy_h
#define Enemy_h

#include "character.h"
#include "item/gold.h"

#include <memory>
#include <iostream>
#include <string>

class Player;

class Enemy: public Character{
    int goldamt;
    bool ishostile; 
public:
    Enemy(int HP,int Atk,int Def,char sym,std::string race,int row,int col,int maxHP,int goldamt,bool ishostile);
    ~Enemy();
    
    int getamount();
    bool gethostile();
    void sethostile(); // call it for dragon and merchant
    virtual void setHoardPickable();
    virtual std::shared_ptr<Gold> getHoard();
    
    void attack(std::shared_ptr<Player> p);
    void moveEnemy(); // move randomly
    
};

#endif /* Enemy_h */




