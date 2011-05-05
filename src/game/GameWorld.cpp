#include "GameWorld.hpp"
#include <iostream>

using hstefan::game::GameWorld;

GameWorld* GameWorld::_instance = new GameWorld();

void GameWorld::update()
{
   std::cout << "updatan" << std::endl;
}

void GameWorld::render()
{
   std::cout << "renderan" << std::endl;
}