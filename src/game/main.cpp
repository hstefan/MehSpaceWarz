/*
 *   Copyright (C) 2011 by Hugo Stefan Kaus Puhmann
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 */


#include <GL/glfw.h>
#include "GameWorld.hpp"
#include <ctime>
#include <cstdlib>


int main(int argc, char* argv[])
{
   glfwInit();
   glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
   glfwOpenWindow(800, 450, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);

   using hstefan::game::GameWorld;

   GameWorld* world = GameWorld::getInstance();

   bool running = true;

   double last_render = 0;
   double last_update = 0;

   double frame_interval = 1.f/60.f;
   double update_interval = 1.f/90.f;

   double cur_time = 0;

   while(running) 
   {
      cur_time = glfwGetTime();
      if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) 
         break;
      if(cur_time - last_render > frame_interval) 
      {
         last_render = glfwGetTime();
         world->render();
      }
      
     
      if(cur_time - last_update > update_interval)
      {
         world->update();
         last_update = glfwGetTime();
      }

      glfwSleep(update_interval - (cur_time + glfwGetTime()));
      glfwSwapBuffers();
      running = glfwGetWindowParam(GLFW_OPENED) != 0;
   }

   glfwTerminate();
}