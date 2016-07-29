
#ifndef student_h
#define student_h

#include "../player.h"
class Student: public Player{
public:
    Student(int row,int col,int chamberId);
    ~Student();
};

#endif /* student_h */



