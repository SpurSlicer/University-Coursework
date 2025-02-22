#include <iostream>
#include <cstdlib>
#include <iostream>
#include "MyStack.hpp"

using namespace std;

MyStack::MyStack()
{
	head = nullptr;
}

MyStack::~MyStack()
{
    while(!this->isEmpty())
        this->pop();
}

bool MyStack::isEmpty()
{
	return (head == nullptr);
}

void MyStack::push(int val)
{
    Node* nn = new Node;
    nn->val = val;
    nn->next = head;
	head = nn;
	return;
}

void MyStack::pop()
{   
    if(!this->isEmpty())
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    else
    {
        cout<<"Stack empty, cannot pop an item!"<<endl;
    }
	return;
}

Node* MyStack::peek()
{
	if (!this->isEmpty()) {
		return head;
	} else {
		cout << "Stack empty, cannot peek!" << endl;
		return nullptr;
	}
}
