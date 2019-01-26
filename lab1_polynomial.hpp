//Nicholas Varabioff 20702729
//Ryan Gangl 20737072
#ifndef lab1_polynomial_H
#define lab1_polynomial_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

//function declaration():
//PURPOSE:
//INPUTS:
//RETURNS:

using namespace std;

class Polynomial {
	int* data;
	int data_size;
	friend class PolynomialTest;
public:
	Polynomial(int A[], int size);	//class constructor with 2 input parameters
	Polynomial();					//class constructor with random values
	Polynomial(string fileName);	//class constructor with input file
	~Polynomial();					//destructor performs cleanup if needed
	
	bool operator==(const Polynomial& target);		//performs *this == target
	void print();									//prints the polynomial (ex. 2x^3 + 1x^0)
	Polynomial operator+(const Polynomial& target);	//performs *this + target
	Polynomial operator-(const Polynomial& target);	//performs *this - target
	Polynomial operator*(const Polynomial& target);	//performs *this * target
	Polynomial derivative();						//computes the derivative d/dx of *this
	
	
};

class PolynomialTest {
public:
	bool test_constructors();	//Tests the constructors
	bool test_isEqual();		//Tests '==' operator
	bool test_addition();		//Tests '+' operator
	bool test_subtraction();	//Tests '-' operator
	bool test_multiplication();	//Tests '*' operatop
	bool test_derivative();		//Tests derivative function
	void test_print();			//Tests print function
	void run();					//Runs all tests
};

#endif
