/**********************************************************************************
 * Copyright (C) 2011 by Hugo Stefan Kaus Puhlmann                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 * copies of the Software, and to permit persons to whom the Software is          * 
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in     *
 * all copies or substantial portions of the Software.                            *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN      *
 * THE SOFTWARE.                                                                  *
 *********************************************************************************/

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
   {
      if(!(*it)->done())
         (*it)->update();
      else
         game_objs.erase(it);
   }
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
