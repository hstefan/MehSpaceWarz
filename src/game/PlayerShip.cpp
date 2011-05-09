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

#include "PlayerShip.hpp"
#include <GL/glfw.h>
#include "../math/transform.hpp"

#include <iostream>

namespace hstefan
{
namespace game
{
using namespace math;

PlayerShip::PlayerShip(const math::vec3& pos, unsigned int screen_w, unsigned int screen_h)
   : Ship(NUM_LIFES, HITPOINTS, 0.f, makeVec(0.f, 1.f, 1.f), pos, screen_w, screen_h),
   rot_queue(), transmission(), ratio(0), cur_ratio(0), rot_angle(0), max_speed(8.f), 
   handling(.05f), increase_ratio(false), decrease_ratio(false), canons(), shooting_latency(1/3),
   last_shoot(0)
{
   vertex[0] = makeVec(-SHIP_WIDTH/2, -SHIP_HEIGHT/2, 1);
   vertex[1] = makeVec(0.f, SHIP_HEIGHT/2, 1);
   vertex[2] = makeVec(SHIP_WIDTH/2, -SHIP_HEIGHT/2, 1);

   ratio_info r1 = {2.5f, 0.1f, 0.035f};
   ratio_info r2 = {4.2f, 0.07f, 0.030f};
   ratio_info r3 = {6.0f, 0.05f, 0.025f};
   ratio_info r4 = {8.0f, 0.04f, 0.02f};

   transmission[0] = r1;
   transmission[1] = r2;
   transmission[2] = r3;
   transmission[3] = r4;

   cur_ratio = & transmission[ratio];
}

void PlayerShip::update() 
{
   if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) 
   {
     speed += cur_ratio->acc;
     if(speed > cur_ratio->max)        
        speed = cur_ratio->max;
   }
   else
   {
      speed -= cur_ratio->breaking;
      if(speed < 0.f)
         speed = 0.f;
   }

   if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
      rot_queue.push(LEFT_ROTATION_ID); 
   if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
      rot_queue.push(RIGHT_ROTATION_ID);
   if(increase_ratio && glfwGetKey('A') == GLFW_RELEASE)
   {
      if(ratio < 3)
      {
         ++ratio;
         cur_ratio = &transmission[ratio];
      }
      increase_ratio = false;
   }
   if(decrease_ratio && glfwGetKey('D') == GLFW_RELEASE)
   {
      if(ratio > 0)
      {
         --ratio;
         cur_ratio = &transmission[ratio]; 
      } 
      decrease_ratio = false;
   }
   if(!increase_ratio && glfwGetKey('A') == GLFW_PRESS)
      increase_ratio = true;
   if(!decrease_ratio && glfwGetKey('D') == GLFW_PRESS)
      decrease_ratio = true;

   if(glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS /*&& canShoot()*/)
   {
      std::deque<Canon*>::iterator can_end = canons.end();
      for(std::deque<Canon*>::iterator it = canons.begin(); it != can_end; ++it)
         (*it)->shot(pos, dir);
      //std::cout << "shooot" << std::endl;
   }
   pos += dir*speed;
   checkPosition();
}

void PlayerShip::render()
{
   while(!rot_queue.empty())
   {
      if(rot_queue.front() == LEFT_ROTATION_ID) 
         rot_angle += handling;
      else
         rot_angle -= handling;
      rot_queue.pop();
   }
   if(rot_angle >= 360.f)
      rot_angle -= 360;

   math::mat3d rot = math::rotMat2dh(rot_angle);
   dir = rot*math::makeVec(0, 1, 1);
   math::mat3d trans = math::transMat2dh(pos[0], pos[1]);
   math::mat3d scale = math::scaleMat2dh((float)screen_w/SHIP_WINDOW_WIDTH, 
         (float)screen_h/SHIP_WINDOW_HEIGHT);

   math::mat3d res = trans*rot*scale;
   math::vec3 buff[3];
   for(unsigned int i = 0; i < 3; ++i)
      buff[i] = res*vertex[i];

   glColor3f(1.f, .3f, 0.f);
   glBegin(GL_TRIANGLES);
      glVertex2i(buff[0][0], buff[0][1]);
      glVertex2i(buff[1][0], buff[1][1]);
      glVertex2i(buff[2][0], buff[2][1]);
   glEnd();
}

void PlayerShip::checkPosition()
{
   if(pos[1] - SHIP_HEIGHT/2 > screen_h)
      pos[1] = -SHIP_HEIGHT/2;
   if(pos[1] + SHIP_HEIGHT/2 < 0)
      pos[1] = screen_h + SHIP_HEIGHT/2;
   if(pos[0] - SHIP_WIDTH/2 > screen_w)
      pos[0] = -SHIP_WIDTH/2;
   if(pos[0] + SHIP_WIDTH/2 < 0)
      pos[0] = screen_w + SHIP_WIDTH/2;
}

bool PlayerShip::canShoot()
{
   double now = glfwGetTime();
   if(now - last_shoot > shooting_latency)
   {
      last_shoot = now;
      return true;
   }
   return false;
}

} //namespace game
} //namesace hstefan
