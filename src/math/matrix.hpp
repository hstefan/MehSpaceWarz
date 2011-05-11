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
/*
 * Nome: Hugo Stefan Kaus Puhlmann
 * Matricula: 2910182
 */
#ifndef HSTEFAN_MATRIX_HPP
#define HSTEFAN_MATRIX_HPP

namespace hstefan
{
namespace math
{
template <unsigned int M, unsigned int N = M>
struct matrix;

typedef matrix<4> mat4d;
typedef matrix<3> mat3d;
typedef matrix<2> mat2d;

template <unsigned int M, unsigned int N>
struct matrix
{
public:
   inline void operator+=(const matrix& m)
   {
      for(unsigned int i = 0; i < M*N; i++)
      {
         data[i] += m.data[i];
      }
   }

   inline void operator-=(const matrix& m)
   {
      for(unsigned int i = 0; i < M*N; i++)
      {
         data[i] -= m.data[i];
      }
   }

   inline void operator*=(float f)
   {
      for(unsigned int i = 0; i < M*N; i++)
      {
         data[i] *= f; 
      }
   }

   inline void operator/=(float f)
   {
      for(unsigned int i = 0; i < M*N; i++)
      {
         data[i] /= f;
      }
   }

   inline matrix operator-(const matrix& m) const
   {
      matrix f;

      for(unsigned int i = 0; i < M*N; i++)
      {
         f.data[i] = data[i] - m.data[i];
      }

      return f;
   }

   inline matrix operator+(const matrix& m) const
   {
      matrix f;

      for(unsigned int i = 0; i < M*N; i++)
      {
         f.data[i] = data[i] - m.data[i];
      }

      return f;
   }

   inline matrix operator/(float val) const
   {
      matrix f;

      for(unsigned int i = 0; i < M*N; i++)
      {
         f.data[i] = data[i] / val;
      }

      return f;
   }

   inline matrix operator*(float val) const
   {
      matrix f;

      for(unsigned int i = 0; i < M*N; i++)
      {
         f.data[i] = data[i] * val;
      }

      return f;
   }

   inline float& operator()(int l, int c)
   {
      return data[N*l + c];
   }

   inline const float& operator()(int l, int c) const
   {
      return data[N*l + c];
   }

   float& operator[](int i)
   {
      return data[i];
   }

   const float& operator[](int i) const
   {
      return data[i];
   }

   float data[N*M];
};

template <unsigned int M, unsigned int N, unsigned int P>
matrix<M,P> operator*(const matrix<M, N>& m1, const matrix<N, P>& m2)
{
   matrix<M, P> res;

   for(unsigned int i = 0; i < M; ++i)
   {
      for(unsigned int j = 0; j < P; ++j)
      {
         res(i, j) = 0;
         for (unsigned int k = 0; k < N; ++k) 
            res(i, j) += m1(i, k) * m2(k, j);
      }
   }

   return res;
}
} //namespace base
} //namespace hstefan

#endif
