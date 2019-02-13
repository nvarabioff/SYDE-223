#include "lab2_drones_manager.hpp"
#include <iostream>
#include <string>

using namespace std;

//**************************
//DronesManager: ACCESSORS
//**************************

//PURPOSE: Creates a new empty DronesManager
DronesManager::DronesManager() { //DONE
	first = NULL;
	last = NULL;
	size = 0;
}

//PURPOSE: Destroys this instance and frees up all dynamically allocated memory
DronesManager::~DronesManager() { //DONE
	DroneRecord *temp = first;
	DroneRecord *next;
	while (temp != NULL){
		next = temp->next;
		delete (temp);
		temp = next;
	}
}

//PURPOSE: Comparison operator to compare two DroneRecord instances
bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {	//DONE
	bool success = true;
	if (lhs.droneID != rhs.droneID || lhs.range != rhs.range || lhs.yearBought != rhs.yearBought)	//Compares ints
		success = false;
	if (lhs.droneType != rhs.droneType || lhs.manufacturer != rhs.manufacturer || lhs.description != rhs.description || lhs.batteryType != rhs.batteryType)	//Compares strings
		success = false;
	//if (lhs.prev != rhs.prev || lhs.next != rhs.next)	//Compares Pointers
	//	success = false;
	return success;
}

//PURPOSE: Returns the number of elements in the list
unsigned int DronesManager::get_size() const {	//DONE
	return size;
}

//PURPOSE: Checks if the list is empty; returns true if the list is empty, false otherwise
bool DronesManager::empty() const {	//DONE
	bool empty = false;
	if (first == NULL && last == NULL && size == 0)
		empty = true;
	return empty;
}

//PURPOSE: Returns the value at the given index in the list
DronesManager::DroneRecord DronesManager::select(unsigned int index) const {	//SHOULD WORK I BELIEVE
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
unsigned int DronesManager::search(DroneRecord value) const {	//DONE
	if (empty())	//If the list is empty, returns 0
		return 0;
	DroneRecord *temp = first;
	int count = 0;
	while (temp != NULL) {
		if (*temp == value)
			return count;
			break;
		temp = temp->next;
		count++;
	}
	if (count > size)	//If not found, returns the size of the list
		return size;
}

//PURPOSE: Prints all the elements in the list to the console
void DronesManager::print() const {	//DONE
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
bool DronesManager::insert(DroneRecord value, unsigned int index) {	//DONE
	bool success = true;
	if (index >= size || index < 0)	//If the index is invalid, insertion is rejected
		return false;
	DroneRecord *temp = new DroneRecord(value);
	if (empty()) {	//If list is empty
		first = temp;
		last = temp;
		temp->next = NULL;
		temp->prev = NULL;
		size++;
	} else if (index == 0) {	//Inserting at the front
		insert_front(value);
	} else if (index == size - 1) {	//Insterting at the back
		insert_back(value);
	} else {
		DroneRecord *end = first;
		for (unsigned int i = 0; i < index; i++) {
			end = end->next;
		}
		temp->next = end->next;
		temp->prev = end;
		end->next = temp;
		temp->next->prev = temp;
		size++;
	} return success;
}

//PURPOSE: Inserts a value at the beginning of the list; the list is not sorted
bool DronesManager::insert_front(DroneRecord value) {	//DONE
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
bool DronesManager::insert_back (DroneRecord value) {	//DONE
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
bool DronesManager::remove(unsigned int index) {	//DONE
	bool success = true;
	if (index >= size || index < 0)	//If the index is invalid, insertion is rejected
		success = false;
	if (empty())	//If the list is empty, cannot delete
		success = false;
	if (size == 1) {	//If there is only one item in the list, simply delete that item
		delete (first);
		first = NULL;
		last = NULL;
		size--;	
	}
	if (index == 0) {	//Deleting first item
		remove_front();
	} else if (index == size - 1) {	//Deleting last item
		remove_back();
	} else {
		DroneRecord *end = first;
		for (unsigned int i = 0; i < index; i++) {
			end = end->next;
		}
		end->next = end->next->next;
		end->next->next->prev = end;
		delete (end->next);
		size--;
		/*
		DroneRecord *temp = end->next;
		end->next = temp->next;
		temp->next->prev = end;
		delete (temp);
		*/
	}
	return success;
}

//PURPOSE: Deletes a value from the beginning of the list
bool DronesManager::remove_front() {	//DONE
	bool success = true;
	if (empty())	//If the list is empty, cannot delete
		success = false;
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
bool DronesManager::remove_back() {	//DONE
	bool success = true;
	if (empty()) {	//If the list is empty, cannot delete
		success = false;
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
bool DronesManager::replace(unsigned int index, DroneRecord value) {	//DONE
	bool success = true;
	if (index >= size || index < 0)	//If index is invalid, replacement is rejected
		return false;
	DroneRecord *temp = first;
	for (unsigned int i = 0; i < index; i++) {
		temp = temp->next;
	}
	if (temp != NULL) {
		temp = &value;
	}
	return success;
}

//PURPOSE: Reverses the linked list
bool DronesManager::reverse_list() {	//DONE I THINK
	bool success = true;
	DroneRecord *swapper = first;
	DroneRecord *temp = NULL;
	while (temp != NULL) {
		temp = swapper->prev;
		swapper->prev = swapper->next;
		swapper->next = temp;
		swapper = swapper->prev;
	}
	if (temp != NULL) {
		DroneRecord *temp2 = last;
		last = first;
		first = temp2;		
	}
	return success;
}

//********************************
//DronesManagerSorted: ACCESSORS
//********************************

//PURPOSE: Returns true if the list is sorted in ascending (non-descending) order
bool DronesManagerSorted::is_sorted_asc() const {
	bool success = true;
	
	return success;
}

bool DronesManagerSorted::is_sorted_desc() const {
	bool success;
	
	return success;
}

//********************************
//DronesManagerSorted: MUTATORS
//********************************

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	bool success;
	
	return success;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	bool success;
	
	return success;
}

void DronesManagerSorted::sort_asc() {
}
    
void DronesManagerSorted::sort_desc() {
}

int main() {
}
