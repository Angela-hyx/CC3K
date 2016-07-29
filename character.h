
#ifndef character_h
#define character_h
#include <string>
#include <iostream>

class Character{
private:
    int HP;
    int Atk;
    int Def;
    char sym;
    std::string race;
    int row;
    int col;
    int maxHP;
public:
    Character(int HP,int Atk,int Def,char sym,std::string race,int row,int col,int maxHP);
    virtual ~Character() = 0;
    int getHP();
    int getAtk();
    int getDef();
    char getSym();
    int getRow();
    int getCol();
    int getmaxHP();
    std::string getRace();
    
    void setHP(int amt);
    void addHP(int amt);
    void setAtk(int amt);
    void addAtk(int amt);
    void setDef(int amt);
    void addDef(int amt);
    void setRow(int amt);
    void addRow(int amt);
    void setCol(int amt);
    void addCol(int amt);
};


#endif /* character_h */







