
#ifndef dragon_h
#define dragon_h

#include "../enemy.h"
#include <memory>

class Dragon: public Enemy{
    std::shared_ptr<Gold> dragon_hoard;
public:
    std::shared_ptr<Gold> getHoard() override;
    void setHoardPickable() override;
    Dragon(int row,int col,std::shared_ptr<Gold> dragon_hoard);
    ~Dragon();
};

#endif /* dragon_h */



