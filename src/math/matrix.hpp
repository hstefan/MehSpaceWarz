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

	inline matrix operator-(const matrix& m)
	{
		matrix f;

		for(unsigned int i = 0; i < M*N; i++)
		{
			f.data[i] = data[i] - m.data[i];
		}

		return f;
	}

	inline matrix operator+(const matrix& m)
	{
		matrix f;

		for(unsigned int i = 0; i < M*N; i++)
		{
			f.data[i] = data[i] - m.data[i];
		}

		return f;
	}

	inline matrix operator/(float val)
	{
		matrix f;

		for(unsigned int i = 0; i < M*N; i++)
		{
			f.data[i] = data[i] / val;
		}

		return f;
	}

	inline matrix operator*(float val)
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