//exam valid bigint

#ifndef EXM_HPP
#define EXM_HPP

#include <iostream>
#include <string>
class bigint
{
	private:
		std::string nbr;
	public:
		bigint(){
			this->nbr = "0";
		}
		bigint(size_t nbr)
		{
			this->nbr = std::to_string(nbr);
		}
		bigint(std::string nbr)
		{
			this->nbr = nbr;
		}
		friend std::ostream &operator<<(std::ostream &os,const bigint a)
		{
			return os << a.nbr;
		}
		std::string add_strings(const std::string s1 , const std::string s2) const
		{
			std::string result;
			int a =0, b =0;
			int carry = 0;
			int size1 = s1.size() - 1;
			int size2 = s2.size() - 1;
			while (size1 >= 0 || size2 >= 0 || carry)
			{
				if (size1 >= 0)
					a = s1[size1] - '0';
				else
					a = 0;
				if (size2 >= 0)
					b = s2[size2] - '0';
				else
					b = 0;
				int sum = a + b + carry;
				result.push_back(sum % 10 + '0');
				carry = sum / 10;
				size1--;
				size2--;
			}
			std::reverse(result.begin(),result.end());
			return result;
		}
		//Opérateurs d'addition
		bigint operator+(const bigint b) const
		{
			return (bigint(add_strings(this->nbr,b.nbr)));
		}
		bigint &operator+=(const bigint b)
		{
			*this = add_strings(this->nbr , b.nbr);
			return *this;
		}
		bigint &operator++() //++x
		{
			*this = add_strings(this->nbr,"1");
			return *this;
		}
		bigint operator++(int) //x++
		{
			bigint tmp = *this;
			++(*this);
			return tmp;
		}

		//Opérateurs de décalage (shift décimal)
		bigint operator<<(const int sh)
		{
			if (this->nbr == "0")
				return (*this);
			return bigint(this->nbr + std::string(sh,'0'));
		}
		bigint &operator<<=(const int sh)
		{
			if (this->nbr == "0")
				return (*this);
			this->nbr += std::string(sh,'0');
			return (*this);
		}
		bool operator<(const bigint& b) const
		{
			if (this->nbr.size() < b.nbr.size())
				return (true);
			else if (this->nbr.size() > b.nbr.size())
				return (false);
			return (this->nbr < b.nbr);
		}
		bool operator>(const bigint& b) const
		{
			return (b < *this);
		}
		bool operator==(const bigint& b) const
		{
			return (b.nbr == this->nbr);
		}
		bool operator!=(const bigint& b) const
		{
			return (b.nbr != this->nbr);
		}
		bool operator<=(const bigint& b) const
		{
			return !(*this > b);
		}
		bool operator>=(const bigint& b) const
		{
			return !(*this < b);
		}
		bigint operator-(const bigint b) const
		{
			(void)b;
			return bigint("0");
		}
		bigint &operator>>=(const bigint &sh)
		{
			if (sh >= bigint(this->nbr.size()))
				nbr = "0";
			bigint i(0);
			while (i < sh)
			{
				nbr = nbr.substr(0,nbr.size() -1);
				i++;
			}
			return *this;
		}

};

#endif