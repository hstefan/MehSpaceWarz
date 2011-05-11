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

#include "Canon.hpp"
#include <iostream>

namespace hstefan
{
namespace game
{

Canon::Canon(unsigned int sw, unsigned int sh)
   : shots(), screen_width(sw), screen_height(sh)
{
   //shots.resize(100);
   loadTextures();
}

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
      tmp->first += tmp->second*9.0f;
      if(outOfScreen((*tmp).first))
      {
         shots.erase(it);
         break;
      }
   }
}

bool Canon::done()
{
   return false; //o canhão nunca termina
}

void Canon::render()
{
   std::deque<shot_t>::iterator shots_end = shots.end();
   const shot_t* tmp = 0;
   //glColor3f(1.f, .8f, .3f);
   
   glColor4f(1.f, 1.f, 1.f, 1.f);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
   glEnable(GL_TEXTURE_2D);

   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
   glBindTexture(GL_TEXTURE_2D, texture);
   
   glBegin(GL_QUADS);
      for(std::deque<shot_t>::const_iterator it = shots.begin(); it != shots_end; ++it)
      {
         tmp = &(*it);
         glTexCoord2f(0.f, 1.f);
         glVertex2f((*tmp).first[0] - 4, (*tmp).first[1] + 4);
         glTexCoord2f(0.f, 0.f);
         glVertex2f((*tmp).first[0] - 4, (*tmp).first[1] - 3);
         glTexCoord2f(1.f, 0.f);
         glVertex2f((*tmp).first[0] + 3, (*tmp).first[1] - 3);
         glTexCoord2f(1.f, 1.f);
         glVertex2f((*tmp).first[0] + 3, (*tmp).first[1] + 4);
      }
   glEnd();
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);

}

void Canon::loadTextures()
{
   glGenTextures(1, &texture);    
   glBindTexture(GL_TEXTURE_2D, texture); 
   GLuint flags = GLFW_BUILD_MIPMAPS_BIT | GLFW_ALPHA_MAP_BIT;
   if(glfwLoadTexture2D("mehsw-shot.tga", flags) == GL_FALSE) 
      std::cout << "falha ao carregar textura do tiro" << std::endl;
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); 
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}

} //namespace game
} //namespace hstefan
