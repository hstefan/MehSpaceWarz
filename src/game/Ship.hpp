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

#include "GameObject.hpp"
#include "../math/vector.hpp"

namespace hstefan
{
namespace game
{

   class Ship : public GameObject
   {
   public:
      Ship(unsigned int lifes, unsigned int hp);

      virtual void update() = 0;
      virtual void render() = 0;
      bool done();
   protected:
      unsigned int lifes;
      unsigned int hp;
      float speed;
      
      math::vec3 dir;
      //geometry
   };

} //namespace game
} //namespace hstefan
