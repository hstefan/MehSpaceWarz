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

#ifdef __unix__
#include <sys/time.h>
#endif

#ifdef __unix__
struct timespec last_update;
#else
std::clock_t last_update = 0;
#endif

int main(int argc, char* argv[])
{
#ifdef __unix__
   clock_gettime(CLOCK_REALTIME, &last_update);
#else
   last_update = std::clock();
#endif

   glfwInit();
   glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
   glfwOpenWindow(800, 450, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);

   using hstefan::game::GameWorld;

   GameWorld* world = GameWorld::getInstance();

   bool running = true;

   while(running) 
   {
      if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) 
         break;

#ifdef __unix__
      static const double UPDATE_INTERVAL = 1. / 30.;
      static const time_t UPDATE_INTERVAL_SEC = UPDATE_INTERVAL;
      static const unsigned long UPDATE_INTERVAL_NS = (UPDATE_INTERVAL-UPDATE_INTERVAL_SEC) * 1E9;

      struct timespec update_time;
      clock_gettime(CLOCK_REALTIME, &update_time);

      if (update_time.tv_sec - last_update.tv_sec >= UPDATE_INTERVAL_SEC &&
         (unsigned long)update_time.tv_nsec - (unsigned long)last_update.tv_nsec >= UPDATE_INTERVAL_NS)
      {
         world->update();
         clock_gettime(CLOCK_REALTIME, &last_update);
      }
#else
      static const std::clock_t UPDATE_INTERVAL = CLOCKS_PER_SEC / 30;
      world->update();

      if (std::clock() >= last_update + UPDATE_INTERVAL)
      {
         world->render();
         last_update += UPDATE_INTERVAL;
      }
#endif

      glfwSwapBuffers();
      running = glfwGetWindowParam(GLFW_OPENED) != 0;
   }

   glfwTerminate();
}