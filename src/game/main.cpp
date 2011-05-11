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
/*
 * Nome: Hugo Stefan Kaus Puhlmann
 * Matricula: 2910182
 */
#include <GL/glfw.h>
#include "GameWorld.hpp"
#include "PlayerShip.hpp"
#include "Canon.hpp"
#include "../math/vector.hpp"
#include <ctime>
#include <cstdlib>
#include <GL/glu.h>
#include "EnemyShip.hpp"
#include <iostream>

int main()
{
   std::cout << "Trabalho 2 CG - Meh Space Warz!" << std::endl;
   std::cout << "Consiste em movimentacao basica de uma navezinha na tela." << std::endl;
   std::cout << "A: aumenta marcha da nave" << std::endl;
   std::cout << "D: diminui marcha da nave" << std::endl;
   std::cout << "<espaco>: atira" << std::endl;
   std::cout << "Setas: controlam a nave" << std::endl;
   std::cout << "obs: cada marcha possui velocidade maxima, aceleracao e frenagem propria." << std::endl;

   std::cout << "Extras: " << "tiro, nave inimiga perseguidora, marchas" << std::endl;
   static const int WINDOW_HEIGHT = 600;
   static const int WINDOW_WIDTH = 600;
   glfwInit();
   glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
   glfwOpenWindow(WINDOW_HEIGHT, WINDOW_WIDTH, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);

   using hstefan::game::GameWorld;
   using hstefan::game::PlayerShip;
   using hstefan::game::Canon;
   using namespace hstefan::math;
   using hstefan::game::EnemyShip;

   GameWorld* world = GameWorld::getInstance();
   PlayerShip* ship = new PlayerShip(makeVec(WINDOW_WIDTH/2,WINDOW_HEIGHT
            /2,1), WINDOW_WIDTH, WINDOW_HEIGHT);
   Canon* can = new Canon(WINDOW_WIDTH, WINDOW_HEIGHT);
   EnemyShip* enemy = new EnemyShip(ship, makeVec(200, 200, 1), WINDOW_WIDTH, WINDOW_HEIGHT);
   //EnemyShip* enemy2 = new EnemyShip(ship, makeVec(550, 550, 1), WINDOW_WIDTH, WINDOW_HEIGHT);
   ship->addCanon(can);
   world->addObject(can);
   world->addObject(ship);
   world->addObject(enemy);
   //world->addObject(enemy2);
   bool running = true;

   double last_render = 0;
   double last_update = 0;

   double frame_interval = 1.f/60.f;
   double update_interval = 1.f/90.f;

   double cur_time = 0;
   glClearColor(0.f, 0.f, 0.f, 1.f);
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   //float proj[16] = {2/800, 0, 0, 0, 0, 2/800, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1};
   //glLoadMatrixf(proj);
   gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
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
   delete world;
   delete ship;
   delete enemy;
   delete can;
   glfwTerminate();
}
