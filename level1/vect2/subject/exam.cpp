#include "vect2.hpp"

vect2::vect2()
{
    x = 0;
    y = 0;
}

vect2::vect2(int x , int y)
{
    this->x = x;
    this->y = y;
}

vect2::vect2(const vect2 &other)
{
    this->x = other.x;
    this->y = other.y;
}

vect2 &vect2::operator=(const vect2 &other)
{
    if (*this != other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}
int &vect2::operator[](int index)
{
    if (index == 0)
        return x;
    return y;
}
int vect2::operator[](int index) const
{
    if (index == 0)
        return x;
    return y;
}
std::ostream &operator<<(std::ostream &os,vect2 v)
{
    os << "{" << v[0] << ", " << v[1] << "}";
    return os;
}
vect2 operator*(const vect2 v , int a)
{
    return (vect2(v.x * a , v.y * a));
}
vect2 operator*(int a , vect2 v)
{
    return (vect2(v.x * a , v.y * a));
}
vect2 &vect2::operator++()
{
    (this->x)++;
    (this->y)++;
    return *this;
}
vect2 vect2::operator++(int)
{
    vect2 tmp = *this;
    (this->x)++;
    (this->y)++;
    return tmp;
}

vect2 &vect2::operator--()
{
    (this->x)--;
    (this->y)--;
    return *this;
}
vect2 vect2::operator--(int)
{
    vect2 tmp = *this;
    (this->x)--;
    (this->y)--;
    return tmp;
}

vect2 &vect2::operator+=(const vect2 v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

vect2 &vect2::operator-=(const vect2 v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}
vect2 &vect2::operator*=(int a)
{
    this->x *= a;
    this->y *= a;
    return *this;
}
vect2 vect2::operator-(const vect2 v)
{
    return (vect2(this->x - v.x , this->y - v.y));
}

vect2 vect2::operator+(vect2 v)
{
    return (vect2(this->x + v.x , this->y + v.y));
}
vect2 vect2::operator+(const vect2 v) const
{
    return (vect2(this->x + v.x , this->y + v.y));
}

vect2 vect2::operator*(const vect2 v)
{
    return (vect2(this->x * v.x , this->y * v.y));
}

vect2 &vect2::operator-()
{
    this->x = -(this->x);
    this->y = -(this->y);
    return *this;
}

bool vect2::operator==(const vect2 v)
{
    return (this->x == v.x && this->y == v.y);
}

bool vect2::operator!=(const vect2 v)
{
    return (this->x != v.x || this->y != v.y);
}