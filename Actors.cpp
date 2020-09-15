//
//  Actors.cpp
//  proj3
//
//  Created by Muthu Palaniappan on 5/13/20.
//  Copyright © 2020 Muthu Palaniappan. All rights reserved.
//

#include "Actors.h"
#include <iostream>
using namespace std;


//getters and setters
void Actor::setHP(int h){
    hitPoints = h;
}
void Actor::setAP(int a){
    armorPoints = a;
}
void Actor::setDext(int d){
    dexterity = d;
}
void Actor::setST(int sleep){
    sleepTime = sleep;
}
void Actor::setStrength(int s){
    strength = s;
}

int Actor::getHP(){
    return hitPoints;
}
int Actor::getAP(){
    return armorPoints;
}
int Actor::getDext(){
    return dexterity;
}
int Actor::getST(){
    return sleepTime;
}
int Actor::getStrength(){
    return strength;
}

int Actor::getRow() const{
    return posRow;

}

int Actor::getCol() const{
    return posCol;
 
}

void Actor::setRow(int r){
    posRow = r;
}


void Actor::setCol(int c){
    posCol = c;
}

Weapon* Actor::getWeapon(){
    return weapon;
}

void Actor::setWeapon(Weapon* w){
    weapon = w; 
}

//responsible for player moving and attacking and for reading characters like w or g
void Actor::playerMove(char move) {

    Player* player = m_arena->player();

    switch (move) {
        case (DOWN):
    case ARROW_DOWN: // Moves down
            if (getST()>0){
                setST(getST()-1);
                break;
            }
        if (m_arena->getCellStatus(player->getRow() + 1, player->getCol()) == EMPTY) {
            player->setRow(player->getRow() + 1);
            m_arena->setCellStatus(player->getRow(), player->getCol(), PLAYER);
            m_arena->setCellStatus(player->getRow()-1, player->getCol(), EMPTY);
        }
        if (m_arena->getCellStatus(player->getRow() + 1, player->getCol()) == BOGEYMAN || m_arena->getCellStatus(player->getRow() + 1, player->getCol()) == SNAKEWOMAN || m_arena->getCellStatus(player->getRow() + 1, player->getCol()) == GOBLIN || m_arena->getCellStatus(player->getRow() + 1, player->getCol()) == DRAGON) {
            if (m_arena->getMonster(player->getRow() + 1, player->getCol()) != nullptr){
                Monster* a = m_arena->getMonster(player->getRow() + 1, player->getCol());
                m_arena->attack(player, a);
            
            }
            }
            
        break;
        case LEFT:
    case ARROW_LEFT: // Moves left
            if (getST()>0){
                setST(getST()-1);
                break;
            }
        if (m_arena->getCellStatus(player->getRow(), player->getCol() - 1) == EMPTY) {
            player->setCol(player->getCol() - 1);
            m_arena->setCellStatus(player->getRow(), player->getCol(), PLAYER);
            m_arena->setCellStatus(player->getRow(), player->getCol() + 1, EMPTY);
        }
            if (m_arena->getCellStatus(player->getRow(), player->getCol()-1) == BOGEYMAN || m_arena->getCellStatus(player->getRow(), player->getCol()-1) == SNAKEWOMAN || m_arena->getCellStatus(player->getRow(), player->getCol()-1) == GOBLIN || m_arena->getCellStatus(player->getRow(), player->getCol()-1) == DRAGON) {
            if (m_arena->getMonster(player->getRow(), player->getCol()-1) != nullptr){
                Monster* a = m_arena->getMonster(player->getRow(), player->getCol()-1);
                m_arena->attack(player, a);
            
            }
            }
            
        break;
        case RIGHT:
    case ARROW_RIGHT: // Moves right
            if (getST()>0){
                setST(getST()-1);
                break;
            }
        if (m_arena->getCellStatus(player->getRow(), player->getCol() + 1) == EMPTY) {
            player->setCol(player->getCol() + 1);
            m_arena->setCellStatus(player->getRow(), player->getCol(), PLAYER);
            m_arena->setCellStatus(player->getRow(), player->getCol()-1, EMPTY);
        }
            if (m_arena->getCellStatus(player->getRow(), player->getCol()+1) == BOGEYMAN || m_arena->getCellStatus(player->getRow(), player->getCol()+1) == SNAKEWOMAN || m_arena->getCellStatus(player->getRow(), player->getCol()+1) == GOBLIN || m_arena->getCellStatus(player->getRow(), player->getCol()+1) == DRAGON) {
            if (m_arena->getMonster(player->getRow(), player->getCol()+1) != nullptr){
                Monster* a = m_arena->getMonster(player->getRow(), player->getCol()+1);
                m_arena->attack(player, a);
            
            }
            }
        break;
        case UP:
    case ARROW_UP: // Moves up
            if (getST()>0){
                setST(getST()-1);
                break;
            }
        if (m_arena->getCellStatus(player->getRow() - 1, player->getCol()) == EMPTY) {
            player->setRow(player->getRow() - 1);
            m_arena->setCellStatus(player->getRow(), player->getCol(), PLAYER);
            m_arena->setCellStatus(player->getRow()+1, player->getCol(), EMPTY);
        }
            
            if (m_arena->getCellStatus(player->getRow() - 1, player->getCol()) == BOGEYMAN || m_arena->getCellStatus(player->getRow() - 1, player->getCol()) == SNAKEWOMAN || m_arena->getCellStatus(player->getRow() - 1, player->getCol()) == GOBLIN || m_arena->getCellStatus(player->getRow() - 1, player->getCol()) == DRAGON) {
            
            if (m_arena->getMonster(player->getRow() - 1, player->getCol()) != nullptr){
                Monster* a = m_arena->getMonster(player->getRow() - 1, player->getCol());
                m_arena->attack(player, a);
            
            }
            }
            
        break;
            
        case 'c':
            player->setStrength(9);
            player->setMaxHP(50);
            break;
        case 'g':
            this->m_arena->pickUpItem(player);
            break;
        case 'i':
            this->m_arena->showInv(player);
            getCharacter();
            this->m_arena->monsterMove();
            this->m_arena->display("");
            return;
        case 'r':
        case 'w':
            this->m_arena->monsterMove();
            this->m_arena->display("");
            return;
        case '>':{
            this->m_arena->nextLevel(player);
            this->m_arena->display("");
            return;
        }
            
    default:
        break;
    }
    
    if (player->getHP() < player->getMaxHP()){
        int healRand = randInt(1, 10);
        if (healRand == 1){
            player->setHP(player->getHP()+1);
        }
    }
    
    this->m_arena->monsterMove(); //allows monster to move too
    
    this->m_arena->display(""); //displays the grid after both move
    
}
//setters and getters again
Actor::~Actor(){
    delete weapon;
}

Player::~Player(){
    list<gameObject*> :: iterator it = playerInvList.begin();
    while (it != playerInvList.end()){
        if (((*it) != nullptr) && ((*it) != getWeapon())){
            delete (*it);
            it = playerInvList.erase(it);
        }
        else{
            it++;
        }
    }
    
}


string Actor::getName(){
    return m_name;
}

void Player::setMaxHP(int m){
    maxHP = m;
}
   

int Player::getMaxHP(){
    return maxHP;
}

void Dragon::setMaxHPDrag(int m){
    maxHPDrag = m;
}

int Dragon::getMaxHPDrag(){
    return maxHPDrag;
}
//returns the player's inventory list
list<gameObject*>& Player::getInv(){
    return playerInvList;
}
//to add to the player's inventory
void Player::addInv(gameObject* g){ 
    playerInvList.push_back(g);
}
//reads a scroll and changes stats based on that
void Actor::readScroll(Scroll* s){
    string name = s->getName();
    if (name == "scroll of teleportation"){
        int rPlayer;
        int cPlayer;
        m_arena->setCellStatus(m_arena->player()->getRow(), m_arena->player()->getCol(), EMPTY);
        do
        {
            rPlayer = randInt(0, 17);
         //   cout<< rPlayer<<endl;
            cPlayer = randInt(0, 69);
          //  cout<<cPlayer<<endl;
        } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
        m_arena->player()->setRow(rPlayer);
        m_arena->player()->setCol(cPlayer);
        m_arena->setCellStatus(m_arena->player()->getRow(), m_arena->player()->getCol(), PLAYER);
    }
    if (name == "scroll of enhance armor"){
        m_arena->player()->setAP(m_arena->player()->getAP() + randInt(1, 3));
    }
    if (name == "scroll of strength"){
        m_arena->player()->setStrength(m_arena->player()->getStrength() + randInt(1, 3));
    }
    if (name == "scroll of enhance health"){
        m_arena->player()->setMaxHP(m_arena->player()->getMaxHP() + randInt(3, 8));
    }
    if (name == "scroll of enhance dexterity"){
        m_arena->player()->setDext(m_arena->player()->getDext() + 1);
    }
    
}
