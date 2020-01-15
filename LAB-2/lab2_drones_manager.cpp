#include "lab2_drones_manager.hpp"
#include <iostream>
#include <string>

using namespace std;

DronesManager::DronesManager() {
    first = NULL;
    last = NULL;
    size = 0;
}

DronesManager::~DronesManager() {
    DroneRecord* current = first;
    while (current) {
        current = first->next;
        delete first;
        first = current;
    }
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    bool is_equal = false;
    if(lhs.batteryType == rhs.batteryType &&
    lhs.description == rhs.description &&
    lhs.droneID == rhs.droneID &&
    lhs.droneType == rhs.droneType &&
    lhs.manufacturer == rhs.manufacturer &&
    lhs.range == rhs.range &&
    lhs.yearBought == rhs.yearBought){
        is_equal = true;
    }
    return is_equal;
}

unsigned int DronesManager::get_size() const {
    return size;
}

bool DronesManager::empty() const {
    if (!first) {
        return true;
    }
    return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if (empty()) {	//if list is empty, returns DroneRecord(0)
        return DroneRecord(0);
    } else if (index > size-1 || index < 0) {	//if index is invalid, returns last element
        return DroneRecord(*last);
    } else {
        DroneRecord* temp = first;
        int i = 0;
        while (temp) {
            if (i == index) {
                return *temp;
            }
            temp = temp->next;
            ++i;
        }
        return DroneRecord(*temp);
    }
}

unsigned int DronesManager::search(DroneRecord value) const {
    if (!first) {	//if the list is empty, returns 0
        return 0;
    } else {
        DroneRecord* temp = first;
        int index = 0;
        while (temp) {
            if (temp->droneID == value)
                return index;
            temp = temp->next;
            ++index;
        }
        //if not found, returns the size of the list
        return size;
    }
}

void DronesManager::print() const {
    cout << "(";
    DroneRecord* temp = first;
    while (temp) {
        cout << "[" << temp->droneID << ", " << temp->droneType << ", " << temp->description << ", "
        << temp->manufacturer << ", " << temp->batteryType << ", " << temp->yearBought << ", " << temp->range << "]";
        temp = temp->next;
        if (temp)
            cout << "->";
    }
    cout << ")\n";
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    if (index > size || index < 0) {	//if index is invalid, insertion is rejected
        return false;
    }
    if (!first) {
        DroneRecord* temp = new DroneRecord(value);
        first = temp;
        last = temp;
        temp->next = NULL;
        temp->prev = NULL;
        ++size;
    } else if (!first->next) {
        if (index == 0)
            insert_front(value);
        if (index == 1)
            insert_back(value);
        ++size;
    } else if (index == size) {
        insert_back(value);
    } else if (index == 0) {
        insert_front(value);
    } else {
        DroneRecord* temp = first;
        for (int i = 0; i < index-1; ++i) {
            temp = temp->next;
        }
        DroneRecord* insert = new DroneRecord(value);
        temp->next->prev = insert;
        insert->prev = temp;
        insert->next = temp->next;
        temp->next = insert;
        ++size;
    }
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    if (!first) {
        DroneRecord* temp = new DroneRecord(value);
        first = temp;
        last = first;
        temp->next = NULL;
        temp->prev = NULL;
        ++size;
        return true;
    } else {
        DroneRecord* temp = new DroneRecord(value);
        temp->next = first;
        temp->prev = NULL;
        first->prev = temp;
        first = temp;
        ++size;
        return true;
    }
}

bool DronesManager::insert_back(DroneRecord value) {
    if (!first) {
        first = new DroneRecord(value);
        first->next = NULL;
        first->prev = NULL;
        last = first;
        ++size;
        return true;
    } else {
        DroneRecord* temp = last;
        DroneRecord* insert = new DroneRecord(value);
        temp->next = insert;
        insert->prev = temp;
        insert->next = NULL;
        last = insert;
        ++size;
        return true;
    }
}

bool DronesManager::remove(unsigned int index) {
    if (!first || index > size-1) {
        return false;
    } else if (index == 0) {
        remove_front();
    } else if (index == size-1) {
        remove_back();
    } else {
        DroneRecord* temp = first;
        int i = 0;
        while (i < index) {
            temp = temp->next;
            i++;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        --size;
    }
    return true;
}

bool DronesManager::remove_front() {
    if (!first) {
        return false;
    } else if (!first->next) {
        delete first;
        first = NULL;
        last = NULL;
    } else {
        DroneRecord* temp = first->next;
        delete temp->prev;
        first = temp;
        first->prev = NULL;
    }
    --size;
    return true;
}

bool DronesManager::remove_back() {
    if (!first) {
        return false;
    } else if (size == 1) {
        delete first;
        first = NULL;
        last = NULL;
        --size;
    } else {
        DroneRecord* temp = last;
        DroneRecord* temp2;
        temp2 = temp->prev;
        delete (temp);
        temp2->next = NULL;
        last = temp2;
        --size;
    }
    return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    if (index > size-1 || index < 0) {	//if the index is invalid, replacement is rejected
        return false;
    } else if (!first) {
    	return false;
	} else {
        remove(index);
        insert(value, index);
        return true;
    }
}

bool DronesManager::reverse_list() {
    if (!first) {
        return false;
    } else if (!first->next) {
        return true;
    } else {
        DroneRecord* current = first;
        DroneRecord* temp = NULL;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        DroneRecord* temp1 = first;
        DroneRecord* temp2 = last;
        first = temp2;
        last = temp1;
        return true;
    }
}

bool DronesManagerSorted::is_sorted_asc() const {
    if (!first) {
        return false;
    } else if (!first->next) {
        return true;
    } else {
        DroneRecord* temp = first;
        while (temp->next != NULL) {
            if (temp->droneID > temp->next->droneID) {
                return false;
            }
            temp = temp->next;
        }
    }
    return true;
}

bool DronesManagerSorted::is_sorted_desc() const {
    if (!first) {
        return false;
    } else if (!first->next) {
        return true;
    } else {
        DroneRecord* temp = first;
        while (temp->next != NULL) {
            if (temp->droneID < temp->next->droneID) {
                return false;
            }
            temp = temp->next;
        }
    }
    return true;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	DroneRecord* temp = new DroneRecord(val);
	if (!first) {
        first = temp;
        last = temp;
        ++size;
        return true;
    } else if (!is_sorted_asc()) {	//if the list is not sorted in appropriate order, insertion is rejected
        return false;
	} else {
        int index = 0;
        DroneRecord* temp2 = first;
        while (temp2) {
            if (temp2->droneID > temp->droneID) {
                insert(*temp, index);
                return true;
            }
            temp2 = temp2->next;
            index++;
        }
        insert_back(*temp);
        return true;
    }
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    DroneRecord* temp = new DroneRecord(val);
    if (!first) {
        first = temp;
        last = temp;
        ++size;
        return true;
      } else if (!is_sorted_desc()) {	//if the list is not sorted in appropriate order, insertion is rejected
            return false;
      } else {
        int index = 0;
        DroneRecord* temp2 = first;
        while (temp2) {
            if (temp2->droneID < temp->droneID) {
                insert(val, index);
                return true;
            }
            temp2 = temp2->next;
            index++;
        }
        insert_back(*temp);
        return true;
    }
}

void DronesManagerSorted::sort_asc() {
    if (!first) {
        return;
    } else if (!first->next) {
        return;
    } else {
        int swapped = 0;
        int temp;
        DroneRecord* temp1;
        DroneRecord* temp2 = NULL;
        do {
            swapped = 0;
            temp1 = first;
            while (temp1->next != temp2) {
                if (temp1->droneID > temp1->next->droneID) {
                    temp = temp1->droneID;
                    temp1->droneID = temp1->next->droneID;
                    temp1->next->droneID = temp;
                    swapped = 1;
                }
                temp1 = temp1->next;
            }
            temp2 = temp1;
        }
        while (swapped);
    }
}

void DronesManagerSorted::sort_desc() {
    sort_asc();
    reverse_list();
}
