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
#include <iostream>

namespace hstefan
{
namespace game
{
using namespace math;

PlayerShip::PlayerShip(const math::vec3& pos, unsigned int screen_w, unsigned int screen_h)
   : Ship(NUM_LIFES, HITPOINTS, 0.f, makeVec(0.f, 1.f, 1.f), pos, screen_w, screen_h)
{}

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
      std::cout << "left pressed" << std::endl;
   }
   else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
   {
      std::cout << "right pressed" << std::endl;
   }
}

void PlayerShip::render()
{
}

} //namespace game
} //namesace hstefan
