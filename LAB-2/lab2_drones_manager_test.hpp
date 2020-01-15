#ifndef lab2_drones_manager_test_hpp
#define lab2_drones_manager_test_hpp

#include "lab2_drones_manager.hpp"
#include "lab2_drones_manager.cpp"
#include <cstdlib>

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

using namespace std;

class DronesManagerTest {
public:
    // PURPOSE: New empty list is valid
    bool test1() {
        DronesManager manager;
        ASSERT_TRUE(manager.get_size() == 0)
        ASSERT_TRUE(manager.empty() == true)
        ASSERT_TRUE(manager.first == NULL)
        ASSERT_TRUE(manager.last == NULL)
        return true;
    }
    
    // PURPOSE: insert_front() and insert_back() on zero-element list
    bool test2() {
        DronesManager manager1, manager2;
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager2.insert_back(DronesManager::DroneRecord(100));
        
        ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
        ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
        ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
        ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
        ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
        ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
        return true;
    }
    
    // PURPOSE: select() and search() work properly
    bool test3() {
        DronesManager manager;
        
        const int size = 7;
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
        }
        
        unsigned int index = 2;
        ASSERT_TRUE(manager.select(index) == size-index-1)
        ASSERT_FALSE(manager.select(size+1) == true)
        ASSERT_FALSE(manager.select(-4) == true)
        
        ASSERT_TRUE(manager.search(0) == abs(size-1))
        ASSERT_TRUE(manager.search(6) == 0)
        
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.search(i) == abs(size-i-1))
        }

        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        
        return true;
    }
    
    // PURPOSE: remove_front() and remove_back() on one-element list
    bool test4 () {
        DronesManager manager;
        ASSERT_FALSE(manager.remove_back())
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(42), 0))
        ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(5), 4))
        ASSERT_TRUE(manager.remove_front())
        ASSERT_TRUE(manager.first == NULL && manager.last == NULL)
        ASSERT_TRUE(manager.get_size() == 0 && manager.empty() == 1)
        
        ASSERT_FALSE(manager.remove_front())
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(100)))
        ASSERT_TRUE(manager.remove_back())
        ASSERT_TRUE(manager.first == NULL && manager.last == NULL)
        ASSERT_TRUE(manager.get_size() == 0 && manager.empty() == 1)
        
        return true;
    }
    
    // PURPOSE: replace() and reverse_list() work properly
    bool test5 () {
        DronesManager manager;
        const int size = 6;
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
        }
        
        ASSERT_TRUE(manager.replace(0, DronesManager::DroneRecord(3)))
        ASSERT_TRUE(manager.replace(3, DronesManager::DroneRecord(42)))
        ASSERT_FALSE(manager.replace(8, DronesManager::DroneRecord(100)))
        ASSERT_FALSE(manager.replace(-2, DronesManager::DroneRecord(0)))
        ASSERT_TRUE(manager.replace(5, DronesManager::DroneRecord(6)))
        ASSERT_TRUE(manager.replace(5, DronesManager::DroneRecord(6)))
        ASSERT_TRUE(manager.replace(4, DronesManager::DroneRecord(7)))
        
        ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(3))
        ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(6))
        ASSERT_TRUE(*(manager.last->prev->prev) == DronesManager::DroneRecord(42))
        
        int test_values[size] = {6, 7, 42, 2, 1, 3};
        ASSERT_TRUE(manager.reverse_list());
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]));
        }
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        
        return true;
    }
    
    // PURPOSE: insert_front() keeps moving elements forward
    bool test6 () {
        DronesManager manager;
        const int size = 7;
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
            ASSERT_TRUE(manager.get_size() == (i+1))
            ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(i))
            
            DronesManager::DroneRecord* temp = manager.first;
            for (int j = 0; j <= i; j++) {
                DronesManager::DroneRecord value = DronesManager::DroneRecord(i - j);
                ASSERT_TRUE(temp && *temp == value)
                temp = temp->next;
            }
        }
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        
        return true;
    }
    
    // PURPOSE: inserting at different positions in the list
    bool test7() {
        DronesManager manager;
		const int num_elems = 8;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
		}
		//Manager: [7,6,5,4,3,2,1,0]
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(10), 0));
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(20), 3));
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(30), 6));
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(40), 10));
		//Now: [10,7,6,20,5,4,30,3,2,1,40,0]
		int values[] = {10,7,6,20,5,4,30,3,2,1,40,0};
		ASSERT_TRUE(manager.get_size() == 12)
		for (int i = 0; i < 12; i++) {
			ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(values[i]))
		}
		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
		
        return true;
    }
    
    // PURPOSE: try to remove too many elements, then add a few elements
    bool test8() {
        DronesManager manager;
        ASSERT_TRUE(manager.empty());
        ASSERT_FALSE(manager.remove_front());
        ASSERT_FALSE(manager.remove_back());
        ASSERT_FALSE(manager.remove(0));
        
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(14)));
		ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(28)));
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(7), 1));
		ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(14));
		ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(28));
		
		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL);
		
        return true;
    }
    
    // PURPOSE: lots of inserts and deletes, some of them invalid
    bool test9() {
        DronesManager manager;
		
		ASSERT_FALSE(manager.remove(0));	//Removing from empty
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(1), 0));
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(2), 1));
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(3), 14));	//Inserting index OOR high
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(4), -28));	//Inserting index OOR low
		
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(14)));
		ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(28)));
		ASSERT_TRUE(manager.remove_front());
		ASSERT_TRUE(manager.remove_back());
		
		ASSERT_FALSE(manager.remove(28));	//Removing index OOR high
		ASSERT_FALSE(manager.remove(-14));	//Removing index OOR low
		
		ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(1) && *manager.first == DronesManager::DroneRecord(1))
        ASSERT_TRUE(manager.select(1) == DronesManager::DroneRecord(2) && *manager.last == DronesManager::DroneRecord(2))
        
        ASSERT_TRUE(manager.first->next == manager.last && manager.last->prev == manager.first)
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)		
		
        return true;
    }
    
    // PURPOSE: inserts into an unsorted list, then sort the list
    bool test10() {
        DronesManagerSorted manager;
		DronesManagerSorted manager1;
		//SORT ASCENDING
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(42)));
		ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(7)));
		ASSERT_FALSE(manager.insert_sorted_asc(DronesManager::DroneRecord(114)));
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(28), 2));
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(14), 2));
		ASSERT_FALSE(manager.insert_sorted_asc(DronesManager::DroneRecord(77)));
		//manager: [42,7,14,28]
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(100), 2));
		//manager: [42,7,100,14,28]
		ASSERT_FALSE(manager.is_sorted_asc());
		manager.sort_asc();
		ASSERT_TRUE(manager.is_sorted_asc());
		//manager: [7,14,28,42,100]
		ASSERT_TRUE(manager.select(0) == (DronesManager::DroneRecord(7)));
		ASSERT_TRUE(manager.select(1) == (DronesManager::DroneRecord(14)));
		ASSERT_TRUE(manager.select(2) == (DronesManager::DroneRecord(28)));
		ASSERT_TRUE(manager.select(3) == (DronesManager::DroneRecord(42)));
		ASSERT_TRUE(manager.select(4) == (DronesManager::DroneRecord(100)));
		
		//SORT DESCENDING
		ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(7)));
		ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(42)));
		ASSERT_FALSE(manager1.insert_sorted_desc(DronesManager::DroneRecord(114)));
		ASSERT_TRUE(manager1.insert(DronesManager::DroneRecord(28), 2));
		ASSERT_TRUE(manager1.insert(DronesManager::DroneRecord(14), 2));
		ASSERT_FALSE(manager1.insert_sorted_desc(DronesManager::DroneRecord(77)));
		//manager1: [7,42,14,28]
		ASSERT_TRUE(manager1.insert(DronesManager::DroneRecord(100), 2));
		//manager1: [7,42,100,14,28]
		ASSERT_FALSE(manager1.is_sorted_desc());
		manager1.sort_desc();
		ASSERT_TRUE(manager1.is_sorted_desc());
		//manager1: [100,42,28,14,7]
		ASSERT_TRUE(manager1.select(0) == (DronesManager::DroneRecord(100)));
		ASSERT_TRUE(manager1.select(1) == (DronesManager::DroneRecord(42)));
		ASSERT_TRUE(manager1.select(2) == (DronesManager::DroneRecord(28)));
		ASSERT_TRUE(manager1.select(3) == (DronesManager::DroneRecord(14)));
		ASSERT_TRUE(manager1.select(4) == (DronesManager::DroneRecord(7)));
		
        return true;
    }
    
	// PURPOSE: insert and remove into sorted manager in ascending order
    bool test11() {
        DronesManagerSorted manager;
		ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(1)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(13)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(57)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(8)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(2)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(5)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(35)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(1)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(3)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(22)))
        
        ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(1))
        ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(57))
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(1))
        ASSERT_TRUE(manager.select(9) == DronesManager::DroneRecord(57))
        
		//manager: [1,1,2,3,5,8,13,22,35,57]
		ASSERT_TRUE(manager.is_sorted_asc());
		
		ASSERT_TRUE(manager.remove(3));
		ASSERT_TRUE(manager.remove_front());
		ASSERT_TRUE(manager.remove_back());
		
		ASSERT_TRUE(manager.is_sorted_asc());
		
        return true;
    }
    
    // PURPOSE: insert and remove into sorted manager in descending order
    bool test12() {
        DronesManagerSorted manager;
		ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(1)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(13)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(57)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(8)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(2)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(5)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(35)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(1)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(3)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(22)))
        
        ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(57))
        ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(1))
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(57))
        ASSERT_TRUE(manager.select(9) == DronesManager::DroneRecord(1))
        
		ASSERT_TRUE(manager.is_sorted_desc());
		
		ASSERT_TRUE(manager.remove(3));
		ASSERT_TRUE(manager.remove_front());
		ASSERT_TRUE(manager.remove_back());
		
		ASSERT_TRUE(manager.is_sorted_desc());
		
		return true;
    }
};

#endif /* lab2_drones_manager_test_h */
