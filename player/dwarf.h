
#ifndef dwarf_h
#define dwarf_h

#include "../player.h"

class Dwarf: public Player{
public:
    Dwarf(int row,int col,int chamberId);
    ~Dwarf();
};

#endif 



