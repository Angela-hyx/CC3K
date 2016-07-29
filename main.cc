#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "floor.h"
#include "chamber.h"
#include "character.h"
#include "player.h"
#include "player/human.h"
#include "player/dwarf.h"
#include "player/elves.h"
#include "player/orc.h"
#include "player/student.h"
#include <ctime>

using namespace std; 

int main(int argc, char* argv[]) {
	bool withFile = false;
	bool DLC = false;
	string argDLC = "dlc";
	string myFile;
	srand((unsigned)time(NULL));
 if (argc > 1) {
for (int i = 1; i < argc; ++i) {
	cout <<argv[i]<<endl;
	cout<<strcmp(argv[i], argDLC.c_str())<<endl;
	if (strcmp(argv[i],argDLC.c_str()) == 0) {
		DLC = true;
	} else if (atoi(argv[i]) != 0) {
		srand(atoi(argv[i]));
	} else {
		ifstream file;
		file.open(argv[i], ios::in);
		if (!file) {
			cout << "\033[1;31mInvalid command line arguments. Please try again.\033[0m"<<endl;
			return 0;
		} else {
		withFile = true;
                myFile = argv[i];
		}
	}
 } 
}

  cout << "\033[1;33mWelcome to ChamberCrawler3000!\033[0m" << endl;
  string s2;
  ifstream welcome{"welcome.txt"};
  while(getline(welcome,s2)){
	  cout << "\033[1;35m";
	  cout << s2 << endl;
	  cout << "\033[0m";
  }



  while (true) {
    string command;
    
    // generate PC
    cout << "Please choose your player character." << endl;
    cout << "\033[1;31mh\033[0m stands for human." << endl;
    cout << "\033[1;31md\033[0m stands for dwarf." << endl;
    cout << "\033[1;31me\033[0m stands for elves." << endl;
    cout << "\033[1;31mo\033[0m stands for orc." << endl;
    if (DLC) {
     cout << "\033[1;31ms\033[0m stands for student. 200HP, 50Atk, 50Def." << endl;
     cout<<"\033[3;35mFor real fighters, the creators allow you to fight with your own identity, student.\033[0m"<<endl;
     cout<<"\033[3;35mYou have\033[0m \033[1;31mimmeasurable strength\033[0m."<<endl;
     cout<< "\033[3;35mBut\033[0m \033[1;31mwatch out\033[0m \033[3;35mfor the\033[0m \033[1;31mmidterm\033[0m\033[3;35m, you don't have any chance to be alive when you are too close to it.\033[0m"<<endl;
    }
 
      
auto floor = make_shared<Floor>();
 floor->setDLC(DLC);
string race;    
    cin >> command;
    while(true) {
    if (command == "h") {
        auto newPlayer = make_shared<Human> (-1, -1, -1);
        floor->setPlayer(newPlayer);
      break;
    } else if (command == "d") {
        auto newPlayer = make_shared<Dwarf> (-1, -1, -1);
        floor->setPlayer(newPlayer);
      break;
    } else if (command == "e") {
        auto newPlayer = make_shared<Elves> (-1, -1, -1);
        floor->setPlayer(newPlayer);
      break;
    } else if (command == "o") {
        auto newPlayer = make_shared<Orc> (-1, -1, -1);
        floor->setPlayer(newPlayer);
      break;
    }
    else if (command == "s") {
        auto newPlayer = make_shared<Student> (-1, -1, -1);
        floor->setPlayer(newPlayer);
        break;
    }
     else {
      cout << "\033[1;31mPlease choose a valid player.\033[0m" << endl;
        cin>>command;
    }
  }

      race = command;

      if (withFile) {
	      floor->readFloor(myFile);
      } else {
      floor->setFloor();
      }
     // cout << "\033[1;34m";
      floor->printFloor();

      cout << "Please enter a valid command:" << endl;
      cout << "Change directions: no, so, ea, we, ne, se, sw, nw" << endl;
      cout << "Use Potion: u <direction>" << endl;
      cout << "Attack enemy: a <direction>" << endl;
      cout << "Reset the game : r" << endl;
      cout << "Quit: q" << endl;
    while (cin>>command) {
        if (command == "no" ||command ==  "so" ||command ==  "ea"
               ||command ==  "we" ||command ==  "ne" ||command ==  "se" ||command ==  "sw" ||command ==  "nw") { // read direction
            
            if (floor->checkPoint(command, '\\')) {
                if (floor->getCurFloor() == 5){
                    floor->setWon();
                    cout << "\033[1;33mCongratulations! You win the game!\033[0m" << endl;
		    string s4;
		      ifstream win{"win.txt"};
		        while(getline(win,s4)){
				cout << "\033[1;33m";
				cout << s4 << endl;
				cout << "\033[0m";
			}

		    if(race=="h"){
		      cout << "\033[1;36mYour final score is:\033[0m " << (floor->getgoldAmt() + (floor->getgoldAmt()/2)) << endl;
		    }
		    else if(race == "d"){
		      cout << "\033[1;36mYour final score is:\033[0m " << floor->getgoldAmt() * 2 << endl;
		    }
		    else if(race == "o"){
		      cout << "\033[1;36mYour final score is:\033[0m " << floor->getgoldAmt()/2 << endl;
		    }
		    else{
                    cout << "\033[1;36mYour final score is:\033[0m " << floor->getgoldAmt() << endl;
		    }
		    break;   
                } else {
                    //  auto newplayer = floor
	           //  floor.reset (new Floor);
		    floor->nextFloor();
	            floor->clearFloor();
		    if (withFile) {
			    floor->readFloor(argv[1]);
		    } else {         
                    floor->setFloor();
		    }
		    floor->printFloor();
                }
            }
	  else if (floor->isValid(command)) {
	    floor->movePlayer(command);
        floor->enemyMoveAndAttack();
	if(floor->checkdie()) break;// PC dies
	    floor->printFloor();
      } else {
          cout<<"\033[1;31mThere is no way to go.\033[0m"<<endl;
      }
    }

        else if (command == "u") {  // use Potion
	  cin >> command;  // read direction
	  if (floor->checkPoint(command, 'P')) { //checkPotion checks if there's a potion on the direction command
	    floor->consumePotion(command);  // usePotion is in Player class
        if(floor->checkdie()) break;
	floor->enemyMoveAndAttack();
	if(floor->checkdie()) break;// PC dies
        floor->printFloor();
      } else {
	    cout << "\033[1;31mThere's nothing there.\033[0m" << endl;
	  }
        }
        
        else if (command == "a") {  // attack enemy
	  cin >> command;  // read direction
	  if (floor->checkPoint(command, 'V') || floor->checkPoint(command, 'W') || floor->checkPoint(command, 'N') ||
	      floor->checkPoint(command, 'M') || floor->checkPoint(command, 'D') || floor->checkPoint(command, 'X') ||
          floor->checkPoint(command, 'T') || floor->checkPoint(command, 'E')) {  // checks if there's enemy on the direction command
	    floor->playerAttack(command);  // attack is in player class
        floor->enemyMoveAndAttack();
	if(floor->checkdie()) break;// PC dies
        floor->printFloor();
	  } else {
	    cout << "\033[1;31mThere's no enemy in the direction you pointed.\033[0m" << endl;
	  }
        }
      
        else if (command == "r") {
	  floor->clearFloor(); // reset the game, means clearing and deleting the floor including unique ptrs, in floor class
	  break;
        } else if (command == "q") {
	  break;
        } else {
	  cout << "\033[1;31mPlease enter a valid command.\033[0m" << endl;
        }
    }
      
      
      
    if (command == "q") {
        cout << "\033[1;33mThank you for playing ChamberCrawler3000. Have a good day!\033[0m" << endl;
        string s5;
        ifstream byebye{"byebye.txt"};
        while(getline(byebye,s5)){
            cout << "\033[1;35m";
            cout << s5 << endl;
            cout << "\033[0m";
        }
        break;

    }

    if(floor->checkdie()){
	   // it's so mean! cout << "haha! You lose!" << endl;
            string s3;
	    ifstream lose{"lose.txt"};
	    while(getline(lose,s3)){
		    cout << "\033[1;34m";
		    cout << s3 << endl;
		    cout << "\033[0m";
	    }

    }

    if (floor->isWon() || floor->checkdie()) { // aim to ask for the second round
        string c;
        cout << "\033[1;33mDo you want to play the game again?\033[0m y/n" << endl;
        while(cin >> c) {
      if (c == "n") {
	cout << "\033[1;33mThank you for playing ChamberCrawler3000. Have a good day!\033[0m" << endl;
          string s6;
          ifstream byebye{"byebye.txt"};
          while(getline(byebye,s6)){
              cout << "\033[1;35m";
              cout << s6 << endl;
              cout << "\033[0m";
          }
	break;
      } else if (c == "y") {
          break;
      } else {
	cout << "\033[1;31mPlease enter a valid command.\033[0m y/n" << endl;
      }
        }
        if(c=="n"){
            break;
        }
    }
      
      
  }
}





