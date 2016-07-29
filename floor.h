#ifndef floor_h
#define floor_h

#include <iostream>
#include <vector>
#include <memory>

class Player;
class Enemy;
class Chamber;
class Potion;
class Gold;



class Floor {
    int curFloor;
    bool Won;
    bool DLC = false;
    std::shared_ptr<Player> thePlayer;
    std::vector<std::vector<char>> theDisplay;
    std::vector <std::shared_ptr<Enemy>> theEnemy;
    std::vector <std::shared_ptr<Chamber>> theChamber;
    std::vector <std::shared_ptr<Potion>> thePotion;
    std::vector<std::shared_ptr<Gold>> theGold;
    int numRow;
    int numCol;
    char preTile; //the tile the Player stand on last time
    
    public:
    Floor(std::string filename = "map.txt");
    ~Floor();
    void setDLC(bool dlc);
    bool isWon();
    void setWon();
    
    int getCurFloor();
    void nextFloor();
    int getnumRow();
    int getnumCol();
    int getgoldAmt();
    
    virtual void setPlayer(std::shared_ptr<Player> p);
    void setFloor();
    void readFloor(std::string filename);    
    void clearFloor();
    
    void showStair();
    void generateChamber();
    void generateEnemy();
    void generatePlayer();
    void generateGold();
    void generatePotion();
    void printFloor();
    
    int findPotion(const int row, const int col);
    int findEnemy(const int row, const int col);
    void consumePotion(std::string direction);
    
    void movePlayer(std::string direction);
    bool isValid(std::string direction);
    bool isPickableGold(std::string direction);
    bool checkPoint(std::string direction, char c);
    void setCharAt(const int row, const int col, const char symbol);
    char getCharAt(const int row, const int col);
    std::vector<int> nextStep(std::string direction);
    
    void enemyMoveAndAttack(); //this one changed from moveEnemy(), autoAttack() and enemyAction()!!! combines move and attack together
    void playerAttack(std::string direction);
    bool checkdie();
};

#endif





