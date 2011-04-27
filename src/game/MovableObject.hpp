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

#ifndef HSTEFAN_MOVABLE_OBJECT_HPP
#define HSTEFAN_MOVABLE_OBJECT_HPP

#include "GameObject.hpp"
#include "../math/vector.hpp"

namespace hstefan
{
namespace game
{

class MovableObject : public GameObject
{
public:
   virtual void update() = 0;
   virtual void render() = 0;

   math::vec2 direction;
   math::vec2 position;
};

} //namespace game
} //namespace hstefan

#endif