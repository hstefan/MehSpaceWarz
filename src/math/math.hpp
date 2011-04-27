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