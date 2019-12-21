#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
#include <vector>
#include "Polynomial.h"
#include "Doubly_List.h"

using namespace std;

Polynomial::Polynomial()
{
	polynom = new list;
	initList(polynom);
}

Polynomial::~Polynomial()
{
	clear();
	delete polynom;
}

const Polynomial& Polynomial::operator=(Polynomial const& obj)
{
	Polynomial* newPoly = new Polynomial();

	node* pointer = obj.polynom->head;

	while (pointer)
	{
		newPoly->add(*(pointer->value));
		pointer = pointer->next;
	}

	return *newPoly;
}

const Polynomial& Polynomial::operator+(Monomial const& obj)
{
	Polynomial* result = new Polynomial();
	node* pointer = polynom->head;
	bool isMonoAdded = false;
	while (pointer)
	{
		if (!isMonoAdded && obj.getDegree() > pointer->value->getDegree()) {
			result->add(obj);
			isMonoAdded = true;
		}
		if (pointer->value->getDegree() == obj.getDegree())
		{
			Monomial temp = *pointer->value + obj;
			result->add(temp);
			isMonoAdded = true;
		}
		else {
			result->add(*pointer->value);
		}

		if (pointer)
		{
			pointer = pointer->next;
		}
	}
	if (!isMonoAdded) result->add(obj);

	return *result;
}

const Polynomial& Polynomial::operator+(Polynomial const& obj)
{
	Polynomial* result = new Polynomial();

	node* pointerLocal = polynom->head;
	node* pointerParam = obj.polynom->head;
	bool isLocalCanGoForward = false;
	bool isParamCanGoForward = false;

	while (pointerLocal && pointerParam)
	{
		//make pointerLocal go forward
		if (pointerLocal->value->getDegree() > pointerParam->value->getDegree())
		{
			isLocalCanGoForward = true;
			isParamCanGoForward = false;
		}
		//make pointerParam go forward
		if (pointerLocal->value->getDegree() < pointerParam->value->getDegree())
		{
			isLocalCanGoForward = false;
			isParamCanGoForward = true;
		}
		//same degree -> add
		if (pointerLocal->value->getDegree() == pointerParam->value->getDegree())
		{
			Monomial temp = *pointerLocal->value + *pointerParam->value;
			result->add(temp);
			isLocalCanGoForward = true;
			isParamCanGoForward = true;
		}

		if (pointerLocal && isLocalCanGoForward)
			pointerLocal = pointerLocal->next;
		if (pointerParam && isParamCanGoForward)
			pointerParam = pointerParam->next;
	}

	if (pointerLocal)
		while (pointerLocal)
		{
			result->add(*pointerLocal->value);
			if (pointerLocal)
				pointerLocal = pointerLocal->next;
		}

	if (pointerParam)
		while (pointerParam)
		{
			result->add(*pointerParam->value);
			if (pointerParam)
				pointerParam = pointerParam->next;
		}
	return *result;
}

const Polynomial& Polynomial::operator-(Monomial const& obj)
{
	Polynomial* result = new Polynomial();
	node* pointer = polynom->head;
	bool isMonoAdded = false;
	while (pointer)
	{
		if (!isMonoAdded && pointer->value->getDegree() < obj.getDegree())
		{
			result->add(-obj);
			isMonoAdded = true;
		}
		if (pointer->value->getDegree() == obj.getDegree())
		{
			if ((*pointer->value - obj).getCoefficient() != 0) {
				Monomial temp = *pointer->value - obj;
				result->add(temp);
			}
			isMonoAdded = true;
		}
		else {
			result->add(*pointer->value);
		}

		if (pointer)
		{
			pointer = pointer->next;
		}
	}

	if (!isMonoAdded) result->add(obj);
	if (result->polynom->head == NULL)
		result->add(0);

	return *result;
}

const Polynomial& Polynomial::operator-(Polynomial const& obj)
{
	Polynomial* result = new Polynomial();
	node* pointerLocal = polynom->head;
	node* pointerParam = obj.polynom->head;
	bool isLocalCanGoForward = false;
	bool isParamCanGoForward = false;

	while (pointerLocal && pointerParam)
	{
		if (pointerLocal->value->getDegree() > pointerParam->value->getDegree())
		{
			isLocalCanGoForward = true;
			isParamCanGoForward = false;
		}
		if (pointerLocal->value->getDegree() < pointerParam->value->getDegree())
		{
			isLocalCanGoForward = false;
			isParamCanGoForward = true;
		}
		if (pointerLocal->value->getDegree() == pointerParam->value->getDegree())
		{
			if ((*pointerLocal->value - *pointerParam->value).getCoefficient() != 0) {
				Monomial temp = *pointerLocal->value - *pointerParam->value;
				result->add(temp);
			}

			isLocalCanGoForward = true;
			isParamCanGoForward = true;
		}
		if (pointerLocal && isLocalCanGoForward)
		{
			pointerLocal = pointerLocal->next;
		}
		if (pointerParam && isParamCanGoForward)
		{
			pointerParam = pointerParam->next;
		}
	}

	if (pointerLocal)
		while (pointerLocal)
		{
			result->add(*pointerLocal->value);
			if (pointerLocal)
				pointerLocal = pointerLocal->next;
		}

	if (pointerParam)
		while (pointerParam)
		{
			result->add(*pointerParam->value);
			if (pointerParam)
				pointerParam = pointerParam->next;
		}

	if (result->polynom->head == NULL)
		result->add(0);

	return *result;
}

void Polynomial::add(const Monomial& monomial)
{
	node* pointer = polynom->head;
	node* temp = NULL;
	bool isAddFinished = (monomial.getCoefficient() == 0);

	while (pointer && !isAddFinished)
	{
		// check if there is already monom with the same degree in the polynom
		if (pointer->value->getDegree() == monomial.getDegree())
		{
			if (pointer->value->getCoefficient() + monomial.getCoefficient() == 0)
			{
				temp = pointer->next;
				deleteLink(polynom, pointer);
				pointer = temp;
			}
			else
				pointer->value->setCoefficient(pointer->value->getCoefficient() + monomial.getCoefficient());

			isAddFinished = true;
		}
		if (pointer)
		{
			pointer = pointer->next;
		}
	}

	if (!isAddFinished)
	{
		node* n = allocItem(monomial);
		//insertFirst(polynom, n); // to HW1
		insertLast(polynom, n);	// to HW2
	}
}

void Polynomial::print(std::ostream& outStream) const
{
	node* pointer = this->polynom->head;

	if (pointer == NULL)
	{
		std::cout << "0";
	}
	else
	{
		pointer->value->print();
		pointer = pointer->next;

		while (pointer)
		{
			std::cout << ((pointer->value->getCoefficient() >= 0) ? "+" : "");

			pointer->value->print();
			pointer = pointer->next;
		}
	}
}

void Polynomial::clear() const
{
	while (!isEmpty(polynom))
	{
		deleteLast(polynom);
	}
}

size_t Polynomial::size() const
{
	return length(polynom);
}

std::ostream& operator<<(std::ostream& out, const Polynomial& p)
{
	//todo: check if concatanating couts works here

	p.print(out);
	return out;
}

std::istream & operator>>(std::istream & in, Polynomial& p)
{
	p.clear();

	string tempStr;
	std::getline(in, tempStr);

	tempStr = tempStr.substr(0, tempStr.size() - 1); // excluding ","
	
	std::replace(tempStr.begin(), tempStr.end(), '+', ' ');	// replace '+' by ' '

	tempStr = std::regex_replace(tempStr, std::regex("-"), " -");	// replace '-' by " -"

	Monomial tempMonom;
	string splitedStr;

	size_t pos = tempStr.find(' ');
	while (pos != string::npos)
	{
		splitedStr = tempStr.substr(0, pos);
		tempStr = tempStr.substr(pos+1, tempStr.size()-(pos+1));

		stringstream ss;
		ss.str(splitedStr);
		ss >> tempMonom;

		p.add(tempMonom);
		pos = tempStr.find(' ');
	}

	if (!tempStr.empty())
	{
		stringstream ss;
		ss.str(tempStr);
		ss >> tempMonom;

		p.add(tempMonom);
	}
	
	///todo: validation?

	return in;
}

const Polynomial& Polynomial::operator +=(Monomial const& obj)
{
	this->add(obj);
	return *this;
}

const Polynomial& Polynomial::operator+=(Polynomial const& obj)
{
	node* pointerParam = obj.polynom->head;
	while (pointerParam)
	{
		this->add(*pointerParam->value);

		if (pointerParam)
		{
			pointerParam = pointerParam->next;
		}
	}
	return *this;
}

const Polynomial& Polynomial::operator-=(Monomial const& obj)
{
	this->add(-obj);
	return *this;
}

const Polynomial& Polynomial::operator-=(Polynomial const& obj)
{
	node* pointerParam = obj.polynom->head;
	while (pointerParam)
	{
		this->add(-*pointerParam->value);

		if (pointerParam)
		{
			pointerParam = pointerParam->next;
		}
	}
	return *this;
}

bool Polynomial::operator==(Polynomial const& obj) const
{
	node* pointerLocal = polynom->head;
	node* pointerParam = obj.polynom->head;

	while (pointerLocal && pointerParam)
	{
		if (pointerLocal->value->getDegree() != pointerParam->value->getDegree())
			return false;

		if (pointerLocal->value->getCoefficient() != pointerParam->value->getCoefficient())
			return false;


		if (pointerLocal && pointerParam)
		{
			pointerLocal = pointerLocal->next;
			pointerParam = pointerParam->next;
		}
		else
			return false;
	}

	//if (pointerLocal)
	//	return false;

	//if (pointerParam)
	//	return false;

	return true;
}

bool Polynomial::operator!=(Polynomial const& obj) const
{
	node* pointerLocal = polynom->head;
	node* pointerParam = obj.polynom->head;

	while (pointerLocal && pointerParam)
	{
		if (pointerLocal->value->getDegree() != pointerParam->value->getDegree())
			return true;

		if (pointerLocal->value->getCoefficient() != pointerParam->value->getCoefficient())
			return true;

		if (pointerLocal && pointerParam)
		{
			pointerLocal = pointerLocal->next;
			pointerParam = pointerParam->next;
		}
		else
			return true;
	}
	return false;
}

bool Polynomial::operator==(Monomial const& obj) const
{
	//  notice that the implementaion defines that empty polynom is equal to Monomial(0)
	if ((size() == 0 && obj == Monomial(0)) || ((size() == 1) && (obj == *(polynom->head->value))))
		return true;

	return false;
}

bool Polynomial::operator!=(Monomial const& obj) const
{
	return !(*this == obj);
}

Polynomial Polynomial::operator-() const &
{
	Polynomial result;
	node* pointerLocal = polynom->head;

	while (pointerLocal)
	{
		result.add(-*pointerLocal->value);
		if (pointerLocal)
			pointerLocal = pointerLocal->next;
	}
	return result;
}

const double Polynomial::operator()(const double r) const
{
	double result = 0;
	node* pointerLocal = polynom->head;

	while (pointerLocal)
	{
		Monomial temp = *pointerLocal->value;
		result += temp(r);

		if (pointerLocal)
			pointerLocal = pointerLocal->next;
	}
	return result;
}

const double Polynomial::operator[](const unsigned int d) const
{
	node* pointer = this->polynom->head;

	while (pointer)
	{
		if (pointer->value->getDegree() == d)
			return pointer->value->getCoefficient();

		pointer = pointer->next;
	}

	return 0;
}

//double& Polynomial::operator[](const unsigned int d)
//{
//	node* pointer = this->polynom->head;
//
//	while (pointer)
//	{
//		if (pointer->value->getDegree() == d)
//			return *(pointer->value);
//
//		pointer = pointer->next;
//	}
//
//	return 0;	// what happen if there is no monom with degree d?
//}