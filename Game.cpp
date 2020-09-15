// Game.cpp

#include "Game.h"
#include "Arena.h"
#include "Actors.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.



Game::Game(int goblinSmellDistance)
{   m_arena = new Arena();
    m_arena->setGoblinSmell(goblinSmellDistance);
    
      int rPlayer;
      int cPlayer;
      do
      {
          rPlayer = randInt(0, 17);
       //   cout<< rPlayer<<endl;
          cPlayer = randInt(0, 69);
        //  cout<<cPlayer<<endl;
      } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
      m_arena->addPlayer(rPlayer, cPlayer);
    
    
}




void Game::play()
{
    m_arena->display("");
    //hcout << "Press q to exit game." << endl;
    Player* player = m_arena->player();

    
    //cases based on what character is inputted
    while (!(player->getHP() <= 0) && (m_arena->getWin()==false)) {
        char getC = getCharacter();
        switch (getC) {
        case 'q':
            return;
        case 'g':
        case '>':
                player->playerMove(getC);
                break;
        case 'i':
                player->playerMove(getC);
                break;
            case 'w':{
                m_arena->showInv(player);
                char input = getCharacter();
                m_arena->wieldInv(input);
                player->playerMove(getC);
                break;
            }
            case 'r':{
                m_arena->showInv(player);
                char input = getCharacter();
                m_arena->scrollRead(input);
                player->playerMove(getC);
                break;
            }
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
        case ARROW_UP:
        case 'c':
            player->playerMove(getC);
            break;
        default:
            player->playerMove(getC);
            break;
        }
    }
    if (player->getHP() <= 0){
        cout << "You lose." << endl;
    cout << "Press q to exit game." << endl;
        while (getCharacter() != 'q'){
            
        }
        return;
    }
    else if (m_arena->getWin() == true){ 
        cout << "You win." << endl;
        cout << "Press q to exit game." << endl;
        while (getCharacter() != 'q'){}
        return;
    }
    else{
        cout << "You lose"<<endl;
        cout << "Press q to exit game." << endl;
        while (getCharacter() != 'q'){}
        return;
    }
}
   

Game::~Game()
{
    
    delete m_arena;
}




