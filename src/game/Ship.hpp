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
#ifndef HSTEFAN_SHIP_HPP
#define HSTEFAN_SHIP_HPP

#include "GameObject.hpp"
#include "../math/vector.hpp"

namespace hstefan
{
namespace game
{

   class Ship : public GameObject
   {
   public:
      Ship(unsigned int lifes, unsigned int hp, float speed, const math::vec3& dir,
            const math::vec3& pos, unsigned int screen_w, unsigned int screen_h);

      virtual void update() = 0;
      virtual void render() = 0;
      bool done();
      
      inline math::vec3 getPos()
      {
         return pos;
      }

      inline float getSpeed()
      {
         return speed;
      }
   protected:
      unsigned int lifes;
      unsigned int hp;
      float speed;
      
      math::vec3 dir;
      math::vec3 pos;

      const unsigned int screen_w;
      const unsigned int screen_h;
   };

} //namespace game
} //namespace hstefan

#endif
