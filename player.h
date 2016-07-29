#ifndef player_h
#define player_h

#include <iostream>
#include <memory>

#include "character.h"
#include "item/potion.h"
#include "item/gold.h"
#include <string>

class Enemy;
class Player: public Character{
    int goldamt;
    int chamberId; //see which chamber is the player in(for initializing stairs)
    std::string action; // store in this field for each player's action
    const int deAtk,deDef;
  public:
    Player(int HP,int Atk,int Def,std::string race,int row,int col,int maxHP,int chamberId,const int deAtk,const int deDef);
    virtual ~Player();
    
    int getAmt();
    int getChamberId();
    int getdeAtk();
    int getdeDef();
    std::string getAction();
    
    void setChamberId(const int i);
    void setAction(const std::string a);
    void addAction(const std::string a);
    
    void addGold(int amount);
    
    void attack(std::shared_ptr<Enemy> e);
    void movePos(std::string direction);
    
    void usePotion(std::shared_ptr<Potion> p);
    void useGold(std::shared_ptr<Gold> g);
};

#endif 




