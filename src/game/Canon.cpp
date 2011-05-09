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

#include "Canon.hpp"
#include <GL/glfw.h>

namespace hstefan
{
namespace game
{

Canon::Canon(unsigned int sw, unsigned int sh)
   : shots(), screen_width(sw), screen_height(sh)
{}

void Canon::shot(const math::vec3& orig, const math::vec3& dir)
{
   shots.push_back(std::pair<math::vec3, math::vec3>(orig, dir));
}

void Canon::update()
{
   std::deque<shot_t>::iterator shots_end = shots.end();
   shot_t* tmp = 0;
   for(std::deque<shot_t>::iterator it = shots.begin(); it != shots_end; ++it)
   {
      tmp = &(*it);
      tmp->first += tmp->second;
      if(outOfScreen((*tmp).first))
         shots.erase(it);
   }
}

bool Canon::done()
{
   return false;
}

void Canon::render()
{
   std::deque<shot_t>::iterator shots_end = shots.end();
   shot_t* tmp = 0;
   glBegin(GL_QUADS);
      for(std::deque<shot_t>::iterator it = shots.begin(); it != shots_end; ++it)
      {
         tmp = &(*it);
         glVertex2i((*tmp).first[0] - 1, (*tmp).first[0] + 1);
         glVertex2i((*tmp).first[0] - 1, (*tmp).first[1] - 1);
         glVertex2i((*tmp).first[0] + 1, (*tmp).first[1] - 1);
         glVertex2i((*tmp).first[0] + 1, (*tmp).first[1] + 1);
      }
   glEnd();
}

} //namespace game
} //namespace hstefan
