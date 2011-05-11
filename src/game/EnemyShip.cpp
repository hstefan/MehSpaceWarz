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

#include "EnemyShip.hpp"
#include "../math/transform.hpp"
#include <iostream>
namespace hstefan
{
namespace game
{
   EnemyShip::EnemyShip(Ship* tracking, const math::vec3& pos, unsigned int screen_w, unsigned int screen_h)
      : Ship(0, 100, 0.f, math::makeVec(0,1,1), pos, screen_w, screen_h),
      rot_angle(0.f), max_speed(6.f), acc(0.01f), angle_left(0.f), tracking(tracking)
   {
      vertex[0] = math::makeVec(-SHIP_WIDTH/2, SHIP_HEIGHT/2, 1);
      vertex[1] = math::makeVec(-SHIP_WIDTH/2, -SHIP_HEIGHT/2, 1);
      vertex[2] = math::makeVec(SHIP_WIDTH/2, -SHIP_HEIGHT/2, 1);
      vertex[3] = math::makeVec(SHIP_WIDTH/2, SHIP_HEIGHT/2, 1);
      loadTexture();
   }

   void EnemyShip::update()
   { 
      math::vec3 tpos_buf = tracking->getPos();
      math::vec2 tpos_2 = math::makeVec(tpos_buf[0], tpos_buf[1]);
      math::vec2 mpos_2 = math::makeVec(pos[0], pos[1]); 
      angle_left = 360.f*math::angle2dh(tpos_2, mpos_2);
      math::mat3d rot = math::rotMat2dh(angle_left);
      math::vec3 ve = rot*pos;
      float ren = dot(math::makeVec(ve[0], ve[1]), mpos_2);
      if(std::abs(ren) <= 0.012)
      {
         angle_left = angle_left - 360;
      }
      if(speed < max_speed && math::norm(tpos_2 - mpos_2) >  50.f)
      {
         if(speed < 0)
            speed = 0;
         speed += acc;
         pos += dir*speed;
      }
      if(speed > max_speed)
         speed = max_speed/2;
   }

   void EnemyShip::render()
   {
      math::mat3d rot = math::rotMat2dh(0);
      dir = tracking->getDir();       
      math::mat3d trans = math::transMat2dh(pos[0], pos[1]); 
      math::mat3d scale = math::scaleMat2dh((float)screen_w/SHIP_WINDOW_WIDTH, 
            (float)screen_h/SHIP_WINDOW_HEIGHT);
      math::mat3d res = trans*rot*scale;       
      math::vec3 buff[4];
      for(unsigned int i = 0; i < 4; ++i)
         buff[i] = res*vertex[i]; 

      glColor4f(1.f, 1.f, 1.f, 1.f);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
      glEnable(GL_TEXTURE_2D);

      glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
      glBindTexture(GL_TEXTURE_2D, texture); 
      glBegin(GL_QUADS);
         glTexCoord2f(0.f, 1.f);
         glVertex2f(buff[0][0], buff[0][1]);
         glTexCoord2f(0.f, 0.f);
         glVertex2f(buff[1][0], buff[1][1]);
         glTexCoord2f(1.f, 0.f);
         glVertex2f(buff[2][0], buff[2][1]);
         glTexCoord2f(1.f, 1.f);
         glVertex2f(buff[3][0], buff[3][1]);
      glEnd();
   }

   void EnemyShip::loadTexture()
   {
      glGenTextures(1, &texture); //gera 3 texturas no vetor textures (GLuint textures[3])
      glBindTexture(GL_TEXTURE_2D, texture); //binda a textura da nave parada (0)
      GLuint flags = GLFW_BUILD_MIPMAPS_BIT | GLFW_ALPHA_MAP_BIT;
      if(glfwLoadTexture2D("mehsw-enemy.tga", flags) == GL_FALSE) //carrega a textura
         std::cout << "falha ao carregar textura do inimigo" << std::endl;
      
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //seta o MIN filter
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //set o MAG filter
      glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); //seta o wrap
      glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
   }

} //
} //namespace hstefan
