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

#ifndef HSTEFAN_VECTOR_HPP
#define HSTEFAN_VECTOR_HPP

#include "matrix.hpp"
#include "math.hpp"
#include <cmath>
#include <ostream>

namespace hstefan
{
namespace math
{
typedef matrix<4, 1> vec4;
typedef matrix<3, 1> vec3;
typedef matrix<2, 1> vec2;

template<unsigned int N>
float dot(const matrix<N, 1>& v1, const matrix<N, 1>& v2)
{
   float ret = 0;
   for(unsigned int i = 0; i < N; i++)
   {
      ret += v1.data[i] * v2.data[i];
   }
   return ret;
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
   vec3 res = {{
      v1[1]*v2[2] - v2[1]*v1[2],
         v1[2]*v2[0] - v2[2]*v1[0],
         v1[1]*v2[0] - v2[1]*v1[0] 
   }};

   return res;
}

template<unsigned int N>
float norm(const matrix<N, 1>& vec)
{
   float acc = 0;

   for(unsigned int i = 0; i < N; ++i)
      acc += vec[i] * vec[i];

   return std::sqrt(acc);
}

template<unsigned int N>
matrix<N, 1>& normalize(matrix<N, 1>& vec)
{
   float s = 0;
   for(unsigned int i = 0; i < N; ++i)
      s += vec[i] * vec[i];
   vec *= math::invSqrt(s);
   return vec;
}

template<unsigned int N>
matrix<N, 1> unit(matrix<N, 1>& vec)
{
   float s = 0;
   for(unsigned int i = 0; i < N; ++i)
      s += vec[i] * vec[i];
   return vec * math::invSqrt(s);
}

inline char quadrant(const vec2& vec)
{
   char quad = 1;
   if(vec[0] < 0 && vec[1] > 0)
      quad = 2;
   else if (vec[0] < 0 && vec[1] < 0)
      quad = 3;
   else if (vec[0] > 0 && vec[1] < 0)
      quad = 4;
   return quad;
}

} //namespace math
} //namespace hstefan
#ifdef _DEBUG
template <unsigned int M, unsigned int N>
std::ostream& operator<<(std::ostream& out, const hstefan::math::matrix<M, N>& m)
{
	out << "(";
	for(unsigned int i = 0; i < M; ++i)
	{
		out << m[i];
		if(i + 1 == M)
			out << ")";
		else
			out << ",";
	}

	return out;
}
#endif

#endif
