#include "floor.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "character.h"
#include "chamber.h"
#include "enemy/dragon.h"
#include "enemy/goblin.h"
#include "enemy/vampire.h"
#include "enemy/merchant.h"
#include "enemy/phoenix.h"
#include "enemy/troll.h"
#include "enemy/werewolf.h"
#include "enemy/midterm.h"
#include "player/dwarf.h"
#include "player/elves.h"
#include "player/human.h"
#include "player/orc.h"
#include "player/student.h"
#include "item/gold.h"
#include "item/potion.h"

#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <utility>
#include <cstdlib>

	using namespace std;


	Floor::Floor(string filename):curFloor{1},Won{false},thePlayer{nullptr},numRow{25},numCol{79} {
	    ifstream file {filename};
	    string s;
	    while (getline(file, s)) {
		vector <char> row;
		int len = (int)s.length();
		for (int i = 0; i < len; ++i) {
		    row.emplace_back(s[i]);
		}
		theDisplay.emplace_back(row);
	    }
	    preTile = '.';
	}
	//used std::move for Player here because unique_ptr cannnot be copyed

	Floor::~Floor(){
		clearFloor();
}

void  Floor::setDLC(bool dlc) {
      DLC = dlc;
}

bool Floor::isWon(){
    return Won;
}

void Floor::setWon() {
    Won = true;
}

int Floor::getCurFloor() {
    return curFloor;
}

void Floor::nextFloor() {
    ++curFloor;
    ostringstream ss;
    ss << curFloor;
    thePlayer->setAction("Welcome to Floor " + ss.str() +"!");
}

int Floor::getnumRow() {
    return numRow;
}

int Floor::getnumCol() {
    return numCol;
}

int Floor::getgoldAmt() {
    return thePlayer->getAmt();
}

 void Floor::setPlayer(std::shared_ptr<Player> p) {
    thePlayer = p;
}

void Floor::setFloor(){
    generateChamber();
    generatePlayer(); // all the generate function should also replace the corresponding char in vec
    showStair();
    generatePotion();
    generateGold();
    generateEnemy();
}

void Floor::readFloor(string filename) {
	ifstream file {filename};
	string s;
	vector<vector<int>> dragonPos;
	vector<vector<int>> dGoldPos;
        generateChamber();
        bool goTo = false;
       for (int start = 25*(curFloor-1); start < 25*curFloor; ++start) {
	       int count = 0;
	       while (start > count && goTo == false) {
		       ++count;
	       getline(file, s);
	       }
	       goTo = true;
	       getline(file, s);

	         vector <char> row;    
		 int len = (int)s.length();
                   for (int i = 0; i < len; ++i) {
			   if (s[i]== '0') {
				   row.emplace_back('P');
				   auto newPotion = make_shared<Potion> (start-25*(curFloor-1), i, "RH", 'P', 10);
				         thePotion.emplace_back(newPotion);
			   } 
			   else if (s[i]== '1') {
				    auto newPotion = make_shared<Potion> (start-25*(curFloor-1), i,"BA", 'P', 5);
				          thePotion.emplace_back(newPotion);
				   row.emplace_back('P');
	                  }
			   else if (s[i]== '2') {
				   auto newPotion = make_shared<Potion> (start-25*(curFloor-1), i,"BD", 'P', 5);
				           thePotion.emplace_back(newPotion);
				   row.emplace_back('P');
				                              } 
			   else if (s[i]== '3') {
				   auto newPotion = make_shared<Potion> (start-25*(curFloor-1), i,"PH", 'P', -10);
				           thePotion.emplace_back(newPotion);
				   row.emplace_back('P');
				                              } 
			   else if (s[i]== '4') {
				   auto newPotion = make_shared<Potion> (start-25*(curFloor-1), i,"WA", 'P', -5);
				           thePotion.emplace_back(newPotion);
				   row.emplace_back('P');
				                              } 
			   else if (s[i]== '5') {
				   auto newPotion = make_shared<Potion> (start-25*(curFloor-1), i,"WD", 'P', -5);
				           thePotion.emplace_back(newPotion);
				   row.emplace_back('P');	            
			   } 
			   else if (s[i] =='6') {
				   auto newGold = make_shared<Gold> (start-25*(curFloor-1), i, "normal", 'G', 1, true);
				           theGold.emplace_back(newGold);
				   row.emplace_back('G');

				                              } 
			   else if (s[i]== '7') {
				   auto newGold = make_shared<Gold> (start-25*(curFloor-1), i,"small", 'G', 2, true);
				           theGold.emplace_back(newGold);
				   row.emplace_back('G');

				                              } 
			   else if (s[i]== '9') {
				   vector<int> pos;
				   pos.emplace_back(start-25*(curFloor-1));
				   pos.emplace_back(i);
				   dGoldPos.emplace_back(pos);
				   row.emplace_back('G');
				                              } 
			  else  if (s[i]== '@') { 
				  for (int j = 0; j < 5; ++j) {
					  bool within = theChamber[j]->withinRange(start-25*(curFloor-1), i);
					  if (within) {
						  thePlayer->setChamberId(j+1);
				  }
			}
				          thePlayer->setRow(start-25*(curFloor-1));
					      thePlayer->setCol(i);
				   row.emplace_back('@');
				                              } 
			   else  if (s[i]== 'V') {
				   auto newEnemy = make_shared<Vampire>(start-25*(curFloor-1), i);
				         theEnemy.emplace_back(newEnemy);
				   row.emplace_back('V');
				                              } 
			   else if (s[i]== 'W') {
				   auto newEnemy = make_shared<Werewolf> (start-25*(curFloor-1), i);
				           theEnemy.emplace_back(newEnemy);
				   row.emplace_back('W');
				                              } 
			   else if (s[i]== 'N') {
				   auto newEnemy = make_shared<Goblin> (start-25*(curFloor-1), i);
				          theEnemy.emplace_back(newEnemy);
				   row.emplace_back('N');
				                              } 
			   else if (s[i]== 'M') {
				   auto newEnemy = make_shared<Merchant> (start-25*(curFloor-1), i);
				          theEnemy.emplace_back(newEnemy);
				   row.emplace_back('M');
				                              } 
			   else if (s[i]== 'T') {
				   auto newEnemy = make_shared<Troll> (start-25*(curFloor-1), i);
				         theEnemy.emplace_back(newEnemy);
				   row.emplace_back('T');

				                              } 
			   else if (s[i]== 'X') {
				   auto newEnemy = make_shared<Phoenix> (start-25*(curFloor-1), i);
				        theEnemy.emplace_back(newEnemy);
				   row.emplace_back('X');
				                              }
			   else if (s[i]== 'E') {
				   auto newEnemy = make_shared<Midterm> (start-25*(curFloor-1), i);                                                      theEnemy.emplace_back(newEnemy);
													                                         row.emplace_back('E');
														                                                               } 
			   else if (s[i]== 'D') {
				   vector<int> pos;
				   pos.emplace_back(start-25*(curFloor-1));
                                   pos.emplace_back(i);					 
				   dragonPos.emplace_back(pos);
				   row.emplace_back('D');
				                              }
			   else {
				   row.emplace_back(s[i]);
			   }
		   }
		 theDisplay.erase(theDisplay.begin());
		 theDisplay.emplace_back(row);
         }
		   for (int i = 0; i < (int)dragonPos.size(); ++i) {
			   auto newGold = make_shared<Gold> (dGoldPos[i].front(), dGoldPos[i].back(), "dragon hoard", 'G', 6, false);
			           theGold.emplace_back(newGold);
		           auto newEnemy = make_shared<Dragon> (dragonPos[i].front(), dragonPos[i].back(), newGold);
			               theEnemy.emplace_back(newEnemy);
		   }
}


void Floor::clearFloor() {
   // theDisplay.clear();
    while((int)theEnemy.size() > 0){
	    theDisplay[theEnemy[0]->getRow()][theEnemy[0]->getCol()] = '.';
	    theEnemy.erase(theEnemy.begin());
    }
    while((int)theChamber.size() > 0){
	    theChamber.erase(theChamber.begin());
    }
    while((int)thePotion.size() > 0){
	    theDisplay[thePotion[0]->getRow()][thePotion[0]->getCol()] = '.';
	    thePotion.erase(thePotion.begin());
    }
    while((int)theGold.size() > 0){
	    theDisplay[theGold[0]->getRow()][theGold[0]->getCol()] = '.';
	    theGold.erase(theGold.begin());
    }
    for(int i = 0; i < numRow; i++){ // clear stair
	    for(int j = 0; j < numCol ; ++j){
		    if(theDisplay[i][j] == '\\') {
			    theDisplay[i][j] = '.';
		    }
	    }
    }
    theDisplay[thePlayer->getRow()][thePlayer->getCol()] = '.';
    thePlayer->setAtk(thePlayer->getdeAtk());
    thePlayer->setDef(thePlayer->getdeDef());
   // theEnemy.clear();
   // theChamber.clear();
   // thePotion.clear();
   // theGold.clear();
}


void Floor::showStair() {
    int id = rand() % 5;
    while(id == thePlayer->getChamberId()) { 
        id = rand() % 5;
    }
    theChamber[id]->generatePos('\\');
}
                                
                                
void Floor::generateChamber() {
    for (int i = 1; i <= 5; ++i) {
        auto newChamber = make_shared <Chamber> (i, theDisplay);  //?????????
        theChamber.emplace_back(newChamber);
    }
}

void Floor::generatePlayer() {
    int id = rand() % 5; //
    thePlayer->setChamberId(id);
    vector<int> cor = theChamber[id]->generatePos('@');
    thePlayer->setRow(cor.front());
    thePlayer->setCol(cor.back());
    
}

void Floor::generateEnemy() {
    int dragonamt = 0;
    for (int i = 0; i < 10; ++i) {
        if (theGold[i]->getQuantity() == 6) {
            theGold[i]->setPickable(false);
            int currRow, currCol;
            ++dragonamt;

	    while (true) {
            currRow = theGold[i]->getRow();
            currCol = theGold[i]->getCol();

            int where = rand() % 8; //determine dragon's pos
            char currTile;
            
            if (where == 0) {
                --currRow;
                --currCol;
                currTile = getCharAt(currRow, currCol);
                if (currTile == '.') {
                    setCharAt(currRow, currCol, 'D');
		    break;
                }
            }
            if (where == 1) {
                --currRow;
                currTile = getCharAt(currRow, currCol);
                if (currTile == '.') {
                    setCharAt(currRow, currCol, 'D');
		    break;
                }
            }
            if (where == 2) {
                --currRow;
                ++currCol;
                currTile = getCharAt(currRow, currCol);
                if (currTile == '.') {
                    setCharAt(currRow, currCol, 'D');
		    break;
                }
            }
            if (where == 3) {
                --currCol;
                 currTile = getCharAt(currRow, currCol);
                if (currTile == '.') {
                    setCharAt(currRow, currCol, 'D');
		    break;
                }
            }
            if (where == 4) {
                ++currCol;
                currTile = getCharAt(currRow, currCol);
                if (currTile == '.') {
                    setCharAt(currRow, currCol, 'D');
		    break;
                }
            }
            if (where == 5) {
                ++currRow;
                --currCol;
                currTile = getCharAt(currRow, currCol);
                if (currTile == '.') {
                    setCharAt(currRow, currCol, 'D');
		    break;
                }
            }
            if (where == 6) {
                ++currRow;
                currTile = getCharAt(currRow, currCol);
                if (currTile == '.') {
                    setCharAt(currRow, currCol, 'D');
		    break;
                }
            }
            
            if (where == 7) {
                ++currRow;
                ++currCol;
                currTile = getCharAt(currRow, currCol);
                if (currTile == '.') {
                    setCharAt(currRow, currCol, 'D');
		    break;
                }
            }
	    }
            auto newDragon = make_shared<Dragon> (currRow, currCol, theGold[i]);
            theEnemy.emplace_back(newDragon);
        }
    }
    
  int restamt = 20 - dragonamt;
    
  for (int i = 0; i < restamt; ++i) {
    int id = rand() % 5; //
    int type = rand() % 18; // 0-3 reps Werewolf, 4-6 reps Vampire, 7-11 reps Goblin, 12-13 reps Troll, 14-15 reps Phoenix, 16-17 reps Merchant
    if (type == 0 || type == 1 || type == 2 || type == 3) {
     vector<int> cor = theChamber[id]->generatePos('W');
        auto newEnemy = make_shared<Werewolf> (cor.front(), cor.back());
        theEnemy.emplace_back(newEnemy);
        
    } else if (type == 4 || type == 5 || type == 6) {
      vector<int> cor = theChamber[id]->generatePos('V');
      auto newEnemy = make_shared<Vampire>(cor.front(), cor.back());
      theEnemy.emplace_back(newEnemy);
        
    } else if (type == 7 || type == 8 || type == 9 || type == 10 || type == 11) {
      vector<int> cor = theChamber[id]->generatePos('N');
      auto newEnemy = make_shared<Goblin> (cor.front(), cor.back());
       theEnemy.emplace_back(newEnemy);
        
    } else if (type == 12 || type == 13) {
      vector<int> cor = theChamber[id]->generatePos('T');
      auto newEnemy = make_shared<Troll> (cor.front(), cor.back());
       theEnemy.emplace_back(newEnemy);
        
    } else if (type == 14 || type == 15) {
      vector<int> cor = theChamber[id]->generatePos('X');
      auto newEnemy = make_shared<Phoenix> (cor.front(), cor.back());
        theEnemy.emplace_back(newEnemy);
        
    } else {
      vector<int> cor = theChamber[id]->generatePos('M');
      auto newEnemy = make_shared<Merchant> (cor.front(), cor.back());
        theEnemy.emplace_back(newEnemy);
    }
  }
  if (DLC) {
    int id = rand() % 5; // generate one midterm !!!!!!!!!!!
    vector<int> cor = theChamber[id]->generatePos('E');
    auto newEnemy = make_shared<Midterm>(cor.front(),cor.back());
    theEnemy.emplace_back(newEnemy);
  }
}



void Floor::generateGold() {
  int id,type;
  for (int i = 0; i < 10; i++) {
    id = rand() % 5; //
    vector<int> cor = theChamber[id]->generatePos('G');
    type = rand() % 8; // 0-4 reps normal, 5-6 reps small, 7 reps dragon gold
    if (type == 0 || type == 1 || type == 2 || type == 3 || type == 4) {
        auto newGold = make_shared<Gold> (cor.front(), cor.back(), "normal", 'G', 1, true);
        theGold.emplace_back(newGold);
    } else if (type == 5 || type == 6) {
      auto newGold = make_shared<Gold> (cor.front(), cor.back(),"small", 'G', 2, true);
        theGold.emplace_back(newGold);
    } else {
      auto newGold = make_shared<Gold> (cor.front(), cor.back(), "dragon hoard", 'G', 6, false);
        theGold.emplace_back(newGold);
    }
  }
}


void Floor::generatePotion() {
  int id,type;
	for (int i = 0; i < 10; i++) {
    id = rand() % 5;//
    vector<int> cor = theChamber[id]->generatePos('P');
    type = rand() % 6; // 0 reps RH, 1 reps BA, 2 reps BD, 3 reps PH, 4 reps WA, 5 reps WD
    if (type == 0) {
      auto newPotion = make_shared<Potion> (cor.front(), cor.back(),"RH", 'P', 10);
      thePotion.emplace_back(newPotion);
    } else if (type == 1) {
      auto newPotion = make_shared<Potion> (cor.front(), cor.back(),"BA", 'P', 5);
      thePotion.emplace_back(newPotion);
    } else if (type == 2) {
      auto newPotion = make_shared<Potion> (cor.front(), cor.back(),"BD", 'P', 5);
        thePotion.emplace_back(newPotion);
    } else if (type == 3) {
      auto newPotion = make_shared<Potion> (cor.front(), cor.back(),"PH", 'P', -10);
        thePotion.emplace_back(newPotion);
    } else if (type == 4) {
      auto newPotion = make_shared<Potion> (cor.front(), cor.back(),"WA", 'P', -5);
        thePotion.emplace_back(newPotion);
    } else {
      auto newPotion = make_shared<Potion> (cor.front(), cor.back(),"WD", 'P', -5);
        thePotion.emplace_back(newPotion);
    }
  }

}

void Floor::printFloor(){
    for (int i = 0; i < numRow; ++i) {
        for (int j = 0; j < numCol; ++j) {
	    if(theDisplay[i][j]=='G'){
		    cout << "\033[1;33m";
		    cout << theDisplay[i][j];
		    cout << "\033[0m";
	    }
	    else if(theDisplay[i][j]=='P'){
		    cout << "\033[1;32m";
		    cout << theDisplay[i][j];
		    cout << "\033[0m";
	    }
	    else if(theDisplay[i][j]=='@'||theDisplay[i][j]=='\\'){
		    cout << "\033[1;31m";
		    cout << theDisplay[i][j];
		    cout << "\033[0m";
	    }
	    else if(theDisplay[i][j]=='M'||theDisplay[i][j]=='V'||theDisplay[i][j]=='W'||theDisplay[i][j]=='D'||theDisplay[i][j]=='T'||theDisplay[i][j]=='N'||theDisplay[i][j]=='X'||theDisplay[i][j]=='E'){
		    cout << "\033[34m"; ///////!!!!!!!!
		    cout << theDisplay[i][j];
		    cout << "\033[0m";
	    }
	    else if(theDisplay[i][j]=='#'||theDisplay[i][j]=='+'||theDisplay[i][j]=='-'||theDisplay[i][j]=='|'){
		    cout << "\033[1;35m";
		    cout << theDisplay[i][j];
		    cout << "\033[0m";
	    }
	    else {
		    cout << "\033[1;37m";
		    cout << theDisplay[i][j];
		    cout << "\033[0m";
	    }
        }
        cout << "\n\033[0m";
    }
   /* if(thePlayer->getRace()=="Dwarf"){
      thePlayer->setAmt(thePlayer->getAmt() * 2);
    }
    if(thePlayer->getRace()=="Orc"){
      thePlayer->setAmt(thePlayer->getAmt() / 2);
    }
    */
    cout << "Race: " << thePlayer->getRace() << " Gold: " << thePlayer->getAmt();
    for (int i = 0; i < 50; ++i) {
        cout << " ";
    }
    cout << "Floor " << curFloor<<endl;
    cout << "HP: " << thePlayer->getHP() << endl;
    cout << "Atk: " << thePlayer->getAtk() << endl;
    cout << "Def: " << thePlayer->getDef() << endl;
    cout << "Action: " << thePlayer->getAction() << endl; 
}


int Floor::findPotion(const int row, const int col) {
  for (int i = 0; i < (int)thePotion.size(); ++i) {
    if (thePotion[i]->getRow() == row && thePotion[i]->getCol() == col) return i;
  }
    return -1; // it should never return -1
}

int Floor::findEnemy(const int row, const int col) {
    for (int i = 0; i < (int)theEnemy.size(); ++i) {
        if (theEnemy[i]->getRow() == row && theEnemy[i]->getCol() == col) return i;
    }
    return -1; // it should never return -1
}


void Floor::consumePotion(string direction) {
    vector<int> pos = nextStep(direction);
    int ind = findPotion(pos.front(), pos.back());
    thePlayer->usePotion(thePotion[ind]);  //REMEMBER TO CHECK
    thePotion.erase(thePotion.begin()+ind);
    theDisplay[pos.front()][pos.back()] = '.';
}

void Floor::movePlayer(string direction){
    int prow = thePlayer->getRow(); //current row of player
    int pcol = thePlayer->getCol(); //current col of player
    vector<int> prePos = nextStep(direction);
    char temp = theDisplay[prePos.front()][prePos.back()]; // next char
    if (temp == 'G') {  // next step is Gold
      int ind;
      for (ind = 0; ind < (int)theGold.size(); ++ind) {
	      if (theGold[ind]->getRow() == prePos.front() && theGold[ind]->getCol() == prePos.back()){
		      break;
	      }
      }
      if(theGold[ind]->isPickable()){  // the gold is not dragon hoard or it's a dragon hoard(dragon is dead now)
	      thePlayer->useGold(theGold[ind]);
	      theGold.erase(theGold.begin()+ind);
	      temp = '.';
      }
      else{
	      cout<<"The gold is guarded by the Dragon. You can't pick it." << endl; 
      }
    }
    
    theDisplay[prow][pcol] = preTile;
    thePlayer->movePos(direction);
    theDisplay[thePlayer->getRow()][thePlayer->getCol()] = '@';
    preTile = temp;
}

bool Floor::isValid(string direction){
    return(checkPoint(direction,'.')||checkPoint(direction, '+')
           ||checkPoint(direction, '#')||( checkPoint(direction, 'G') && isPickableGold(direction))); // only include pickable gold
}

bool Floor::isPickableGold(string direction){ // check if the next gold is pickable
	vector <int> ns = nextStep(direction);
	int i;
	for (i = 0; i < (int)theGold.size(); i++) {
		if (theGold[i]->getRow() == ns.front() && theGold[i]->getCol() == ns.back()) {
			break;
		}
	}
	return theGold[i]->isPickable();
}

bool Floor::checkPoint(string direction, char c) {
    vector<int> pos = nextStep(direction);
  if (c == theDisplay[pos.front()][pos.back()]) return true;
  return false;
}

void Floor::setCharAt(const int row, const int col, const char symbol){
    theDisplay[row][col]=symbol;
}

char Floor::getCharAt(const int row, const int col){
    return theDisplay[row][col];
}

vector<int> Floor::nextStep(string direction) { //I AM A HELPER
    int prow = thePlayer->getRow();
    int pcol = thePlayer->getCol();
    vector<int> pos;
    if (direction == "no") {
        --prow;
    } else if (direction == "so") {
        ++prow;
    } else if (direction == "ea") {
        ++pcol;
    } else if (direction == "we") {
        --pcol;
    } else if (direction == "ne") {
        --prow;
        ++pcol;
    } else if (direction == "se") {
        ++prow;
        ++pcol;
    } else if (direction == "sw") {
        ++prow;
        --pcol;
    } else{
        --prow;
        --pcol;    
        cout << "Floor " << curFloor<<endl;

    }
    pos.emplace_back(prow);
    pos.emplace_back(pcol);
    return pos;
}


void Floor::enemyMoveAndAttack() {
    //this one changed from moveEnemy() and enemyAction()!!! combines move and attack together
    //line by line fashion!!!
    
    int enRow,enCol;  //row, col of enemy
    int pRow = thePlayer->getRow();
    int pCol = thePlayer->getCol();
    
    for (int i = 0; i < numRow; ++i) {  //line by line fashion
        for (int j = 0; j < numCol; ++j) {
           int enemyThere = findEnemy(i, j);
            if (enemyThere > -1) {
                enRow = theEnemy[enemyThere]->getRow();
                enCol = theEnemy[enemyThere]->getCol();
                
                if (!theEnemy[enemyThere]->gethostile()){ //deal with dragon and merchant
                    
                    if (theEnemy[enemyThere]->getRace() == "Dragon") {
                        shared_ptr<Gold> tempGold = theEnemy[enemyThere]->getHoard();
                        enRow = tempGold->getRow();
                        enCol = tempGold->getCol();
                        if ((enRow-1 <= pRow && enRow+1 >= pRow) && (enCol-1 <= pCol && enCol+1 >= pCol)) {
                            theEnemy[enemyThere]->sethostile();
                            cout<< "\033[1;31mYou are near the dragon hoard. Dragon is now hostile.\033[0m"<<endl;
                        }
                    }
		    else { // merchant who is not hostile and can only move
                    enRow = theEnemy[enemyThere]->getRow();
                    enCol = theEnemy[enemyThere]->getCol();
                    theDisplay[enRow][enCol] = '.';
                    
                    while (true){
                        theEnemy[enemyThere]->setRow(enRow);
                        theEnemy[enemyThere]->setCol(enCol);
                        theEnemy[enemyThere]->moveEnemy();
                        if (theDisplay[theEnemy[enemyThere]->getRow()][theEnemy[enemyThere]->getCol()] == '.') break;
                    }
                    theDisplay[theEnemy[enemyThere]->getRow()][theEnemy[enemyThere]->getCol()]
                    = theEnemy[enemyThere]->getSym();
            }
                    
                }
                else  {  //deal with the rest of enemies and hostile merchant and dragon
                    if ((enRow-1 <= pRow && enRow+1 >= pRow) && (enCol-1 <= pCol && enCol+1 >= pCol)) {
                    theEnemy[enemyThere]->attack(thePlayer);
                        if(theEnemy[enemyThere]->getRace()=="Midterm"&&thePlayer->getRace()=="Student"){ //!!!
                            cout << "\033[1;31mYou fail the midterm!\033[0m" << endl;
                        }
                    } else { 
		      if (theEnemy[enemyThere]->getRace() != "Dragon"){  // hostile dragon is not included, dragon never moves
                        enRow = theEnemy[enemyThere]->getRow();
                        enCol = theEnemy[enemyThere]->getCol();
                        theDisplay[enRow][enCol] = '.';
                        
                        while (true){
                            theEnemy[enemyThere]->setRow(enRow);
                            theEnemy[enemyThere]->setCol(enCol);
                            theEnemy[enemyThere]->moveEnemy();
                            if (theDisplay[theEnemy[enemyThere]->getRow()][theEnemy[enemyThere]->getCol()] == '.') break;
                        }
                        theDisplay[theEnemy[enemyThere]->getRow()][theEnemy[enemyThere]->getCol()]
                        = theEnemy[enemyThere]->getSym();
		      }
		    }
		}
            }
        }
    }
}


void Floor::playerAttack(string direction) {
    vector<int> pos = nextStep(direction);
    int ind = findEnemy(pos.front(), pos.back());
    thePlayer->attack(theEnemy[ind]);
    if (theEnemy[ind]->getHP() <= 0) {
                theDisplay[theEnemy[ind]->getRow()][theEnemy[ind]->getCol()] = '.';
                theEnemy.erase(theEnemy.begin()+ind); 
        }
    }

bool Floor::checkdie(){
	if(thePlayer->getHP() > 0) return false;
	return true;
}





