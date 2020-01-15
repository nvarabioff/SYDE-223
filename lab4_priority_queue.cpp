#include <iostream>

#include "lab4_priority_queue.hpp"

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	capacity = n_capacity;
	size = 0;
	heap = new TaskItem *[capacity+1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for (int i = 1; i <= size; ++i) {
		delete heap[i];
	}
	delete [] heap;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	if (size == 0)
		return true;
	return false;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	if (size == capacity)
		return true;
	return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	for (int i = 1; i < size + 1; i++) {
		cout << "Task " << i << ": " << endl;
		cout << "Priority: " << heap[i]->priority << endl;
		cout << "Description: " << heap[i]->description << endl;
		cout << endl;
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if (empty()) {
		return TaskItem(-1, "N/A");
	} else {
		TaskItem *ret = heap[1];
		return *ret;
	}
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if (full()) {
		return false;
	} else if (empty()) {
		heap[1] = new TaskItem(val);
	} else {
		int i = size + 1;
		heap[i] = new TaskItem(val);
		while (i > 1 && heap[i/2]->priority < heap[i]->priority) {
			TaskItem *temp = heap[i];
			heap[i] = heap[i/2];
			heap[i/2] = temp;
			i /= 2;
		}
	}
	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if (empty()) {
		return false;
	} else if (size == 1) {
		delete heap[1];
		heap[1] = NULL;
		size--;
	} else {
		TaskItem *temp = heap[1];
		heap[1] = heap[size];
		heap[size] = temp;
		delete heap[size];
		size--;
		int i = 1;
		bool keep_swapping = true;			
		int max = i;
		while (i <= size && keep_swapping) {
			if (2*i + 1 <= size) {
				if (heap[2*i] < heap[2*i + 1]) {
					max = 2*i + 1;
				} else {
					max = 2*i;
				}
			} else if (2*i <= size) {
				max = 2*i;
			} else {
				keep_swapping = false;
			}
			if (heap[i] < heap[max]) {
				TaskItem *temp = heap[i];
				heap[i] = heap[max];
				heap[max] = temp;
				i = max;				
			} else {
				keep_swapping = false;
			}
		}
	}
	return true;
}
