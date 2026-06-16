#include "vect2.hpp"
#include <iostream>

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::vect2(const vect2 &v) : x(v.x), y(v.y) {}

vect2 vect2::operator*(int scalar)
{
	return vect2(this->x * scalar, this->y * scalar);
}

vect2 vect2::operator*(int scalar) const
{
	return vect2(this->x * scalar, this->y * scalar);
}

vect2 vect2::operator+(const vect2 &vct)
{
	return vect2(this->x + vct.x, this->y + vct.y);
}

vect2 vect2::operator+(const vect2 &vct) const
{
	return vect2(this->x + vct.x, this->y + vct.y);
}

vect2 vect2::operator-() const
{
	return (vect2(-(this->x), -(this->y)));
}

vect2 vect2::operator-(const vect2 &vct) const
{
	return vect2(this->x - vct.x, this->y - vct.y);
}
int &vect2::operator[](int index)
{
	if (index == 0)
		return this->x;
	return this->y;
}
// int const &vect2::operator[](int index) const
// {
// 	if (index == 0)
// 		return this->x;
// 	return this->y;
// }
vect2 &vect2::operator++()
{
	x++;
	y++;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 tmp = *this;
	this->x++;
	this->y++;
	return tmp;
}

vect2 &vect2::operator--()
{
	x--;
	y--;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 tmp = *this;
	this->x--;
	this->y--;
	return tmp;
}

vect2 &vect2::operator*=(int scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

vect2 &vect2::operator+=(const vect2 &vct)
{
	this->x += vct.x;
	this->y += vct.y;
	return *this;
}

vect2 &vect2::operator-=(const vect2 &vct)
{
	this->x -= vct.x;
	this->y -= vct.y;
	return *this;
}

bool vect2::operator!=(const vect2 &v)
{
	return (this->x != v.x || this->y != v.y);
}

bool vect2::operator!=(const vect2 &v) const
{
	return (this->x != v.x || this->y != v.y);
}

bool vect2::operator==(const vect2 &v)
{
	return (this->x == v.x && this->y == v.y);
}

bool vect2::operator==(const vect2 &v) const
{
	return (this->x == v.x && this->y == v.y);
}

void vect2::operator=(const vect2 &v)
{
	if (this == &v)
		return;
	this->x = v.x;
	this->y = v.y;
}

std::ostream &operator<<(std::ostream &out, const vect2 &v)
{
	out << "{" << v.x << ", " << v.y << "}";
	return out;
}
vect2 operator*(int scalar, vect2 const& v)
{
	return (vect2(scalar * v.x , scalar *v.y));
}
vect2::~vect2() {}
