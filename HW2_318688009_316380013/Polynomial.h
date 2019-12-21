#pragma once
#include "Monomial.h"
#include "Doubly_List.h"

class Polynomial
{
public:
	Polynomial();
	~Polynomial();

	const Polynomial& operator=(Polynomial const& obj);

	const Polynomial& operator + (Monomial const& obj);
	const Polynomial& operator + (Polynomial const& obj);
	const Polynomial& operator - (Monomial const& obj);
	const Polynomial& operator - (Polynomial const& obj);

	const Polynomial& operator +=(Monomial const& obj);
	const Polynomial& operator +=(Polynomial const& obj);
	const Polynomial& operator -=(Monomial const& obj);
	const Polynomial& operator -=(Polynomial const& obj);

	bool operator==(Polynomial const&) const;
	bool operator!=(Polynomial const&) const;

	Polynomial operator -() const &;
	const double& operator ()(const double r) const;


	friend std::ostream& operator << (std::ostream& out, const Polynomial& p);
	friend std::istream & operator >> (std::istream &in, Polynomial& p);

	//const Monomial &operator[] (int);
	//index function

	void add(const Monomial& monomial);
	void print(std::ostream& outStream = std::cout) const;

private:
	list* polynom;
};
