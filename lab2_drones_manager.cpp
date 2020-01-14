#include "lab2_drones_manager.hpp"
#include <iostream>
#include <string>

using namespace std;

//**************************
//DronesManager: ACCESSORS
//**************************

//PURPOSE: Creates a new empty DronesManager
DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}

//PURPOSE: Destroys this instance and frees up all dynamically allocated memory
DronesManager::~DronesManager() {
	DroneRecord *temp = first;
	while (temp != NULL){
		temp = first->next;
		delete (first);
		first = temp;
	}
}

//PURPOSE: Comparison operator to compare two DroneRecord instances
bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	bool success = true;
	if (lhs.droneID != rhs.droneID || lhs.range != rhs.range || lhs.yearBought != rhs.yearBought)	//Compares ints
		success = false;
	if (lhs.droneType != rhs.droneType || lhs.manufacturer != rhs.manufacturer || lhs.description != rhs.description 
			|| lhs.batteryType != rhs.batteryType)	//Compares strings
		success = false;
	return success;
}

//PURPOSE: Returns the number of elements in the list
unsigned int DronesManager::get_size() const {
	return size;
}

//PURPOSE: Checks if the list is empty; returns true if the list is empty, false otherwise
bool DronesManager::empty() const {
	bool empty = false;
	if (first == NULL && last == NULL && size == 0)
		empty = true;
	return empty;
}

//PURPOSE: Returns the value at the given index in the list
DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (index >= size)	//If index is invalid, returns last element
		return *last;
	else if (empty())	//If the list is empty, returns DroneRecord(0)
		return DroneRecord(0);
	DroneRecord *temp = first;
	unsigned int count = 0;
	while (temp != NULL) {
		if (count == index)
			return *temp;
		temp = temp->next;
		count++;
	}
}

//PURPSOE: Searches for the given value, and returns the index of this value if found
unsigned int DronesManager::search(DroneRecord value) const {
	if (empty())	//If the list is empty, returns 0
		return 0;
	DroneRecord *temp = first;
	int count = 0;
	while (temp != NULL) {
		if (*temp == value)
			return count;
		temp = temp->next;
		count++;
	}
	if (count > size)	//If not found, returns the size of the list
		return size;
}

//PURPOSE: Prints all the elements in the list to the console
void DronesManager::print() const {
	DroneRecord *temp = first;
	int count = 0;
	cout << "DroneManager List:\n";
	while (temp != NULL) {
		cout << "\nIndex: " << count << endl;
		cout << "Drone ID: " << temp->droneID << endl;
		cout << "Range: " << temp->range << endl;
		cout << "Year Bought: " << temp->yearBought << endl;
		cout << "Drone Type: " << temp->droneType << endl;
		cout << "Manufacturer: " << temp->manufacturer << endl;
		cout << "Description: " << temp->description << endl;
		cout << "Battery Type: " << temp->batteryType << endl;
		cout << endl;
		temp = temp->next;
		count++;
	}
}

//**************************
//DronesManager: MUTATORS
//**************************

//PURPOSE: Inserts a value into the list at a given index; the list is not sorted
bool DronesManager::insert(DroneRecord value, unsigned int index) {
	bool success = true;
	if (index > size || index < 0)	{	//If the index is invalid, insertion is rejected
		return false;
	}
	if (empty()) {	//If list is empty
		DroneRecord *temp = new DroneRecord(value);
		first = temp;
		last = temp;
		temp->next = NULL;
		temp->prev = NULL;
		size++;
	} else if (first->next == NULL) {
		DroneRecord* temp = new DroneRecord(value);
        first->next = temp;
        temp->next = NULL;
        temp->prev = first;
        last = temp;
        size++;
	} else if (index == 0) {	//Inserting at the front
		insert_front(value);
	} else if (index == size) {	//Insterting at the back
		insert_back(value);
	} else {
		DroneRecord *temp = first;
		for (unsigned int i = 0; i < index - 1; i++) {
			temp = temp->next;
		}
		DroneRecord *insert = new DroneRecord(value);
		temp->next->prev = insert;
        insert->prev = temp;
        insert->next = temp->next;
        temp->next = insert;
        size++;
	} 
	return success;
}

//PURPOSE: Inserts a value at the beginning of the list; the list is not sorted
bool DronesManager::insert_front(DroneRecord value) {
	bool success = true;
	DroneRecord *temp = new DroneRecord(value);
	if (empty()) {	//If list is empty
		first = temp;
		last = temp;
		temp->next = NULL;
		temp->prev = NULL;
	} else {	//Inserting at the front
		temp->next = first;
		temp->prev = NULL;
		first = temp;
		temp->next->prev = first;
	} 
	size++;
	return success;
}

//PURPOSE: Inserts a value at the end of the list; the list is not sorted
bool DronesManager::insert_back (DroneRecord value) {
	bool success = true;	
	DroneRecord *temp = new DroneRecord(value);
	if (empty()) {	//If list is empty
		first = temp;
		last = temp;
		temp->next = NULL;
		temp->prev = NULL;
	} else {	//Inserting at the back
		temp->next = NULL;
		temp->prev = last;
		last = temp;
		temp->prev->next = last;
	} 
	size++;
	return success;
}

//PURPOSE: Deletes a value from the list at the given index
bool DronesManager::remove(unsigned int index) {
	bool success = true;
	if (empty())	{	//If the list is empty, cannot delete
		return false;
	} else if (index >= size || index < 0)	{	//If the index is invalid, insertion is rejected
		return false;
	} else if (size == 1) {	//If there is only one item in the list, simply delete that item
		delete (first);
		first = NULL;
		last = NULL;
		size--;	 
	} else if (index == 0) {	//Removing first item
		remove_front();
	} else if (index == size - 1) {	//Removing last item
		remove_back();
	} else {
		DroneRecord *temp = first;
		for (unsigned int i = 0; i < index; i++) {
			temp = temp->next;
		}
		temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
		delete (temp->next);
		size--;
	}
	return success;
}

//PURPOSE: Deletes a value from the beginning of the list
bool DronesManager::remove_front() {
	bool success = true;
	if (empty())	//If the list is empty, cannot delete
		return false;
	else if (size == 1){	//If there is only one item in the list, simply delete that item
		delete (first);
		first = NULL;
		last = NULL;
		size--;	
	} else {
		DroneRecord *temp = first;
		first = first->next;
		delete (temp);
		size--;
	}
	return success;
}

//PURPOSE: Deletes a value from the end of the list
bool DronesManager::remove_back() {
	bool success = true;
	if (empty()) {	//If the list is empty, cannot delete
		return false;
	} else if (size == 1){	//If there is only one item in the list, simply delete that item
		delete (first);
		first = NULL;
		last = NULL;
		size--;	
	} else {
		DroneRecord *temp = last;
		last = last->prev;
		delete (temp);
		size--;
	}
	return success;
}

//PURPOSE: Replaces value at the given index with the given value; the list is not sorted
bool DronesManager::replace(unsigned int index, DroneRecord value) {
	bool success = true;
	if (index >= size || index < 0) {	//If index is invalid, replacement is rejected
		return false;
	} else {
	    remove(index);
        insert(value, index);
        return true;
	}
	return success;
}

//PURPOSE: Reverses the linked list
bool DronesManager::reverse_list() {
	bool success = true;
	if (empty()) {
		return false;
	} else if (first->next == NULL) {
		return true;
	} else {
		DroneRecord *temp = first;
		DroneRecord *prev = NULL;
		DroneRecord *next = NULL;
		while (temp != NULL) {
			next = temp->next;
			temp->next = prev;
			prev = temp;
			temp = next;
		}
		last = first;
		first = prev;
		first->prev = NULL;
		last->next = NULL;
		}
	return success;
}

//********************************
//DronesManagerSorted: ACCESSORS
//********************************

//PURPOSE: Returns true if the list is sorted in ascending (non-descending) order
bool DronesManagerSorted::is_sorted_asc() const {
	bool success = true;
	DroneRecord *temp = first;
	while (temp->next != NULL) {
		if (temp->droneID > temp->next->droneID) {
			return false;
		}
		temp = temp->next;
	}
	return success;
}

//PURPOSE: Returns true if the list is sorted in descending (non-ascending) order
bool DronesManagerSorted::is_sorted_desc() const {
	bool success = true;
	DroneRecord *temp = first;
	while (temp->next != NULL) {
		if (temp->droneID < temp->next->droneID) {
			return false;
		}
		temp = temp->next;
	}
	return success;
}

//********************************
//DronesManagerSorted: MUTATORS
//********************************

// PURPOSE: Inserts a value so that the list remains sorted in ascending order
bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	bool success = true;
	if (!is_sorted_asc()) {	// if the list is not sorted in appropriate order, insertion is rejected
		return false;
	} else {
		DroneRecord *temp = first;
		int count = 0;
		while (temp != NULL) {
			if (val.droneID < temp->droneID) {
				insert(val, count);
				return true;
			}
			temp = temp->next;
			count++;
		}
	}
	return success;
}

// PURPOSE: Inserts a value so that the list remains sorted in descending order
bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	bool success;
	if (!is_sorted_desc()) {	// if the list is not sorted in appropriate order, insertion is rejected
		return false;
	} else {
		DroneRecord *temp = first;
		int count = 0;
		while (temp != NULL) {
			if (val.droneID > temp->droneID) {
				insert(val, count);
				return true;
			}
			temp = temp->next;
			count++;
		}
	}
	return success;
}

// PURPOSE: Sorts the list into ascending (non-descending) order
void DronesManagerSorted::sort_asc() {
	if (empty()) {
		return;
	} else if (size <= 1) {
		return;
	} else {
		bool swapped = true;
		DroneRecord *temp1;
		DroneRecord *temp2 = NULL;
		int tempint;
		do {
			swapped = false;
			temp1 = first;
			while (temp1->next != temp2) {
				if (temp1->droneID > temp1->next->droneID) {
					tempint = temp1->droneID;
					temp1->droneID = temp1->next->droneID;
					temp1->next->droneID = tempint;
					swapped = true;
				}
				temp1 = temp1->next;
			}
			temp2 = temp1;
		} while (swapped);
	}
}

// PURPOSE: Sorts the list into descending (non-ascending) order
void DronesManagerSorted::sort_desc() {
	sort_asc();
	reverse_list();
}
