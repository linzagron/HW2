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
	bool operator==(Monomial const& obj) const;
	bool operator!=(Monomial const& obj) const;

	Polynomial operator -() const &;
	const double operator()(const double r) const;
	const double operator[](const unsigned int d) const;
	//const double operator[](const unsigned int d);

	//Monomial& operator[] = (const unsigned int d) const;	//index function
	//Monomial& operator[](const unsigned int d) const;	//index function

	friend std::ostream& operator << (std::ostream& out, const Polynomial& p);
	friend std::istream & operator >> (std::istream &in, Polynomial& p);

	void add(const Monomial& monomial);
	void print(std::ostream& outStream = std::cout) const;
	void clear() const;
	size_t size() const;

private:
	list* polynom;
};