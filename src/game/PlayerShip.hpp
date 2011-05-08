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
#ifndef HSTEFAN_PLAYER_SHIP_HPP
#define HSTEFAN_PLAYER_SHIP_HPP
#include "Ship.hpp"
#include "../math/vector.hpp"
#include <queue>

namespace hstefan
{
namespace game
{ 
   class PlayerShip : public Ship
   {
   public:
      static const unsigned int NUM_LIFES = 3;
      static const unsigned int HITPOINTS = 150;
      static const int SHIP_WIDTH = 32;
      static const int SHIP_HEIGHT = 32;
      static const int SHIP_WINDOW_HEIGHT = 800;
      static const int SHIP_WINDOW_WIDTH = 800;

      static const int LEFT_ROTATION_ID = 0;
      static const int RIGHT_ROTATION_ID = 1;

       PlayerShip(const math::vec3& pos, unsigned int screen_w, unsigned int screen_h);
      void update();
      void render();
   private:
      std::queue<char> rot_queue;
      float rot_angle;
      math::vec3 vertex[4];
   };

} //namespace game
} //namespace hstefan

#endif
