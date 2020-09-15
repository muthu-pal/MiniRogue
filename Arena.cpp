//
//  Arena.cpp
//  proj3
//
//  Created by Muthu Palaniappan on 5/13/20.
//  Copyright © 2020 Muthu Palaniappan. All rights reserved.
//

#include "Arena.h"
#include "Actors.h"
#include "gameObjects.h"
#include "utilities.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;


//arena constructor - sets all the member variables and sets cell statuses to empty or wall; also adds objects and monsters randomly
Arena::Arena() :m_rows(18), m_cols(70), m_level(0), m_goblinSmell(15), win(false), m_MonsterAmt(randInt(2, 5*(1+1)+1))//: m_history(nRows, nCols)
{
    m_player = nullptr;
    
    createRandGrid();
    
    
    addObject();
    addMonster();
}

//arena destructor deletes anything allocated with "new"
Arena::~Arena(){
    for (list<gameObject*> :: iterator it = listObjs.begin(); it != listObjs.end(); ){
        if ((*it) != nullptr){
        delete (*it);
            it = listObjs.erase(it);
        }
        else{
            it++;
        }
    }
    for (list<Monster*> :: iterator it = listMonsters.begin(); it != listMonsters.end();){
        if ((*it) != nullptr){
        delete (*it);
            it = listMonsters.erase(it);
        }
        else{
            it++;
        }
    }
    delete m_player;    
    
}

//getters and setters
int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

void Arena::setGoblinSmell(int n){
    m_goblinSmell = n;
}
bool Arena::getWin(){
    return win;
}
void Arena::setWin(bool b){
    win = b; 
}

void Arena::setCellStatus(int r, int c, int status)
{
    m_grid[r][c] = status;
}


int Arena::getCellStatus(int r, int c) const
{
    return m_grid[r][c];
}

Player* Arena::player() const
{
    return m_player;
}


void Arena::setLevel(int l){
    m_level = l;
}

int Arena::getLevel(){
    return m_level;
}



//display function that reads cell statuses and object lists and couts a grid based on that

void Arena::display(string msg) 
{
    char displayGrid[18][70];
    int r, c;
    
      // Fill displayGrid with spaces (empty) and hashtags(walls)
    for (r = 0; r < 18; r++)
        for (c = 0; c < 70; c++){
            switch (getCellStatus(r, c)) {
                case EMPTY:
                    displayGrid[r][c] = ' ';
                    break;
                    
                case WALL:
                    displayGrid[r][c] = '#';
                    break;
                    
                case STAIRCASE:
                    displayGrid[r][c] = '>';
                    break;
                case GOBLIN:
                    displayGrid[r][c] = 'G';
                    break;
                case SNAKEWOMAN:
                    displayGrid[r][c] = 'S';
                    break;
                case BOGEYMAN:
                    displayGrid[r][c] = 'B';
                    break;
                case DRAGON:
                    displayGrid[r][c] = 'D';
                    break;
                default:
                    break;
            }
        }
    
    //these two for loops to establish precedence about which objects should appear on top of each other if r and c are the same
    for (list<gameObject*> :: iterator it = listObjs.begin(); it != listObjs.end(); it++) {
        if ((*it)->getName() == "short sword" || (*it)->getName() == "mace" || ((*it)->getName() == "magic fangs of sleep")
            || ((*it)->getName() == "long sword") || ((*it)->getName() == "magic axe")) {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = ')';
        }
        else if ((*it)->getName() == "staircase"){
            displayGrid[(*it)->getRow()][(*it)->getCol()] = '>';
        }
        else if ((*it)->getName() == "the golden idol"){
            displayGrid[(*it)->getRow()][(*it)->getCol()] = '&';
        }
        else {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = '?';
        }
    }
    
    for (list<Monster*> :: iterator it = listMonsters.begin(); it != listMonsters.end(); it++) {
        if ((*it)->getName() == "Goblin") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = 'G';
        }
        if ((*it)->getName() == "Snakewoman") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = 'S';
        }
        if ((*it)->getName() == "Bogeyman") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = 'B';
        }
        if ((*it)->getName() == "Dragon") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = 'D';
        }
    }
    
    
    if (m_player != nullptr)
        displayGrid[m_player->getRow()][m_player->getCol()] = '@';
    
    
      // Draw the grid
    clearScreen();
    for (r = 0; r < 18; r++)
    {
        for (c = 0; c < 70; c++)
            cout << displayGrid[r][c];
        cout << endl;
    }
    cout << endl;
    cout<< "Dungeon Level: "<<getLevel()<<", Hit points: "<<m_player->getHP()<<", Armor: "<<m_player->getAP()<<", Strength: "<<m_player->getStrength()<<", Dexterity: "<<m_player->getDext()<<endl<<endl<<endl;
    while (!actionLog.empty()){
        cout<<actionLog.front()<<endl;
        actionLog.pop();
    }
}


//creates a new player for our member variable and sets the cell status
bool Arena::addPlayer(int r, int c){
    m_player = new Player(this, r, c);
    setCellStatus(r, c, PLAYER);
    return true;
}

//adds new object to list when level is constructed
void Arena::addObject(){
    for (int i = 0; i < m_objAmt; i++){
    
    int n = randInt(6);
    
    switch (n){
        case 0:
            listObjs.emplace_back(new Mace());
            break;
        case 1:
            listObjs.emplace_back(new shortSword());
            break;
        case 2:
            listObjs.emplace_back(new longSword());
            break;
        case 3:
            listObjs.emplace_back(new enhanceArmor());
            break;
        case 4:
            listObjs.emplace_back(new raiseStrength());
            break;
        case 5:
            listObjs.emplace_back(new enhanceHealth());
            break;
        case 6:
            listObjs.emplace_back(new enhanceDexterity());
            break;
    }
    
    }
    //these are only added during certain levels
    if (m_level != 4){
    listObjs.emplace_back(new Staircase());
    }
    if (m_level == 4){
        listObjs.emplace_back(new goldenIdol());
    }
    
    setObj();
}

//places things in a random spot
void Arena::randomPlace(int &r, int &c){
    do
    {
        r = randInt(0, 17);
     //   cout<< rPlayer<<endl;
        c = randInt(0, 69);
      //  cout<<cPlayer<<endl;
    } while (getCellStatus(r, c) != EMPTY);
}
 //sets the row and col for an already constructed object that needs to be placed
void Arena::setObj(){
    
    for(list<gameObject*> :: iterator it = listObjs.begin(); it != listObjs.end(); it++){
        int row;
        int col;
        randomPlace(row, col);
        (*it)->setRow(row);
        (*it)->setCol(col);
    }
    
}
//similar to add obj function but this one is for monsters
void Arena::addMonster(){
    for (int i = 0; i < m_MonsterAmt; i++){  
        if (m_level == 0 || m_level == 1){
            int n = randInt(101, 102);
            int r,c;
            do
            {
                r = randInt(0, 17);
             //   cout<< rPlayer<<endl;
                c = randInt(0, 69);
              //  cout<<cPlayer<<endl;
            } while (getCellStatus(r, c) != EMPTY);
    
                switch (n){
                    case 101:
                        listMonsters.emplace_back(new Goblin(this,r,c));
                        setCellStatus(r, c, GOBLIN);
                        break;
                    case 102:
                        listMonsters.emplace_back(new Snakewoman(this,r,c));
                        setCellStatus(r, c, SNAKEWOMAN);
                        break;
                        }
        }
        if (m_level == 2){
                int n = randInt(101, 103);
                int r,c;
                do
                {
                    r = randInt(0, 17);
                 //   cout<< rPlayer<<endl;
                    c = randInt(0, 69);
                  //  cout<<cPlayer<<endl;
                } while (getCellStatus(r, c) != EMPTY);
        
                    switch (n){
                        case 101:
                            listMonsters.emplace_back(new Goblin(this,r,c));
                            setCellStatus(r, c, GOBLIN);
                            break;
                        case 102:
                            listMonsters.emplace_back(new Snakewoman(this,r,c));
                            setCellStatus(r, c, SNAKEWOMAN);
                            break;
                        case 103:
                            listMonsters.emplace_back(new Bogeyman(this,r,c));
                            setCellStatus(r, c, BOGEYMAN);
                            break;
                            }
        }
        if (m_level == 3 || m_level == 4){
                int n = randInt(101, 104);
                int r,c;
                do
                {
                    r = randInt(0, 17);
                 //   cout<< rPlayer<<endl;
                    c = randInt(0, 69);
                  //  cout<<cPlayer<<endl;
                } while (getCellStatus(r, c) != EMPTY);
        
                    switch (n){
                        case 101:
                            listMonsters.emplace_back(new Goblin(this,r,c));
                            setCellStatus(r, c, GOBLIN);
                            break;
                        case 102:
                            listMonsters.emplace_back(new Snakewoman(this,r,c));
                            setCellStatus(r, c, SNAKEWOMAN);
                            break;
                        case 103:
                            listMonsters.emplace_back(new Bogeyman(this,r,c));
                            setCellStatus(r, c, BOGEYMAN);
                            break;
                        case 104:
                            listMonsters.emplace_back(new Dragon(this,r,c));
                            setCellStatus(r, c, DRAGON);
                            break;
                            }
        }
    
    }
}
//allows monsters to move based on what type they are and what area they are in
void Arena::monsterMove(){
    for (list<Monster*> :: iterator it = listMonsters.begin(); it != listMonsters.end(); it++) {
        int monstRow = (*it)->getRow();
        int monstCol =(*it)->getCol();
        char dirChange='\0';
                if ((*it)->getName() == "Goblin") {
                    if (goblinSmell((*it), monstRow, monstCol, m_goblinSmell)){
                        dirChange = goblinMap.front();
                        goblinMap.pop();
                        switch (dirChange){
                            case ARROW_UP:
                                if (getCellStatus((*it)->getRow() - 1, (*it)->getCol()) == EMPTY){
                                (*it)->setRow((*it)->getRow() - 1);
                                setCellStatus((*it)->getRow(), (*it)->getCol(), GOBLIN);
                                setCellStatus((*it)->getRow()+1, (*it)->getCol(), EMPTY);
                                    break;
                                }
                                if (isNext(*it)){
                                    attack(*it, m_player);
                                }
                                break;
                                
                            case ARROW_DOWN:
                                if (getCellStatus((*it)->getRow() + 1, (*it)->getCol()) == EMPTY){
                                (*it)->setRow((*it)->getRow() + 1);
                                setCellStatus((*it)->getRow(), (*it)->getCol(), GOBLIN);
                                setCellStatus((*it)->getRow()-1, (*it)->getCol(), EMPTY);
                                    break;
                                }
                                if (isNext(*it)){
                                    attack(*it, m_player);
                                }
                                break;
                                
                            case ARROW_LEFT:
                                if (getCellStatus((*it)->getRow(), (*it)->getCol() - 1) == EMPTY){
                                (*it)->setCol((*it)->getCol() - 1);
                                setCellStatus((*it)->getRow(), (*it)->getCol(), GOBLIN);
                                setCellStatus((*it)->getRow(), (*it)->getCol() + 1, EMPTY);
                                    break;
                                }
                                if (isNext(*it)){
                                    attack(*it, m_player);
                                }
                                break;
                                
                            case ARROW_RIGHT:
                                if (getCellStatus((*it)->getRow(), (*it)->getCol() + 1) == EMPTY){
                                (*it)->setCol((*it)->getCol() + 1);
                                setCellStatus((*it)->getRow(), (*it)->getCol(), GOBLIN);
                                setCellStatus((*it)->getRow(), (*it)->getCol()-1, EMPTY);
                                    break;
                                }
                                if (isNext(*it)){
                                    attack(*it, m_player);
                                }
                                break;
                        }
                        
                    }
                    queue<char> empty;
                    goblinMap.swap(empty);
                }
                if ((*it)->getName() == "Snakewoman") {
                    if (smell(*it, 3) == true){
                        dirChange = moveDir(monstRow, monstCol);
                        switch (dirChange){
                            case ARROW_UP:
                                if (getCellStatus((*it)->getRow() - 1, (*it)->getCol()) == EMPTY){
                                (*it)->setRow((*it)->getRow() - 1);
                                setCellStatus((*it)->getRow(), (*it)->getCol(), SNAKEWOMAN);
                                setCellStatus((*it)->getRow()+1, (*it)->getCol(), EMPTY);
                                    break;
                                }
                                if (isNext(*it)){
                                    attack(*it, m_player);
                                }
                                break;
                                
                            case ARROW_DOWN:
                                if (getCellStatus((*it)->getRow() + 1, (*it)->getCol()) == EMPTY){
                                (*it)->setRow((*it)->getRow() + 1);
                                setCellStatus((*it)->getRow(), (*it)->getCol(), SNAKEWOMAN);
                                setCellStatus((*it)->getRow()-1, (*it)->getCol(), EMPTY);
                                    break;
                                }
                                if (isNext(*it)){
                                    attack(*it, m_player);
                                }
                                break;
                                
                            case ARROW_LEFT:
                                if (getCellStatus((*it)->getRow(), (*it)->getCol() - 1) == EMPTY){
                                (*it)->setCol((*it)->getCol() - 1);
                                setCellStatus((*it)->getRow(), (*it)->getCol(), SNAKEWOMAN);
                                setCellStatus((*it)->getRow(), (*it)->getCol() + 1, EMPTY);
                                    break;
                                }
                                if (isNext(*it)){
                                    attack(*it, m_player);
                                }
                                break;
                                
                            case ARROW_RIGHT:
                                if (getCellStatus((*it)->getRow(), (*it)->getCol() + 1) == EMPTY){
                                (*it)->setCol((*it)->getCol() + 1);
                                setCellStatus((*it)->getRow(), (*it)->getCol(), SNAKEWOMAN);
                                setCellStatus((*it)->getRow(), (*it)->getCol()-1, EMPTY);
                                    break;
                                }
                                if (isNext(*it)){
                                    attack(*it, m_player);
                                }
                                break;
                        }
                        
                    }
                }
                if ((*it)->getName() == "Bogeyman") {
                    if (smell(*it, 5) == true){
                        if (smell(*it, 3) == true){
                            dirChange = moveDir(monstRow, monstCol);
                            switch (dirChange){
                                case ARROW_UP:
                                    if (getCellStatus((*it)->getRow() - 1, (*it)->getCol()) == EMPTY){
                                    (*it)->setRow((*it)->getRow() - 1);
                                    setCellStatus((*it)->getRow(), (*it)->getCol(), BOGEYMAN);
                                    setCellStatus((*it)->getRow()+1, (*it)->getCol(), EMPTY);
                                        break;
                                    }
                                    if (isNext(*it)){
                                        attack(*it, m_player);
                                    }
                                    break;
                                    
                                case ARROW_DOWN:
                                    if (getCellStatus((*it)->getRow() + 1, (*it)->getCol()) == EMPTY){
                                    (*it)->setRow((*it)->getRow() + 1);
                                    setCellStatus((*it)->getRow(), (*it)->getCol(), BOGEYMAN);
                                    setCellStatus((*it)->getRow()-1, (*it)->getCol(), EMPTY);
                                        break;
                                    }
                                    if (isNext(*it)){
                                        attack(*it, m_player);
                                    }
                                    break;
                                    
                                case ARROW_LEFT:
                                    if (getCellStatus((*it)->getRow(), (*it)->getCol() - 1) == EMPTY){
                                    (*it)->setCol((*it)->getCol() - 1);
                                    setCellStatus((*it)->getRow(), (*it)->getCol(), BOGEYMAN);
                                    setCellStatus((*it)->getRow(), (*it)->getCol() + 1, EMPTY);
                                        break;
                                    }
                                    if (isNext(*it)){
                                        attack(*it, m_player);
                                    }
                                    break;
                                    
                                case ARROW_RIGHT:
                                    if (getCellStatus((*it)->getRow(), (*it)->getCol() + 1) == EMPTY){
                                    (*it)->setCol((*it)->getCol() + 1);
                                    setCellStatus((*it)->getRow(), (*it)->getCol(), BOGEYMAN);
                                    setCellStatus((*it)->getRow(), (*it)->getCol()-1, EMPTY);
                                        break;
                                    }
                                    if (isNext(*it)){
                                        attack(*it, m_player);
                                    }
                                    break;
                            }
                            
                            
                            
                        }
                        
                    }
                }
        if ((*it)->getName() == "Dragon"){
            Dragon* b = dynamic_cast<Dragon*>(*it);
            if (b != nullptr){
            if (b->getHP() < b->getMaxHPDrag()){
                int healRand = randInt(1, 10);
                if (healRand == 1){
                    b->setHP((*it)->getHP()+1);
                    }
                }
            }
            if (isNext(*it)){
                attack(*it, m_player);
            }
        }
        
        
    }
}
//does math to figure out if the monsters should move
bool Arena::smell(Monster* it, int r){
        int rowP = m_player->getRow();
        int colP = m_player->getCol();
    int rowM = (*it).getRow();
    int colM = (*it).getCol();
        
        int maxR = max(rowP, rowM);
        int minR = min(rowP, rowM);
        int maxC = max(colP,colM);
        int minC = min(colP, colM);
        
        
        int playerDist = (maxR-minR) + (maxC-minC);
        if (playerDist <= r){
            return true;
        }
        return false;
}
//sets the char to the direction that the monster must move based on relative area of player and monster
char Arena::moveDir(int r, int c){
    int rowP = m_player->getRow();
    int colP = m_player->getCol();
    int rowM = r;
    int colM = c;
    
    int dRow = rowP - rowM;
    int dCol = colP - colM;
    
    char dir = '\0';
    
    if (dRow > 0 && dCol >= 0){ //monster is above player and not at same column; needs to move down
        if (dRow >= dCol && dCol != 0) // if player is right of monster, then monster moves right
        {
            if((getCellStatus(r, c+1) == WALL))
                dir = ARROW_DOWN;
            else
                dir = ARROW_RIGHT;
        }
        else
        {
            if((getCellStatus(r+1, c) == WALL)) //if the row+1 is empty that means we can move right
                dir =ARROW_RIGHT;
            else
                dir = ARROW_DOWN;
        }
    }
    else if (dRow >= 0 && dCol < 0)
    {
        if(dRow >= (-dCol) || dRow == 0)
        {
            if ((getCellStatus(r, c-1) == WALL))
                dir = ARROW_DOWN;
            else
                dir = ARROW_LEFT;
        }
        else
        {
            if((getCellStatus(r+1, c) == WALL))
                dir =ARROW_LEFT;
            else
                dir = ARROW_DOWN;
        }
    }
    else if (dRow < 0 && dCol <= 0 )
    {
        if((-dRow) >= (-dCol) && dCol != 0)
        {
            if ((getCellStatus(r, c-1) == WALL))
                dir = ARROW_UP;
            else
                dir = ARROW_LEFT;
        }
        else
        {
            if((getCellStatus(r-1, c) == WALL))
                dir =ARROW_LEFT;
            else
                dir = ARROW_UP;
        }
    }
    
    else if (dRow <= 0 && dCol > 0)
    {
        if((-dRow) >= dCol  || dRow == 0)
        {
            if ((getCellStatus(r, c+1) == WALL))
                dir = ARROW_UP;
            else
                dir = ARROW_RIGHT;
        }
        else
        {
            if((getCellStatus(r-1, c) == WALL))
                dir =ARROW_RIGHT;
            else
                dir = ARROW_UP;
        }
    }
    
    return dir;
}

bool Arena::goblinSmell(Monster* it, int r, int c, int goblinDist) {
    int playerRow = m_player->getRow();
    int playerCol = m_player->getCol();

    if (goblinDist < 1) {
        return false;
    }
    if (r == playerRow && c == playerCol) {
        return true;
    }
    // Go south
    if (r < playerRow)
    {
    if (goblinSmell(it, r + 1, c, goblinDist - 1) && ((getCellStatus(r + 1, c) == PLAYER) || (getCellStatus(r + 1, c) == EMPTY))){
        goblinMap.push(ARROW_DOWN);
        return true;
    }
    }
    // go north
    if (r > playerRow)
    {
    if (goblinSmell(it, r - 1, c, goblinDist - 1) && ((getCellStatus(r - 1, c) == PLAYER) || (getCellStatus(r - 1, c) == EMPTY))){
        goblinMap.push(ARROW_UP);
        return true;
    }
    }
    // Go west
    if ( c > playerCol)
    {
    if (goblinSmell(it, r, c - 1, goblinDist - 1) && ((getCellStatus(r, c-1) == PLAYER) || (getCellStatus(r, c-1) == EMPTY))){
        goblinMap.push(ARROW_LEFT);
        return true;
    }
    }
    // go east
    if (c < playerCol)
    {
    if (goblinSmell(it, r, c + 1, goblinDist - 1) && ((getCellStatus(r, c+1) == PLAYER) || (getCellStatus(r, c+1) == EMPTY))){
        goblinMap.push(ARROW_RIGHT);
        return true;
    }
    }
    return false;
}





bool Arena::isNext(Monster* it){ //should tell us if the monster is directly next to the player
    int playerRow = m_player->getRow();
    int playerCol = m_player->getCol();
    int rowM = (*it).getRow();
    int colM = (*it).getCol();
    
    if (rowM+1 == playerRow && colM == playerCol){
        return true;
    }
    if (rowM-1 == playerRow && colM == playerCol){
        return true;
    }
    if (rowM == playerRow && colM+1 == playerCol){
        return true;
    }
    if (rowM+1 == playerRow && colM-1 == playerCol){
        return true;
    }
    return false;
}


//A dexterity bonus, an integer used in determining whether an attacker using that weapon hits the defender, using the following formula:
//    attackerPoints = attackerDexterity + weaponDexterityBonus;
//    defenderPoints = defenderDexterity + defenderArmorPoints;
//    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints))
//        attacker has hit defender
//A damage amount, an integer used in determining how much damage is done to a defender who is hit (i.e., how much the defender's hit points decrease), using the following formula:
//    damagePoints = randInt(0, attackerStrength + weaponDamageAmount - 1);
void Arena::attack(Actor* hunter, Actor* prey){
    string actions ="";
    string hits ="";
    string target = "";
    Weapon* h_weapon = hunter->getWeapon();
    if (h_weapon->getName() != "magic fangs of sleep"){
        int attackerPoints = hunter->getDext() + h_weapon->getDext();
        int defenderPoints = prey->getDext() + prey->getAP();
        
        actions = hunter->getName()+ " " + hunter->getWeapon()->getAction() + " the " + prey->getName();
        
        
        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)){
            int afterDamage = prey->getHP() - randInt(0, hunter->getStrength()+h_weapon->getDamg()-1);
            prey->setHP(afterDamage);
            hits = " and hits";
        }
        else {
            hits =" and misses";
        }
        
    }
    else {
        actions = hunter->getName()+ " " + hunter->getWeapon()->getAction() + " the " + prey->getName();
        int attackerPoints = hunter->getDext() + h_weapon->getDext();
        int defenderPoints = prey->getDext() + prey->getAP();
        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)){
            
            int afterDamage = prey->getHP() - randInt(0, hunter->getStrength()+h_weapon->getDamg()-1);
            prey->setHP(afterDamage);
            int sleepChance = randInt(1, 5);
            if (sleepChance == 1){
                int randSleep = randInt(2, 6);
                hits = " and hits, putting "+prey->getName()+" to sleep.";
                if (prey->getST() > 0){
                    prey->setST(max(prey->getST(), randSleep));
                }
                else {prey->setST(prey->getST()+ randSleep); }
            }
            else{
                hits =" and misses.";
            }
        }
    }
    Monster* b = dynamic_cast<Monster*>(prey);
    if (b != nullptr){
        if (isMonstDead(b)){
            hits = " dealing a final blow.";
            monstDrop(b);
            setCellStatus(b->getRow(), b->getCol(), EMPTY);
            list<Monster*> :: iterator it = listMonsters.begin();
            while (it != listMonsters.end()){
                if (*it == b){
                    delete (*it);
                    list<Monster*> :: iterator q = listMonsters.erase(it);
                    it = q;
                }
                else { it++;}
            }
        }
    }
    string finalAction = actions + hits;
    actionLog.push(finalAction);
    
}
//returns monster pointer's row and col position
Monster* Arena::getMonster(int r, int c){
    for (list<Monster*> :: iterator it = listMonsters.begin(); it != listMonsters.end(); it++) {
    int monstRow = (*it)->getRow();
    int monstCol =(*it)->getCol();
        if (monstRow == r && monstCol == c){
            return (*it);
        }
    }
    return nullptr;
}
//checks if the monster is dead
bool Arena::isMonstDead(Monster* it){
    if (it->getHP() <= 0){
        return true;
    }
    return false;
}
//allows player to pick up an item; cannot pick up a staircase
void Arena::pickUpItem(Player* p){
    list<gameObject*> :: iterator it = listObjs.begin();
    while( it != listObjs.end()) {
        int objRow = (*it)->getRow();
        int objCol =(*it)->getCol();
        if (objRow == p->getRow() && objCol == p->getCol()){
            if ((*it)->getName() == "staircase"){
                return;
            }
            if ((*it)->getName() == "the golden idol"){ //this means they won
                
                string action = "You pick up the golden idol.";
                actionLog.push(action);
                win = true;
                return;
            }
            
            if (p->getInv().size() > 25){
                string action = "Your knapsack is full; you can't pick that up.";
                actionLog.push(action);
                return;
            }
            
            //p->addInv((*it));
            p->getInv().push_back(*it);
            
            Scroll* b = dynamic_cast<Scroll*>(*it);
            if (b != nullptr) {
                string action = "You pick up a scroll called " + b->getName();
                actionLog.push(action);
            }
            else {
                string action = "You pick up a " + (*it)->getName();
                actionLog.push(action);
            }
            
           it = listObjs.erase(it);
        }
        else {it++;}
    }

}
//shows the inventory list
void Arena::showInv(Player* p){
    
    clearScreen();
    list<gameObject*> :: iterator it = p->getInv().begin();
    cout<<"Inventory: "<<endl;
    char counter = 'a';
    while( it != p->getInv().end()) {
        cout<<counter<<". ";
        cout<< (*it)->getName() <<endl;
        it++;
        counter++;
    }
}
//to weild a weapon; you cannot weild a scroll
void Arena::wieldInv(char c){
    
    
    list<gameObject*> inv = m_player->getInv();
        int answer = c - 'a';
        int w = 0;
        for (list<gameObject*>::iterator it = m_player->getInv().begin(); it != m_player->getInv().end(); it++) {
            if (w > answer)
                break;
            if (w == answer) {
                Weapon* b = dynamic_cast<Weapon*>(*it);
                if (b != nullptr) {
                    m_player->setWeapon(b);
                    string action = "You are wielding " + b->getName();
                    actionLog.push(action);
                    return;
                }
                else {
                    string action = "You can't wield " + (*it)->getName();
                    actionLog.push(action);
                    return;
                }
            }
            else
                w++;
        }

    
}
//read a scroll, but you cannot read a weapon
void Arena::scrollRead(char c){
    
    
        int answer = c - 'a';
        int w = 0;
        for (list<gameObject*>::iterator it = m_player->getInv().begin(); it != m_player->getInv().end(); it++) {
            if (w > answer)
                break;
            if (w == answer) {
                Scroll* s = dynamic_cast<Scroll*>(*it);
                if (s != nullptr) {
                    m_player->readScroll(s);
                    string action = "You read the scroll called " + s->getName();
                    actionLog.push(action);
                    delete(*it);
                    m_player->getInv().erase(it);
                    return;
                }
                else {
                    string action = "You can't read a " + (*it)->getName();
                    actionLog.push(action);
                    return;
                }
            }
            else
                w++; 
        }

    
}
//drops an item when a monster dies
void Arena::monstDrop(Monster* m){
    list<gameObject*> :: iterator it = listObjs.begin();
    while( it != listObjs.end()) {
        int objRow = (*it)->getRow();
        int objCol =(*it)->getCol();
        if (objRow == m->getRow() && objCol == m->getCol()){
            return;
        }
        else {it++;}
    }
    int x;
    if (m->getName() == "Dragon"){
        x = randInt(1, 5);
        switch (x){
            case 1:
                listObjs.emplace_back(new enhanceArmor(m->getRow(),m->getCol()));
                break;
            case 2:
                listObjs.emplace_back(new enhanceDexterity(m->getRow(),m->getCol()));
                break;
            case 3:
                listObjs.emplace_back(new enhanceHealth(m->getRow(),m->getCol()));
                break;
            case 4:
                listObjs.emplace_back(new Teleportation(m->getRow(),m->getCol()));
                break;
            case 5:
                listObjs.emplace_back(new raiseStrength(m->getRow(),m->getCol()));
                break;
        }
    }
    else if (m->getName() == "Snakewoman"){
        x = randInt(1, 3);
        if (x ==1){
            listObjs.emplace_back(new magicFang(m->getRow(),m->getCol()));
        }
    }
    else if (m->getName() == "Bogeyman"){
        x = randInt(1, 10);
        if (x ==1){
            listObjs.emplace_back(new magicAxe(m->getRow(),m->getCol()));
        }
    }
    else if (m->getName() == "Goblin"){
        x = randInt(1, 3);
        int y = randInt(1,2);
        if (x ==1){
            if (y == 1){
            listObjs.emplace_back(new magicAxe(m->getRow(),m->getCol()));
            }
            if (y == 2){
            listObjs.emplace_back(new magicFang(m->getRow(),m->getCol()));
            }
        }
    }
}
//changes the level when the player is on the staircase and presses the correct key
void Arena::nextLevel(Player* p){
    list<gameObject*> :: iterator it = listObjs.begin();
    while( it != listObjs.end()) {
        int objRow = (*it)->getRow();
        int objCol =(*it)->getCol();
        if (objRow == p->getRow() && objCol == p->getCol()){
            if ((*it)->getName() == "staircase"){
                resetGrid(p);
                
                return;
            }
        }
        it++;
    }
    return;
}


void Arena::resetGrid(Player* p){
    
    m_level++;
//    listObjs.clear();
    
    for (list<gameObject*> :: iterator it = listObjs.begin(); it != listObjs.end(); ){
        if (*it != nullptr){
        delete (*it);
            it = listObjs.erase(it);
        }
        else{
            it++;
        }
    }
    for (list<Monster*> :: iterator it = listMonsters.begin(); it != listMonsters.end();){
        if (*it != nullptr){
        delete (*it);
            it = listMonsters.erase(it);
        }
        else{
            it++;
        }
    }
    
    
//    listMonsters.clear();
    
    m_MonsterAmt = randInt(2, 5*(m_level+1)+1);
    
    
    createRandGrid();
    
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(0, 17);
     //   cout<< rPlayer<<endl;
        cPlayer = randInt(0, 69);
      //  cout<<cPlayer<<endl;
    } while (getCellStatus(rPlayer, cPlayer) != EMPTY);
    p->setRow(rPlayer);
    p->setCol(cPlayer);
    setCellStatus(p->getRow(), p->getCol(), PLAYER);
    
    
    addObject();
    addMonster();
    
    
}
//random room generation
void Arena::createRandGrid(){
    int numberOfRooms = randInt(4, 6);
    vector<Room> rooms(numberOfRooms);
    for (int a =0; a<18; a++){
        for (int b=0; b<70; b++){
            setCellStatus(a, b, WALL);
        }
    }
    
    //making the rooms
    for (int i = 0; i < numberOfRooms; ) {
            rooms[i].width = randInt(11, 15);
            rooms[i].height = randInt(6,9);
            rooms[i].row = randInt(1, 18 - rooms[i].height - 1); // Y Coord
            rooms[i].col = randInt(1, 70 - rooms[i].width- 1); // X Coord
            int minX = rooms[i].col;
            int minY = rooms[i].row;
            int maxY = rooms[i].row + rooms[i].height;
            int maxX = rooms[i].col + rooms[i].width;
            // Row and col are the TOP RIGHT of the room

            bool overlap = false;
            if (i > 0) {
                for (int h = 0; h < rooms[i].height; h++)
                    for (int w = 0; w < rooms[i].width; w++) {
                        if (getCellStatus(rooms[i].row + h, rooms[i].col + w) == EMPTY) {
                            overlap = true;
                            break;
                        }
                        if (getCellStatus(minY - 1, minX -1) == WALL &&
                            getCellStatus(maxY + 1, minX - 1) == WALL &&
                            getCellStatus(maxY + 1, maxX + 1) == WALL &&
                            getCellStatus(minY - 1, maxX + 1)
                            ) {
                            overlap = true;
                            break;
                        }
                    }
            }
            if (!overlap) {
                for (int h = 1; h < rooms[i].height - 1; h++)
                    for (int w = 1; w < rooms[i].width - 1; w++) {
                        setCellStatus(rooms[i].row + h, rooms[i].col + w, EMPTY);
                    }
                i++;
            }
        }
    

//for (int i = 0; i < numberOfRooms-1; i++) {
//    int midY1 = rooms[i].row + (rooms[i].height /2);
//    int midX1 = rooms[i].col + (rooms[i].width /2);
//    int midY2 = rooms[i+1].row + (rooms[i+1].height /2);
//    int midX2 = rooms[i+1].col + (rooms[i+1].width /2);
//
//    if (midX1 <= midX2 && midY1 <= midY2) {
//        for (int a = midX1; a <= midX2; a++)
//            setCellStatus(midY1, a, EMPTY);
//
//        for (int a = midY1; a <= midY2; a++)
//            setCellStatus(a, midX2, EMPTY);
//    }
//    if (midX1 <= midX2 && midY1 > midY2) {
//        for (int a = midX1; a <= midX2; a++)
//            setCellStatus(midY1, a, EMPTY);
//
//        for (int a = midY2; a <= midY1; a++)
//            setCellStatus(a, midX2, EMPTY);
//    }
//    if (midX1 > midX2 && midY1 <= midY2) {
//        for (int a = midX2; a <= midX1; a++)
//            setCellStatus(midY2, a, EMPTY);
//
//        for (int a = midY1; a < midY2; a++)
//            setCellStatus(a, midX1, EMPTY);
//    }
//    if (midX1 > midX2 && midY1 > midY2) {
//        for (int a = midX2; a < midX1; a++)
//            setCellStatus(midY2, a, EMPTY);
//
//        for (int a = midX2; a < midX1; a++)
//            setCellStatus(a, midX1, EMPTY);
//    }
//
//}
    for (int c = 0; c < numberOfRooms-1; c++)
    {
        int middleRow1 = rooms[c].row + (rooms[c].height / 2);
        int middleRow2 = rooms[c+1].row + (rooms[c+1].height / 2);
        int middleCol1 = rooms[c].col + (rooms[c].width / 2);
        int middleCol2 = rooms[c+1].col + (rooms[c+1].width / 2);
        if (middleCol1 <= middleCol2 && middleRow1 <= middleRow2)
        {
            for (int d = 0; d < middleCol2-middleCol1+1; d++)
            {
                setCellStatus(middleRow1,d+middleCol1, EMPTY);
            }
            for (int e = 0; e < middleRow2-middleRow1; e++)
            {
                setCellStatus(middleRow2-e,middleCol2,EMPTY);
            }
        }
        if (middleCol1 <= middleCol2 && middleRow1 > middleRow2)
        {
            for (int f = 0; f < middleCol2-middleCol1+1; f++)
            {
                setCellStatus(middleRow1,f+middleCol1, EMPTY);
            }
            for (int g = 0; g < middleRow1-middleRow2; g++)
            {
                setCellStatus(middleRow2+g,middleCol2,EMPTY);
            }
        }
        if (middleCol1 > middleCol2 && middleRow1 <= middleRow2)
           {
            for (int h = 0; h < middleCol1-middleCol2+1; h++)
            {
                setCellStatus(middleRow2,h+middleCol2,EMPTY);
            }
            for (int i = 0; i < middleRow2-middleRow1; i++)
            {
                setCellStatus(middleRow1+i,middleCol1,EMPTY);
            }
        }
        if (middleCol1 > middleCol2 && middleRow1 > middleRow2)
        {
            for (int j = 0; j < middleCol1-middleCol2+1; j++)
            {
                setCellStatus(middleRow2,j+middleCol2, EMPTY);
            }
            for (int k = 0; k < middleRow1-middleRow2; k++)
            {
                setCellStatus(middleRow1-k,middleCol1,EMPTY);
            }
        }
    }
}


    
    


 
