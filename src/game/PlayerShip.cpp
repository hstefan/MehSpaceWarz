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
   rot_queue(), rot_angle(0)
{
   vertex[0] = makeVec(-SHIP_WIDTH/2, SHIP_HEIGHT/2, 1);
   vertex[1] = makeVec(-SHIP_WIDTH/2, -SHIP_HEIGHT/2, 1);
   vertex[2] = makeVec(SHIP_WIDTH/2, -SHIP_HEIGHT/2, 1);
   vertex[3] = makeVec(SHIP_WIDTH/2, SHIP_HEIGHT/2, 1);
}
void PlayerShip::update() 
{
   if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) 
   {
      std::cout << "up pressed" << std::endl;
   } 
   else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) 
   {
      std::cout << "down pressed" << std::endl;
   }
   else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
   {
      rot_queue.push(LEFT_ROTATION_ID); 
   }
   else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
   {
      rot_queue.push(RIGHT_ROTATION_ID);
   }
}

void PlayerShip::render()
{
   while(!rot_queue.empty())
   {
      if(rot_queue.front() == LEFT_ROTATION_ID) 
         rot_angle += 0.1f;
      else
         rot_angle -= 0.1f;
      rot_queue.pop();
   }
   if(rot_angle >= 360.f)
      rot_angle -= 360;

   math::mat3d rot = math::rotMat2dh(rot_angle);
   math::mat3d trans = math::transMat2dh(pos[0], pos[1]);
   math::mat3d scale = math::scaleMat2dh((float)screen_w/SHIP_WINDOW_WIDTH, 
         (float)screen_h/SHIP_WINDOW_HEIGHT);

   math::mat3d res = trans*rot*scale;
   math::vec3 buff[4];
   for(unsigned int i = 0; i < 4; ++i)
      buff[i] = res*vertex[i];

   glColor3f(1.f, 0.f, 0.f);
   glBegin(GL_QUADS);
      glVertex2i(buff[0][0], buff[0][1]);
      glVertex2i(buff[1][0], buff[1][1]);
      glVertex2i(buff[2][0], buff[2][1]);
      glVertex2i(buff[3][0], buff[3][1]);
   glEnd();
}

} //namespace game
} //namesace hstefan
