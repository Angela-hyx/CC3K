
#ifndef human_h
#define human_h

#include "../player.h"

class Human: public Player{
public:
    Human(int row,int col,int chamberId) ;
    ~Human();
};

#endif 



