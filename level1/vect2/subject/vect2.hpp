#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
class vect2
{
	public:
		int x;
		int y;
		vect2();
		vect2(int x,int y);
		vect2(vect2 const& v);
		vect2 operator*(int scalar);
		vect2 operator*(int scalar) const;
		vect2 operator+(const vect2 &vct);
		vect2 operator+(const vect2 &vct) const;
		vect2 operator-() const;
		vect2 operator-(const vect2 &vct) const;

		int &operator[](int index);
		int const &operator[](int index) const ;

		vect2 &operator++();
		vect2 operator++(int);
		vect2 &operator--();
		vect2 operator--(int);
		vect2 &operator+=(const vect2 &vct);
		vect2 &operator-=(const vect2 &vct);
		vect2 &operator*=(int scalar);
		bool operator==(const vect2 &v);
		bool operator==(const vect2 &v) const ;
		bool operator!=(const vect2 &v);
		bool operator!=(const vect2 &v) const;
		void operator=(const vect2 &v);
		~vect2();
};

std::ostream &operator<<(std::ostream &out, const vect2 &v);
vect2 operator*(int scalar, vect2 const& v);
#endif