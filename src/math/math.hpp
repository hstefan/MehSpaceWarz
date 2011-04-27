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

#ifndef HSTEFAN_MATH_HPP
#define HSTEFAN_MATH_HPP

namespace hstefan
{
namespace math
{

float invSqrt(float x)
{
   float xhalf = 0.5f*x;
   int i = *(int*)&x;
   i = 0x5f3759df - (i>>1);
   x = *(float*)&i;
   x = x*(1.5f - xhalf*x*x);
   return x;
}

} //namespace math
} //namespace hstefan

#endif