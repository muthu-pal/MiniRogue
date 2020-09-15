//
//  gameObjects.hpp
//  proj3
//
//  Created by Muthu Palaniappan on 5/14/20.
//  Copyright © 2020 Muthu Palaniappan. All rights reserved.
//

#ifndef gameObjects_h
#define gameObjects_h
#include <iostream>
using namespace std;


//const ints to keep track of objects
const int MACE = 0;
const int SHORTSWORD = 1;
const int LONGSWORD = 2;
const int ENHANCEARMOR = 3;
const int ENHANCESTRENGTH = 4;
const int ENHANCEHEALTH = 5;
const int ENHANCEDEXTERITY = 6;

const int MAGICAXE = 7;
const int MAGICFANG = 8;
const int TELEPORTATION =9;
const int STAIRCASE = 10;


class gameObject{
public:
    gameObject(string n, int r, int c, string log) : m_name(n), objRow(r), objCol(c), action(log) {};
    gameObject(string n, string log) : m_name(n),action(log){};
    virtual ~gameObject(){};
    
    int getRow();
    int getCol();
    string getName();
    
    void setRow(int r);
    void setCol(int c);
    void setAction(string s);
    string getAction();
    
    
    
    
private:
    string m_name;
    int objRow;
    int objCol;
    string action;
    
};

class Weapon : public gameObject{
public:
    Weapon(int dB, int dA, string n, int r, int c, string log) : dexterityBonus(dB), damageAmt(dA), gameObject(n,r,c,log){};
    Weapon(int dB, int dA, string n, string log) : dexterityBonus(dB), damageAmt(dA), gameObject(n,log){};
    virtual ~Weapon(){};
        
    int getDext();
    int getDamg();
    void setDext(int n);
    void setDamg(int n);
    
private:
    int dexterityBonus;
    int damageAmt;
};


class Mace : public Weapon{
public:
    Mace(int r, int c) : Weapon(0,2,"mace",r,c,"swings mace at"){};
    Mace() : Weapon(0,2,"mace","swings mace at"){};
    ~Mace(){};
private:
    
};

class shortSword : public Weapon{
public:
    shortSword(int r, int c) : Weapon(0,2,"short sword",r,c,"slashes short sword at"){};
    shortSword() : Weapon(0,2,"short sword","slashes short sword at"){};
    virtual ~shortSword(){};
private:
    
};

class longSword : public Weapon{
public:
    longSword(int r, int c) : Weapon(2,4,"long sword",r,c,"swings long sword at"){};
    longSword() : Weapon(2,4,"long sword","swings long sword at"){};
    virtual ~longSword(){};
private:
    
};

class magicAxe : public Weapon{
public:
    magicAxe(int r, int c) : Weapon(5,5,"magic axe",r,c,"chops magic axe at"){};
    magicAxe() : Weapon(5,5,"magic axe","chops magic axe at"){};
    virtual ~magicAxe(){};
private:
    
};

class magicFang : public Weapon{
public:
    magicFang(int r, int c) : Weapon(3,2,"magic fangs of sleep",r,c,"strikes magic fangs at"){};
    magicFang() : Weapon(3,2,"magic fangs of sleep","strikes magic fangs at"){};
    virtual ~magicFang(){};
private:
    
};



class Scroll : public gameObject{
    public:
    Scroll (string n, int r, int c,string log) : gameObject(n, r, c, log){};
    Scroll (string n,string log) : gameObject(n,log){};
    virtual ~Scroll(){};
    private:
    
};

class Teleportation : public Scroll {
public:
    Teleportation(int r, int c) : Scroll("scroll of teleportation",r,c,"You feel your body wrenched in space and time."){};
    Teleportation() : Scroll("scroll of teleportation","You feel your body wrenched in space and time."){};
    virtual ~Teleportation(){};
private:
    
    
};

class enhanceArmor : public Scroll {
public:
    enhanceArmor(int r, int c) : Scroll("scroll of enhance armor",r,c,"Your armor glows blue."){};
    enhanceArmor() : Scroll("scroll of enhance armor","Your armor glows blue."){};
    virtual ~enhanceArmor(){};
private:
    
    
};

class raiseStrength : public Scroll {
public:
    raiseStrength(int r, int c) : Scroll("scroll of strength",r,c,"Your muscles bulge."){};
    raiseStrength() : Scroll("scroll of strength","Your muscles bulge."){};
    virtual ~raiseStrength(){};
private:
    
    
};

class enhanceHealth : public Scroll {
public:
    enhanceHealth(int r, int c) : Scroll("scroll of enhance health",r,c,"You feel your heart beating stronger."){};
    enhanceHealth() : Scroll("scroll of enhance health","You feel your heart beating stronger."){};
    virtual ~enhanceHealth(){};
private:
    
    
};

class enhanceDexterity : public Scroll {
public:
    enhanceDexterity(int r, int c) : Scroll("scroll of enhance dexterity",r,c,"You feel like less of a klutz."){};
    enhanceDexterity() : Scroll("scroll of enhance dexterity","You feel like less of a klutz."){};
    virtual ~enhanceDexterity(){};
private:
    
    
};




class Staircase : public gameObject{
    public:
    Staircase() : gameObject("staircase",""){};
    virtual ~Staircase(){};
    

    
};

class goldenIdol : public gameObject{
public:
    goldenIdol() : gameObject("the golden idol",""){};
    virtual ~goldenIdol(){};
};


#endif /* gameObjects_hpp */
