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

#ifndef HSTEFAN_GAMEWORLD_HPP
#define HSTEFAN_GAMEWORLD_HPP

namespace hstefan
{

namespace game
{

class GameWorld
{
public:
   static GameWorld* getInstance()
   {
      return _instance;
   }

   void update();
   void render();

private:
   GameWorld() 
   {}
   GameWorld(const GameWorld& game);
   GameWorld& operator=(const GameWorld& game);

   static GameWorld* _instance;
};

} //namespace game
} //namespace hstefan

#endif