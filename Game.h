//
//  Game.hpp
//  proj3
//
//  Created by Muthu Palaniappan on 5/13/20.
//  Copyright © 2020 Muthu Palaniappan. All rights reserved.
//

// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include <iostream>
#include <list>
#include "utilities.h"
using namespace std;
class Arena;
class Actor;

// You may add data members and other member functions to this class.

class Game
{
public:
  //  Game();
    ~Game();
    Game(int goblinSmellDistance);
    void play();
    void addMonster();

    
private:
    Arena* m_arena;
    
};

#endif // GAME_INCLUDED
