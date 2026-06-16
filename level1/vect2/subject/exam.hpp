#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
class vect2
{
    private:
        int x;
        int y;
    public:
        vect2();
        vect2(int x, int y);
        vect2(const vect2 &other);
        vect2 &operator=(const vect2 &other);
        int &operator[](int index);
        int operator[](int index) const;
        vect2 &operator++();
        vect2 operator++(int);
        vect2 &operator--();
        vect2 operator--(int);

        vect2 &operator+=(const vect2 v);
        vect2 &operator-=(const vect2 v);
        vect2 &operator*=(int a);

        vect2 operator-(const vect2 v);
        vect2 operator+(vect2 v);
        vect2 operator+(const vect2 v) const ;
        vect2 operator*(const vect2 v);

        vect2 &operator-();

        bool operator==(const vect2 v);

        bool operator!=(const vect2 v);
        friend std::ostream &operator<<(std::ostream &os,vect2 v);
        friend vect2 operator*(const vect2 v , int a);
        friend vect2 operator*(int a , vect2 v);
};
#endif