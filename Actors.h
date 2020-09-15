//
//  Actors.hpp
//  proj3
//
//  Created by Muthu Palaniappan on 5/13/20.
//  Copyright © 2020 Muthu Palaniappan. All rights reserved.
//

#ifndef Actors_h
#define Actors_h
#include <iostream>
#include <list>
#include "utilities.h"
#include "Arena.h"
#include "Game.h"
#include "gameObjects.h"
using namespace std;

class Arena;

const int GOBLIN = 101;
const int SNAKEWOMAN = 102;
const int BOGEYMAN = 103;
const int DRAGON = 104;

class Actor{
    
public:
    Actor(Arena* ap, int r, int c, int hitP, int armP, int dext, int sleepT, int str, string name) : m_arena(ap), posRow(r), posCol(c), hitPoints(hitP), armorPoints(armP), dexterity(dext), sleepTime(sleepT), strength(str), m_name(name){
//        Weapon* initial = new shortSword();
//        setWeapon(initial);
    }
    
    virtual ~Actor();
    
  //  virtual void move();
    void setHP(int h);
    void setAP(int a);
    void setDext(int d);
    void setST(int sleep);
    void setStrength(int s);
    void setRow(int r);
    void setCol(int c);
    void setWeapon(Weapon* w);
   
    int getHP();
    int getAP();
    int getDext();
    int getST();
    int getStrength();
    int getRow() const;
    int getCol() const;
    string getName();
    
    void readScroll(Scroll* s);
    
    Weapon* getWeapon();
    
    void playerMove(char move);
    
    
    
private:
    int hitPoints; //0-99
    int armorPoints;
    int dexterity;
    int sleepTime; //0-9
    int posRow; //position
    int posCol; //position
    int strength;
    Weapon* weapon;
    
    Arena* m_arena;
    
    string m_name;
    
    //Weapon weapons;
};

class Monster : public Actor{
public:
    Monster(Arena* ap, int r, int c, int hitP, int armP, int dext, int sleepT, int str,  string name): Actor(ap,r,c, hitP,armP,dext,sleepT,str, name){}
    ~Monster(){};
    
    
private:
    

};

class Player : public Actor {
public:
    virtual ~Player();
    Player(Arena* ap, int r, int c) : Actor(ap,r,c, 20,2,2,0,2, "Player"){
        Weapon* initial = new shortSword();
        setWeapon(initial);
        playerInvList.push_back(initial);
    }
    
    void setMaxHP(int m);
    int getMaxHP();
    void addInv(gameObject* g);
    list<gameObject*>& getInv();
    
    
private:
    int maxHP = 20;
    list<gameObject*> playerInvList;
    
    

};

class Bogeyman : public Monster {
public:
    Bogeyman(Arena* ap, int row, int col): Monster(ap, row, col, randInt(5, 10), 2, randInt(2, 3), 0, randInt(2, 3), "Bogeyman"){
        Weapon* initial = new shortSword();
        setWeapon(initial);
    }
    ~Bogeyman(){};
    
};

class Snakewoman : public Monster {
public:
    Snakewoman(Arena* ap, int row, int col): Monster(ap, row, col, randInt(3, 6), 3, 3, 0, 2, "Snakewoman"){
        Weapon* initial = new magicFang();
        setWeapon(initial);
    }
    ~Snakewoman(){};
    
};

class Dragon : public Monster {
public:
    Dragon(Arena* ap, int row, int col): Monster(ap, row, col, randInt(20, 25), 4, 4, 0,4, "Dragon"){
        Weapon* initial = new longSword();
        setWeapon(initial);
    }
    ~Dragon(){};
    void setMaxHPDrag(int m);
    int getMaxHPDrag();
    
    
    
private:
    int maxHPDrag = getHP(); 
    
};

class Goblin : public Monster {
public:
    Goblin(Arena* ap, int row, int col): Monster(ap,row, col, randInt(15, 20), 1, 1, 0, 3,"Goblin"){
        Weapon* initial = new shortSword();
        setWeapon(initial);
    }
    
   // virtual void move();
    ~Goblin(){};
};

#endif /* Actors_h */
