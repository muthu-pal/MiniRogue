//
//  Arena.hpp
//  proj3
//
//  Created by Muthu Palaniappan on 5/13/20.
//  Copyright © 2020 Muthu Palaniappan. All rights reserved.
//

#ifndef Arena_h
#define Arena_h
#include "utilities.h"
#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;


const int EMPTY = 100;
const int WALL = 200;
const int PLAYER = 300;
const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;


class Actor;
class Monster;
class Player;

class gameObject;


struct Room {
    int height;
    int width;
    int row;
    int col;
};







class Arena
{
  public:
      // Constructor/destructor
    Arena();
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    int getCellStatus(int r, int c) const;
    int getLevel();
    bool getWin();
   
    bool addPlayer(int r, int c);
    void setCellStatus(int r, int c, int status);
    void addObject();
    void setObj();
    void setGoblinSmell(int n);
    void setLevel(int l);
    void setWin(bool b);
    void randomPlace(int &r, int &c);
    void addMonster();
    void monsterMove();
    bool smell(Monster* it, int r);
    char moveDir(int r, int c);
    bool goblinSmell(Monster* it, int r, int c, int goblinDist);
    char goblinDirection(int r, int c);
    bool isNext(Monster* it);
    void attack(Actor* hunter, Actor* prey);
    Monster* getMonster(int r, int c);
    bool isMonstDead(Monster* it);
    void pickUpItem(Player* p);
    void showInv(Player* p);
    void wieldInv(char c);
    void scrollRead(char c);
    void monstDrop(Monster* m);
    void resetGrid(Player* p);
    Player* player() const;
    void nextLevel(Player* p);
    

  
    void display(std::string msg);
    void createRandGrid();
    bool isOverlapping(int l1x, int l1y, int r1x, int r1y, int l2x, int l2y, int r2x, int r2y);

    
    
  private:
    int     m_grid[18][70]; //our grid of cell statuses
    int      m_rows; //18 rows
    int      m_cols; //70 cols
    int m_objAmt = randInt(2, 3); //object amt initialized to a randInt
    Player* m_player; //maintains player with a pointer
    list<gameObject*> listObjs; //keeps tracks of game objects on level
    
    int m_level; //keeps track of the level
    list<Monster*> listMonsters; //keeps track of the monsters on the level
    int m_MonsterAmt; //number of monsters per level
    
    int m_goblinSmell; //goblin smell distance given in game constructor
    
    
    queue<char> goblinMap;  //to tell the goblin which way to move
    queue<string> actionLog; //queue to get cout statements under the display
    
    bool win; //checks if the status of the game is win or not
    

    
};


#endif /* Arena_hpp */
