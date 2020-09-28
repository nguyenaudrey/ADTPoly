/*
* Student: Audrey Nguyen
* Professor: Christopher Esposito
* Assignment #1: Poly
* Description: Header file for a representation of a Polynomial 
*/

#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <string>

using namespace std;

class Poly
{
public:
	// Constructors
	Poly();
	Poly(int coeff);
	Poly(int coeff, int power);
	Poly(const Poly& other);

	// Deconstructor
	~Poly();

	// Subtraction Operators
	Poly operator-(const Poly& other) const;
	Poly& operator-=(const Poly& other);

	// Addition Operators
	Poly operator+(const Poly& other) const;
	Poly& operator+=(const Poly& other);


	// Multiplication Operators
	Poly operator*(const Poly& other) const;
	Poly& operator*=(const Poly& other);

	// Unary Negation Operator
	Poly operator-() const;

	// Equality Operators
	bool operator==(const Poly& other) const;
	bool operator!=(const Poly& other) const;


	// Assignment Overload Operator
	Poly& operator = (const Poly& other);

	// Outstream and Instream Overload
	friend ostream& operator<<(ostream& outStream, const Poly& thisPoly);
	friend istream& operator>>(istream& inStream, Poly& thisPoly);
	
	// Accesor
	int getCoeff(int power) const;

	// Mutator
	void setCoeff(int coeff, int power);

	// Checks if empty
	bool isEmpty() const;

private:
	int* coeffPtr;
	int highestPower;
};

#endif
