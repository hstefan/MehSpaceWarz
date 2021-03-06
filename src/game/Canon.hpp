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

#ifndef HSTEFAN_CANON_HPP
#define HSTEFAN_CANON_HPP

#include "GameObject.hpp"
#include "../math/vector.hpp"
#include <deque>
#include <utility>
#include <GL/glfw.h>


namespace hstefan
{
namespace game
{
   class Canon : public GameObject
   {
   public:
      Canon(unsigned int sw, unsigned int sh);
      void shot(const math::vec3& orig, const math::vec3& dir); //atira, argumentos de posição inicial e direção do tiro
      void update();
      void render();
      bool done();
      
      typedef std::pair<math::vec3, math::vec3> shot_t; //vectores de posição e direção
   protected:
      inline bool outOfScreen(const math::vec3& pos); //verifica se o tiro esta fora da tela (encerrou seu ciclo de vida)
      void loadTextures();
   private:
      std::deque<shot_t > shots;
      unsigned int screen_width;
      unsigned int screen_height;
      GLuint texture;
   };

   bool Canon::outOfScreen(const math::vec3& pos)
   {
      return pos[0] > screen_width|| pos [0] < 0 || pos[1] > screen_height || pos[1] < 0;
   }

}//namespace game
}//namespace hstefan

#endif
