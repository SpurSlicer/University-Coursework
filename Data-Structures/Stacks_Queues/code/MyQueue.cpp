#include "MyQueue.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

MyQueue::MyQueue(){
    queueFront = -1;
	queueEnd = -1;
}

bool MyQueue::isEmpty(){
	return (counter == 0);
}

bool MyQueue::isFull(){
	return (counter == SIZE);
}

void MyQueue::enqueue(char ch){
	if (this->isFull()) {
		cout << "Queue full, cannot add!" << endl;
		return;
	} else if (this->isEmpty()) {
		queueEnd = 0;
		queueFront = 0;
		queue[queueEnd] = ch;
		++counter;
		return;
	} else {
		++queueEnd;
	} 
	if (queueEnd < 20) {
		queue[queueEnd] = ch;
	} else {
		queueEnd = 0; 
		queue[queueEnd] = ch;
	}
	++counter;
	return;
}


void MyQueue::dequeue(){
	if (this->isEmpty()) {
		cout << "Queue empty, cannot dequeue!" << endl;
		return;
	}
	if (queueFront < 20) {
		queue[queueFront] = '\0';
		++queueFront;
	} else {
		queueFront = 0;
		queue[queueFront] = '\0';
		++queueFront;
	}
	--counter;
	if (counter == 0) {
		queueFront = -1;
		queueEnd = -1;
	}
	return;
}

char MyQueue::peek(){
	if (this->isEmpty()) {
		cout << "Queue empty, cannot peek!" << endl;
		return '\0';
	}
	return queue[queueEnd];
}

int MyQueue::queueSize(){
    return counter;
}
