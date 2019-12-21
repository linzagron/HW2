#include "Monomial.h"
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int Monomial::monomialCounter = 0;

Monomial::Monomial() :degree(0)
{
	coefficient = 1;
	monomialCounter++;
}

Monomial::Monomial(const double coefficient) :degree(0)
{
	this->coefficient = coefficient;
	monomialCounter++;
}

Monomial::Monomial(const double coefficient, const unsigned int degree) :degree(degree)
{
	this->coefficient = coefficient;
	monomialCounter++;
}

Monomial::Monomial(const Monomial& monomial) :degree(monomial.getDegree())
{
	coefficient = monomial.getCoefficient();
	monomialCounter++;
}

double Monomial::getCoefficient() const
{
	return this->coefficient;
}

void Monomial::setCoefficient(double c)
{
	this->coefficient = c;
}

unsigned int Monomial::getDegree() const
{
	return this->degree;
}

void Monomial::setDegree(const unsigned int degree)
{
	this->degree = degree;
}

bool Monomial::add(const Monomial& monomialToAdd)
{
	if (monomialToAdd.getDegree() != this->getDegree())
		return false;

	this->coefficient += monomialToAdd.getCoefficient();
	return true;
}

int Monomial::getNumberOfMonomials()
{
	return monomialCounter;
}

const Monomial Monomial::operator=(Monomial const& obj)
{
	this->setCoefficient(obj.getCoefficient());
	this->setDegree(obj.getDegree());

	return *this;
}

const Monomial Monomial::operator+(Monomial const& obj) const
{
	if (this->getDegree() != obj.getDegree()) return *this;

	Monomial result;
	result.setCoefficient(this->getCoefficient() + obj.getCoefficient());
	result.setDegree(this->getDegree());

	return result;
}
// todo: add ref
const Monomial Monomial::operator-(Monomial const& obj) const
{
	if (this->getDegree() != obj.getDegree()) return *this;

	Monomial result;
	result.setCoefficient(this->getCoefficient() - obj.getCoefficient());
	result.setDegree(this->getDegree());

	return result;
}
// todo: add ref
const Monomial Monomial::operator*(Monomial const& obj) const
{
	Monomial result;

	result.setCoefficient(this->getCoefficient() * obj.getCoefficient());
	result.setDegree(this->getDegree() + obj.getDegree());

	return result;
}

bool Monomial::operator==(Monomial const& m) const
{
	return this->getCoefficient() == m.getCoefficient() &&
		this->getDegree() == m.getDegree();
}

bool Monomial::operator!=(Monomial const& m) const
{
	return !(*this == m);
}

const Monomial& Monomial::operator+=(const Monomial& obj)
{
	if (this->getDegree() == obj.getDegree())
		this->setCoefficient(this->getCoefficient() + obj.getCoefficient());

	return *this;
}

const Monomial& Monomial::operator*=(const Monomial& obj)
{
	this->setCoefficient(this->getCoefficient() * obj.getCoefficient());
	this->setDegree(this->getDegree() + obj.getDegree());

	return *this;
}

const Monomial& Monomial::operator-=(const Monomial& obj)
{
	if (this->getDegree() == obj.getDegree())
		this->setCoefficient(this->getCoefficient() - obj.getCoefficient());

	return *this;
}

Monomial Monomial::operator-() const &
{
	Monomial result;

	result.setDegree(this->getDegree());
	result.setCoefficient(-1 * this->getCoefficient());

	return result;
}

const double& Monomial::operator()(const double r) const
{
	return (this->getCoefficient() * pow(r, this->getDegree()));
}

void Monomial::print(std::ostream &outStream) const
{
	if (this->getCoefficient() == 0)
	{
		outStream << 0;
	}
	else
	{
		if (this->getDegree() == 0)
		{
			outStream << this->getCoefficient();
		}
		else
		{
			if (this->getDegree() == 1)
			{
				(this->getCoefficient() == 1) ? outStream << "x"
					: outStream << this->getCoefficient() << "*x";
			}
			else if (this->getDegree() > 1)
			{
				(this->getCoefficient() == 1) ? outStream << "x^" << this->getDegree()
					: outStream << this->getCoefficient() << "*x^" << this->getDegree();
			}
		}
	}
}

Monomial::~Monomial()
{
	monomialCounter--;
}

ostream& operator<<(ostream& out, const Monomial& m)
{
	//todo: check if concatanating couts works here

	m.print(out);
	return out;
}

istream& operator>>(istream& in, Monomial& m)
{
	string tempStr;
	std::getline(in, tempStr);

	char charsToRemove[] = "^ "; // ignore this characters

	for (unsigned int i = 0; i < strlen(charsToRemove); ++i)
			tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), charsToRemove[i]), tempStr.end());
		
	size_t pos = tempStr.find("x");
	if (pos == string::npos)
	{
		m.coefficient = atoi(tempStr.c_str());
		m.degree = 0;
	}
	else
	{
		m.coefficient = atoi(tempStr.substr(0, pos).c_str());
		m.degree = (pos == tempStr.size() - 1) ? 1 : atoi(tempStr.substr(pos + 1, tempStr.size() - (pos + 1)).c_str());
	}

	///todo: validation?

	return in;
}
