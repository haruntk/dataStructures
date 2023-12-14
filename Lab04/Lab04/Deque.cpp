#include "Deque.h"
#include <iostream>

///------------------------------------------------------
/// Default constructor
/// 
Deque::Deque() {
	head = tail = nullptr;
	noOfItems = 0;
} //end-Deque

///------------------------------------------------------
/// Destructor
/// 
Deque::~Deque() {
	while (this->head) {
		RemoveFront();
	}
	noOfItems=0;
} //end-~Deque

///------------------------------------------------------
/// Adds a new item to the front of the Deque
/// 
void Deque::AddFront(int item) {
	DequeNode* node = new DequeNode(item);
	if (noOfItems == 0) {
		head = node;
		tail = node;
	}
	else {
		node->next = head;
		head->prev = node;
		head = node;
	}
	noOfItems++;
} //end-AddFront

///------------------------------------------------------
/// Adds a new item to the end of the Deque
/// 
void Deque::AddRear(int item) {
	DequeNode* node = new DequeNode(item);
	if (noOfItems == 0) {
		head = node;
		tail = node;
	}
	else {
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	noOfItems++;
} //end-AddRear

///------------------------------------------------------
/// Remove and return the item at the front of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveFront() {
	if (noOfItems == 0) {
		std::cerr << "The list is empty!";
		return -1;
	}
	DequeNode* node = head;
	int item = head->item;
	head = head->next;
	if (head == nullptr) tail = nullptr;
	else head->prev = nullptr;
	delete node;
	noOfItems--;
	return item;
} //end-RemoveFront

///------------------------------------------------------
/// Remove and return the item at the rear of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveRear() {
	if (noOfItems == 0) {
		std::cerr << "The list is empty!";
		return -1;
	}
	int item = tail->item;
	DequeNode* node = tail;
	tail = tail->prev;
	if (tail == nullptr) head = nullptr;
	else tail->next = nullptr;
	delete node;
	noOfItems--;
	return item;
} //end-RemoveRear

///------------------------------------------------------
/// Return the item at the front of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Front() {
	if (noOfItems == 0) {
		std::cerr << "The list is empty!";
		return -1;
	}
	return head->item;
} //end-Front

///------------------------------------------------------
/// Return the item at the rear of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Rear() {
	if (noOfItems==0) {
		std::cerr << "The list is empty!";
		return -1;
	}
	return tail->item;
} //end-Rear
