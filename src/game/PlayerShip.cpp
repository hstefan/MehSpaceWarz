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
   last_shoot(0), cur_tex(0)
{
   /*
    * Vértices do quadrado onde a textura está mapeada.
    */
   vertex[0] = makeVec(-SHIP_WIDTH/2, SHIP_HEIGHT/2, 1);
   vertex[1] = makeVec(-SHIP_WIDTH/2, -SHIP_HEIGHT/2, 1);
   vertex[2] = makeVec(SHIP_WIDTH/2, -SHIP_HEIGHT/2, 1);
   vertex[3] = makeVec(SHIP_WIDTH/2, SHIP_HEIGHT/2, 1);

   /*
    * Informações de marchas da nave (para regular velocidade máxima, aceleração e frenagem.
    * {velocide máxima, aceleração, frenagem}
    */
   ratio_info r1 = {2.5f, 0.1f, 0.035f};
   ratio_info r2 = {4.2f, 0.07f, 0.030f};
   ratio_info r3 = {6.0f, 0.05f, 0.025f};
   ratio_info r4 = {8.0f, 0.04f, 0.02f};

   /*
    * Insere as marchas em um map.
    */
   transmission[0] = r1;
   transmission[1] = r2;
   transmission[2] = r3;
   transmission[3] = r4;

   /*
    * Inicializa marcha atual para a primeira marcha (ratio == 0).
    */
   cur_ratio = & transmission[ratio];
   /*
    * Carrega as texturas da nave. Melhores explicações na função.
    */
   loadTextures();
}

void PlayerShip::update() 
{
   if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) 
   {
      cur_tex = 2;  
      speed += cur_ratio->acc;
      if(speed > cur_ratio->max)        
         speed = cur_ratio->max;
   }
   else
   {
      speed -= cur_ratio->breaking;
      cur_tex = 1;
      if(speed < 0.f)
      {
         speed = 0.f;
         cur_tex = 0;
      }
   }

   if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
      rot_queue.push(LEFT_ROTATION_ID); //adciona uma rotação para esquerda na fila de rotações.
   if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
      rot_queue.push(RIGHT_ROTATION_ID); //rotação para esquerda
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
      //faz com que todos canhões atirem
      for(std::deque<Canon*>::iterator it = canons.begin(); it != can_end; ++it)
         (*it)->shot(pos, dir);
   }
   pos += dir*speed; //incrementa a posição baseado na velocidade da nave e no vetor direção
   checkPosition(); //checa se a posição esta dentro da tela
}

void PlayerShip::render()
{
   while(!rot_queue.empty())
   {
      /*
       * rot_angle é o angulo de rotação que deve ser aplicado (atributo da classe).
       * handling é a 'dirigilidade' da nave, ou seja, quanto ela vira a cada rotação.
       */
      if(rot_queue.front() == LEFT_ROTATION_ID) 
         rot_angle += handling; 
      else
         rot_angle -= handling;
      rot_queue.pop();
   }
   if(rot_angle >= 360.f)
      rot_angle -= 360; 

   math::mat3d rot = math::rotMat2dh(rot_angle);
   dir = rot*math::makeVec(0, 1, 1); //rotaciona o vetor que aponta para cima (direção inicial)
   math::mat3d trans = math::transMat2dh(pos[0], pos[1]); //cria uma matriz de translação até o ponto onde a nave se encontra
   math::mat3d scale = math::scaleMat2dh((float)screen_w/SHIP_WINDOW_WIDTH, 
         (float)screen_h/SHIP_WINDOW_HEIGHT); //cria uma matriz de escala (as texturas são projetadas para 800x800,
                                              //caso a resolução mude é interessante redimensionar a imagem)

   math::mat3d res = trans*rot*scale; //matriz que aplica scaling, rotação e translação.
   math::vec3 buff[4];
   for(unsigned int i = 0; i < 4; ++i) //aplica a matriz res para todos os vértices
      buff[i] = res*vertex[i]; 

   glColor4f(1.f, 1.f, 1.f, 1.f);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
   glEnable(GL_TEXTURE_2D);

   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
   glBindTexture(GL_TEXTURE_2D, textures[cur_tex]); //cur_tex é a textura atual (utilizado para fins de animação)
   glBegin(GL_QUADS); //desenha a nave
      glTexCoord2f(0.f, 1.f);
      glVertex2i(buff[0][0], buff[0][1]);
      glTexCoord2f(0.f, 0.f);
      glVertex2i(buff[1][0], buff[1][1]);
      glTexCoord2f(1.f, 0.f);
      glVertex2i(buff[2][0], buff[2][1]);
      glTexCoord2f(1.f, 1.f);
      glVertex2i(buff[3][0], buff[3][1]);
   glEnd();

   if(speed == max_speed)
   {
      float alpha = 0.1;
      math::mat3d tr = math::transMat2dh(-10*dir[0], -10*dir[1]);
      for(unsigned int i = 0; i < 3; ++i) //desenha um efeitinho caso a nave esteja na velocidade máxima
      {                                   //são basicamente repetições da nave que ficam para trás e são "mais transparentes"
         glColor4f(1.f,1.f,1.f, alpha);
         glBegin(GL_QUADS);
            buff[0] = tr*buff[0];
            buff[1] = tr*buff[1];
            buff[2] = tr*buff[2];
            buff[3] = tr*buff[3];
            
            glTexCoord2f(0.f, 1.f);
            glVertex2i(buff[0][0], buff[0][1]); 
            glTexCoord2f(0.f, 0.f);
            glVertex2i(buff[1][0], buff[1][1]);
            glTexCoord2f(1.f, 0.f);
            glVertex2i(buff[2][0], buff[2][1]);  
            glTexCoord2f(1.f, 1.f);
            glVertex2i(buff[3][0], buff[3][1]);
         glEnd();
         alpha -= 0.03;
      }
   }
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);
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

void PlayerShip::loadTextures()
{
   glGenTextures(3, textures); //gera 3 texturas no vetor textures (GLuint textures[3])
   glBindTexture(GL_TEXTURE_2D, textures[0]); //binda a textura da nave parada (0)
   GLuint flags = GLFW_BUILD_MIPMAPS_BIT | GLFW_ALPHA_MAP_BIT;
   if(glfwLoadTexture2D("mehsw-player-stay.tga", flags) == GL_FALSE) //carrega a textura
      std::cout << "falha ao carregar textura da nave parada" << std::endl;
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //seta o MIN filter
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //set o MAG filter
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); //seta o wrap
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ); 
   
   //as linhas abaixo são basicamente a mesma coisa

   glBindTexture(GL_TEXTURE_2D, textures[1]);   
   if(glfwLoadTexture2D("mehsw-player-acc1.tga", flags) == GL_FALSE)
      std::cout << "falha ao carregar a nave acelerando 1" << std::endl;
   glBindTexture(GL_TEXTURE_2D, textures[1]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );  
   
   glBindTexture(GL_TEXTURE_2D, textures[2]);
   if(glfwLoadTexture2D("mehsw-player-acc2.tga", flags) == GL_FALSE)
      std::cout << "falha ao carregar a nave acelerando 2" << std::endl;
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}

} //namespace game
} //namesace hstefan
