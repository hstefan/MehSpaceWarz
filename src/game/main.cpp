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

#include <GL/glfw.h>
#include "GameWorld.hpp"
#include "PlayerShip.hpp"
#include "../math/vector.hpp"
#include <ctime>
#include <cstdlib>
#include <GL/glu.h>


int main()
{
   glfwInit();
   glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
   glfwOpenWindow(800, 800, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);

   using hstefan::game::GameWorld;
   using hstefan::game::PlayerShip;
   using namespace hstefan::math;

   GameWorld* world = GameWorld::getInstance();
   PlayerShip* ship = new PlayerShip(makeVec(400,400,1), 800, 800);
   world->addObject(ship);
   bool running = true;

   double last_render = 0;
   double last_update = 0;

   double frame_interval = 1.f/60.f;
   double update_interval = 1.f/90.f;

   double cur_time = 0;
   glClearColor(0.f, 0.f, 0.f, 1.f);
   glMatrixMode(GL_PROJECTION);
   //glPushMatrix();
   glLoadIdentity();
   //float proj[16] = {2/800, 0, 0, 0, 0, 2/800, 0, 0, 0, 0, 1, 0, -400, -400, 0, 1};
   //glLoadMatrixf(proj);
   gluOrtho2D(0, 800, 0, 800);
   while(running) 
   {
      cur_time = glfwGetTime();
       
      if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) 
         break;
      if(cur_time - last_render > frame_interval) 
      {
         last_render = glfwGetTime();
         glClear(GL_COLOR_BUFFER_BIT);   
         world->render();
         glfwSwapBuffers();
      }
      
      if(cur_time - last_update > update_interval)
      {
         world->update();
         last_update = glfwGetTime();
      }
      glfwSleep(update_interval - (cur_time + glfwGetTime()));
      running = glfwGetWindowParam(GLFW_OPENED) != 0;
   }

   glfwTerminate();
}
