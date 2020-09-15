//
//  gameObjects.cpp
//  proj3
//
//  Created by Muthu Palaniappan on 5/14/20.
//  Copyright © 2020 Muthu Palaniappan. All rights reserved.
//

#include "gameObjects.h"

//getters and setters
int gameObject::getRow(){
    return objRow;
}

int gameObject::getCol(){
    return objCol;
}

void gameObject::setRow(int r){
    objRow = r;
}

void gameObject::setCol(int c){
    objCol = c;
}

int Weapon::getDext(){
    return dexterityBonus;
}
int Weapon::getDamg(){
    return damageAmt;
}
void Weapon::setDext(int n){
    dexterityBonus = n;
}
void Weapon::setDamg(int n){ 
    damageAmt = n;
}

string gameObject::getName(){
    return m_name;
}

void gameObject::setAction(string s){
    action = s;
}
string gameObject::getAction(){
    return action;
}

