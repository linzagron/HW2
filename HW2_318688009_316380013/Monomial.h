#pragma once
#include <iostream>
#include <string>

class Monomial
{
public:
	Monomial();
	Monomial(const double coefficient);
	Monomial(const double coefficient, const unsigned int degree);
	Monomial(const Monomial& monomial);
	~Monomial();

	double getCoefficient() const;
	void setCoefficient(const double c);
	unsigned int getDegree() const;
	void setDegree(const unsigned int degree);
	static int getNumberOfMonomials();

	const Monomial operator = (Monomial const& obj);
	const Monomial operator + (Monomial const& obj) const;
	const Monomial operator - (Monomial const& obj) const;
	const Monomial operator * (Monomial const& obj) const;

	bool operator==(Monomial const&) const;
	bool operator!=(Monomial const&) const;

	const Monomial& operator +=(const Monomial& obj);
	const Monomial& operator *=(const Monomial& obj);
	const Monomial& operator -=(const Monomial& obj);

	Monomial operator -() const &;
	const double& operator ()(const double r) const;

	friend std::ostream& operator << (std::ostream& out, const Monomial& m);
	friend std::istream& operator >> (std::istream& in, Monomial& m);

	bool add(const Monomial& monomialToAdd);

	void print(std::ostream& outStream = std::cout) const;

private:
	static int monomialCounter;
	double coefficient;
	unsigned int degree;
};
