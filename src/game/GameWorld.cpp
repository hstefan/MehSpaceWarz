#include "GameWorld.hpp"
#include <iostream>
#include <GL/glfw.h>

using hstefan::game::GameWorld;
using hstefan::game::GameObject;
GameWorld* GameWorld::_instance = new GameWorld();

typedef std::deque<GameObject*>::iterator deque_iter; 

void GameWorld::update()
{
   deque_iter it_end = game_objs.end();
   for(deque_iter it = game_objs.begin(); it != it_end; ++it) 
      (*it)->update();
}

void GameWorld::render()
{
   deque_iter it_end = game_objs.end();
   for(deque_iter it = game_objs.begin(); it != it_end; ++it) 
      (*it)->render();
}

void GameWorld::addObject(GameObject* gam)
{
   game_objs.push_back(gam);
}