#ifndef STACKS_HPP
#define STACKS_HPP

#include <iostream>
#include <string>
#include <list>
#include <stack>
using namespace std;

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;
#define ASSERT_NULL(T) if (!(T)) return false;
#define ASSERT_NOT_NULL(T) if ((T)) return false;

// PURPOSE: Models the specified fridge organization problem
class FridgeOrganizerTest;

class FridgeOrganizer {
	// PURPOSE: Models a meal portion as part of the specified fridge organization problem
	struct MealPortion { // internal class that allows storage of meal portions
		string name; // name of meal portion
		string expiry; // expiry of meal portion
		MealPortion(string n_name, string n_expiry) : name(n_name), expiry(n_expiry) {}
		void print() { cout << "| ELEMENT: " << name << ", " << expiry << " |" << endl; }
	};

	list<stack<MealPortion*>*> stacks; // a doubly-linked list of stack pointers
	unsigned int stack_number; // maximum number of stacks
	unsigned int usable_stacks; // leave one stack empty for shuffling
	unsigned int stack_capacity; // maximum stack capacity
	
	friend FridgeOrganizerTest; // set the test class as friend

public:
	// PURPOSE: Parametric constructor for FridgeOrganizer
	FridgeOrganizer(unsigned int n_stack_number, unsigned int n_stack_capacity);
	
	// PURPOSE: Destructor for FridgeOrganizer
	~FridgeOrganizer();
	
	// PURPOSE: Prints all meal stacks in the fridge
	void print_stacks();

	// PURPOSE: Returns the number of meal portions in the fridge
	int number_of_portions();
	
	// PURPOSE: Adds a new meal portion to existing portions if there is space
	// insert the portion into the first empty stack from the back
	bool add_meal_portion(string n_name, string n_expiry);

	// PURPOSE: Removes the meal from the fridge based on LIFO principle
	// if the fridge is empty, returns ("EMPTY", "N/A")
	MealPortion remove_meal_portion();
	
	// PURPOSE: Finds the meal in the fridge with earliest expiry date value
	// assumes that valid expiry will be expressed as YY-MM-DD
	// if the fridge is empty, returns ("EMPTY", "N/A")
	// this method may not disrupt other functionality
	MealPortion find_meal_portion_by_expiry();
};

class FridgeOrganizerTest {	
	// PURPOSE: Tests FridgeOrganizer constructor and basic item insertion
	bool test1();
	
	// PURPOSE: Tests stack growth and shrinking with LIFO removal
	bool test2();
	
	// PURPOSE: Tests finding meal portion by earliest expiry date
	bool test3();
	
public:	
	// PURPOSE: Runs all of the specified tests and produces corresponding output
	void runTests();
};
#endif
