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

#ifndef HSTEFAN_TRANSFORM_HPP
#define HSTEFAN_TRANSFORM_HPP

#include "vector.hpp"
#include "matrix.hpp"
#include <cmath>

namespace hstefan
{
namespace math
{

inline vec2 RotateClockwise(const vec2& vec, float angle)
{
   mat2d m = { 
      std::cos(angle) , std::sin(angle), 
      -std::sin(angle), std::cos(angle) 
   };

   return m*vec;
}

inline vec2 RotateAntiClockwise(const vec2& vec, float angle)
{
   mat2d m = {
      std::cos(angle), -std::sin(angle), 
      std::sin(angle),  std::cos(angle)
   };

   return m*vec;
}

} //namespace math
} //namespace hstefan
#endif