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
/*
 * Nome: Hugo Stefan Kaus Puhlmann
 * Matricula: 2910182
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
//deprecated
inline vec2 rotateClockwise(const vec2& vec, float angle)
{
   mat2d m = {{ 
      std::cos(angle) , std::sin(angle), 
      -std::sin(angle), std::cos(angle) 
   }};

   return m*vec;
}

//deprecated
inline vec2 rotateAntiClockwise(const vec2& vec, float angle)
{
   mat2d m = {{
      std::cos(angle), -std::sin(angle), 
      std::sin(angle),  std::cos(angle)
   }};

   return m*vec;
}

inline mat3d rotMat2dh(float angle)
{ 
   mat3d m = {{
      std::cos(angle), -std::sin(angle), 0,
      std::sin(angle), std::cos(angle) , 0,
      0              , 0,                1
   }};

   return m;
}

inline mat3d scaleMat2dh(float sx, float sy)
{ 
   mat3d m = {{
      sx, 0 , 0,
      0 , sy, 0,
      0 , 0 , 1
   }};

   return m;
}

inline mat3d transMat2dh(float tx, float ty)
{
   mat3d m = {{
      1, 0, tx,
      0, 1, ty,
      0, 0, 1
   }};

   return m;
}

} //namespace math
} //namespace hstefan
#endif
