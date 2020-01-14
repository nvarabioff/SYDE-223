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
	Polynomial(int A[], int size);	
	//PURPOSE: class constructor with 2 input parameters
		//INPUTS: Array A, int size
		//RETURNS: Polynomial Object
	
	Polynomial();
	//PURPOSE: class constructor with random values
		//INPUTS: none
		//RETURNS: Polynomial Object
	
	Polynomial(string fileName);
	//PURPOSE: class constructor with input file
		//INPUTS: name of a file as a string
		//RETURNS: Polynomial Object

	~Polynomial();
	//PURPOSE: destructor performs cleanup if needed
		//INPUTS: none
		//RETURNS: none
	
	bool operator==(const Polynomial& target);
	//PURPOSE: performs *this == target
		//INPUTS: 2 Polynomial objects
		//RETURNS: boolean value of equal or not equal
	
	void print();
	//PURPOSE: prints the polynomial object (ex. 2x^3 + 1x^0)
		//INPUTS: none
		//RETURNS: none

	Polynomial operator+(const Polynomial& target);
	//PURPOSE: performs *this + target
		//INPUTS: 2 Polynomial objects
		//RETURNS: Polynomial object result

	Polynomial operator-(const Polynomial& target);
	//PURPOSE: performs *this - target
		//INPUTS: 2 Polynomial objects
		//RETURNS: Polynomial object result
		
	Polynomial operator*(const Polynomial& target);
	//PURPOSE: performs *this * target
		//INPUTS: 2 Polynomial objects
		//RETURNS: Polynomial object result
		
	Polynomial derivative();
	//PURPOSE: computes the derivative d/dx of *this
		//INPUTS: none
		//RETURNS: Polynomial object result
	
	int getDegree();
	//PURPOSE: get the data_size (degree) member of Polynomial object
		//INPUTS: none
		//RETURNS: int data_size of Polynomial object
};

class PolynomialTest {
public:
	bool test_constructors();
	//PURPOSE: Tests the constructors
		//INPUTS: none
		//RETURNS: bool value of test successful
		
	bool test_isEqual();
	//PURPOSE: Tests '==' operator
		//INPUTS: none
		//RETURNS: bool value of test successful
		
	bool test_addition();
	//PURPOSE: Tests '+' operator
		//INPUTS: none
		//RETURNS: bool value of test successful
		
	bool test_subtraction();
	//PURPOSE: Tests '-' operator
		//INPUTS: none
		//RETURNS: bool value of test successful
		
	bool test_multiplication();
	//PURPOSE: Tests '*' operatop
		//INPUTS: none
		//RETURNS: bool value of test successful
		
	bool test_derivative();
	//PURPOSE: Tests derivative function
		//INPUTS: none
		//RETURNS: bool value of test successful
		
	void test_print();
	//PURPOSE: Tests print function
		//INPUTS: none
		//RETURNS: none
		
	void run();
	//PURPOSE: Runs all tests
		//INPUTS: none
		//RETURNS: none
};

#endif
