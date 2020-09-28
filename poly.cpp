/*
* Student: Audrey Nguyen
* Professor: Christopher Esposito
* Assignment #1: Poly
* Description: Cpp file for a representation of a Polynomial
*/

#include "poly.h"

// Default constructor
Poly::Poly()
{
	coeffPtr = new int[1];
	coeffPtr[0] = 0;
	highestPower = 0;
}

// Constructor that takes one integer
Poly::Poly(int coeff)
{
	coeffPtr = new int[1];
	coeffPtr[0] = coeff;
	highestPower = 0;
}

// Constructor that takes two integers
Poly::Poly(int coeff, int power)
{
	coeffPtr = new int[power+1];
	coeffPtr[power] = coeff;
	highestPower = power;

	for (int i = 0; i < power; i++)
	{
		coeffPtr[i] = 0;
	}
}

// Copy Constructor
Poly::Poly(const Poly& other)
{
	highestPower = other.highestPower;
	coeffPtr = new int[other.highestPower+1];
	
	for (int i = 0; i < other.highestPower + 1; i++)
	{
		coeffPtr[i] = other.coeffPtr[i];
	}
}

// Deconstructor
Poly::~Poly()
{
	delete[] coeffPtr;
	highestPower = 0;
}

// Overloaded subtraction operator
Poly Poly::operator-(const Poly& other) const
{
	Poly newPoly(*this);
	newPoly -= other;
	return newPoly;
}

// Overloaded minus-equals operator 
Poly& Poly::operator-=(const Poly& other)
{
	// Checks if the highest power of left hand side is greater than the right hand side
	if (highestPower >= other.highestPower)
	{
		// Subtracts the right hand side from the left hand side
		for (int i = 0; i < other.highestPower + 1; i++)
		{
			coeffPtr[i] = coeffPtr[i] - other.coeffPtr[i];
		}

		// Checks if the highest power is equal to 0 and the highest power isn't currentley 0
		if ((coeffPtr[highestPower] == 0) && (highestPower != 0))
		{
			// Finds the new highest power
			while ((coeffPtr[highestPower] == 0) && (highestPower != 0))
			{
				highestPower--;
			}
			
			// Dynamically resizes coeffPtr to match the new highest power
			int* newPoly = new int[highestPower + 1];
			for (int i = 0; i < highestPower + 1; i++)
			{
				newPoly[i] = coeffPtr[i];
			}

			delete[] coeffPtr;
			coeffPtr = newPoly;
		}
	}

	// Otherwise the highest power is now from the right hand side
	// Dynamically resizes the array to match the new highest power 
	// Also simaltaneously subtracts the right hand side from the left hand side
	else
	{
		int* newPoly = new int[other.highestPower + 1];
		for (int i = 0; i < other.highestPower + 1; i++)
		{
			newPoly[i] = -other.coeffPtr[i];
			
			if (i < highestPower + 1)
			{
				newPoly[i] = newPoly[i] + coeffPtr[i];
			}
		}
	
		delete[] coeffPtr;
		coeffPtr = newPoly;
		highestPower = other.highestPower;
	}

	return *this;
}

// Overloaded addition operator
Poly Poly::operator+(const Poly& other) const
{
	Poly newPoly(*this);
	newPoly += other;
	return newPoly;
}

// Overloaded plus-equals operator
Poly& Poly::operator+=(const Poly& other)
{
	// If the highest power is from the left hand side, add all values together
	if (highestPower >= other.highestPower)
	{
		for (int i = 0; i < other.highestPower + 1; i++)
		{
			coeffPtr[i] = coeffPtr[i] + other.coeffPtr[i];
		}
	}

	// If the highest power is from the right hand side, dynamically resize the array and add
	else
	{
		int* newPoly = new int[other.highestPower + 1];

		for (int i = 0; i < other.highestPower + 1; i++)
		{
			newPoly[i] = other.coeffPtr[i];
			
			if (i < highestPower + 1)
			{
				newPoly[i] = newPoly[i] + coeffPtr[i];
			}
		}

		delete[] coeffPtr;
		coeffPtr = newPoly;
		highestPower = other.highestPower;
	}

	return *this;
}


// Overloaded multiplication operator
Poly Poly::operator*(const Poly& other) const
{
	Poly newPoly(*this);
	newPoly *= other;
	return newPoly;
}


Poly& Poly::operator*=(const Poly& other)
{
	// If left hand side is empty, return
	if (isEmpty())
	{
		return *this;
	}

	// If right hand side is empty, make the left hand side empty
	else if (other.isEmpty())
	{
		delete[] coeffPtr;
		coeffPtr = new int[1];
		coeffPtr[0] = 1;
		highestPower = 0;
		return *this;
	}

	// If neither side is empty, multiply the two polynomials
	// Finds the newest highest power and makes a new array of that length
	int newHighestPower = highestPower + other.highestPower;
	int* newPoly = new int[newHighestPower + 1];
	for (int i = 0; i < newHighestPower + 1; i++)
	{
		newPoly[i] = 0; // Makes all the coefficients 0 
	}

	// Multiplies the values in the poly
	for (int i = 0; i < highestPower + 1; i++)
	{
		for (int j = 0; j < other.highestPower + 1; j++)
		{
			newPoly[i + j] = (coeffPtr[i] * other.coeffPtr[j]) + newPoly[i + j];
		}
	}

	delete[] coeffPtr;
	coeffPtr = newPoly;
	highestPower = newHighestPower;
	return *this;
}

// Overloaded unary negation operator
// Changes the sign of all components of the polynomial
Poly Poly::operator-() const
{
	for (int i  = 0; i < highestPower + 1; i++)
	{
		coeffPtr[i] = -coeffPtr[i];
	}

	return *this;
}

// Overloaded equality operator
// Returns true if the polynomials are equal to each other
// Returns false if the polynomials are not equal to each other
bool Poly::operator==(const Poly& other) const
{
	// Checks if the highest powers of both polynomials are equal
	if (highestPower == other.highestPower)
	{
		// Checks if all coefficients of the polynomials are equal. If so, return true
		for (int i = 0; i < highestPower + 1; i++)
		{
			if (coeffPtr[i] != other.coeffPtr[i])
			{
				return false;
			}
		}
		return true;
	}
	// If the highest powers of both polynomials are not equal, then return false
	return false;
}

// Overloaded inequality operator
// Returns true if the polynomials are not equal to each other
// Returns false if the polynomials are equal to each other
bool Poly::operator!=(const Poly& other) const
{
	bool doesntEquals = !(*this == other);
	return doesntEquals;
}


// Assignment Overload Operator
Poly& Poly::operator = (const Poly& other)
{
	// if both polynomials are equal, return this existing polynomial
	if (*this == other)
	{
		return *this;
	}

	// Otherwise, copy all values from the right hand side to the left hand side
	delete[] coeffPtr;
	coeffPtr = new int[other.highestPower + 1];
	highestPower = other.highestPower;

	for (int i = 0; i < other.highestPower + 1; i++)
	{
		coeffPtr[i] = other.coeffPtr[i];
	}

	return *this;
}

// Prints out the polynomial by overriding cout
ostream& operator<<(ostream& outStream, const Poly& thisPoly)
{
	// Prints out 0 if the polynomial is empty
	if (thisPoly.isEmpty())
	{
		outStream << " "<< 0;
		return outStream;
	}

	// constructs the string in reverse order
	string reversePoly = "";
	for (int i = 0; i < thisPoly.highestPower + 1; i++)
	{
		// Checks if the coefficiet is not zero so it can print it out
		if (thisPoly.coeffPtr[i] != 0)
		{
			string currentIndex = to_string(i);
			currentIndex = string(currentIndex.rbegin(), currentIndex.rend());
			
			// If index is greater than 1, it has a power
			if (i > 1)
			{
				reversePoly += currentIndex + "^x";
			}

			// If index is equal to 1, the polynomical for the index is just x
			else if (i == 1)
			{
				reversePoly += "x";
			}

			// checks if the coefficient is positive. output will have a "+" to indicate it is positive
			if (thisPoly.coeffPtr[i] > 0)
			{
				string currentCoeff = to_string(thisPoly.coeffPtr[i]);
				currentCoeff = string(currentCoeff.rbegin(), currentCoeff.rend());
				reversePoly += currentCoeff;
				reversePoly += "+ ";
			}

			// checks if the coefficient is negative.  output will have a "+" to indicate it is positive
			else if (thisPoly.coeffPtr[i] < 0)
			{
				string currentCoeff = to_string(-thisPoly.coeffPtr[i]);
				currentCoeff = string(currentCoeff.rbegin(), currentCoeff.rend());
				reversePoly += currentCoeff;
				reversePoly += "- ";
			}
		}
	}
	
	string  retVal(reversePoly.rbegin(), reversePoly.rend());
	outStream << retVal;

	return outStream;
}

// Reads in a polynomial 
istream& operator>>(istream& inStream, Poly& thisPoly)
{
	// Deletes the old data so the poly can be overwritten
	delete[] thisPoly.coeffPtr;
	thisPoly.coeffPtr = new int[1];
	thisPoly.coeffPtr[0] = 0;
	thisPoly.highestPower = 0;
	
	
	// Reads in the coefficient and power
	int coeff = 0;
	int power = 0;
	inStream >> coeff;
	inStream >> power;

	// While loop will continue looping and adding values to the polynomials until user enters -1 -1
	// Loop ends if both coefficient and power are -1
	while (coeff != -1 && power != -1)
	{
		// Sets the coefficient and power
		thisPoly.setCoeff(coeff, power);

		// Reads in the coefficient and power
		inStream >> coeff;
		inStream >> power;
	}
	return inStream;
}

// Returns the coefficient
int Poly::getCoeff(int power) const
{
	// If the power is less than or equal to the highest power, return the coefficient
	if ((highestPower >= power) && (power >= 0))
	{
		return coeffPtr[power];
	}

	// If the power is greater than the highest power, return 0
	return 0;
}

// Sets the coeffient
void Poly::setCoeff(int coeff, int power)
{
	// Checks if power is greater than the current highest power
	// If so, dynamically resizes the array and then sets the coefficent
	if (power > highestPower)
	{
		int* temp = new int[power+1];
		
		for (int i = 0; i < highestPower + 1; i++)
		{
			temp[i] = coeffPtr[i];
		}

		for (int i = highestPower + 1; i < power + 1; i++)
		{
			temp[i] = 0;
		}

		temp[power] = coeff;

		highestPower = power;
		delete[] coeffPtr;
		coeffPtr = temp;
	}
	
	// If the power is less than or equal to the current highest power, set the coefficient
	else
	{
		coeffPtr[power] = coeff;
	}
}

// Checks if the polynomial is empty
bool Poly::isEmpty() const
{
	return (highestPower == 0) && (coeffPtr[0] == 0);
}