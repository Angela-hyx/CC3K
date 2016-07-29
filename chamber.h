#ifndef chamber_h
#define chamber_h

#include <vector>

#include "floor.h"

class Chamber{
    int id;
    int topRow;
    int topCol;
    int rowLen;
    int colLen;
    std::vector<std::vector<char>>& theDisplay;
    
public:
    
    Chamber(int id, std::vector<std::vector<char>>& theDisplay);
    ~Chamber();
    
    int getid();
    int gettopRow();
    int gettopCol();
    int getrowLen();
    int getcolLen();
    
    bool isValidTile(const int row,const int col);
    std::vector<int> generatePos(const char symbol);
    bool withinRange(const int row, const int col);

};

#endif







