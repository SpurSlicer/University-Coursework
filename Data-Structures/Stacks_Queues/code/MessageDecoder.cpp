//g++ -std=c++11 app/main.cpp code/MessageDecoder.cpp code/MessageDecoder.hpp code/MyQueue.cpp code/MyQueue.hpp code/MyStack.cpp code/MyStack.hpp
#include <iostream>
#include <cstdlib>
#include "MessageDecoder.hpp"

using namespace std;
# define SIZE 50

MessageDecoder::MessageDecoder()
{
	my_queue = new MyQueue();
	my_stack = new MyStack();
}

MessageDecoder::~MessageDecoder()
{
    delete my_queue;
    delete my_stack;	
}

/*
    generate_operator_queue(string jumbled_str)

    Takes the jumbled string as the input parameter and stores all the allowed operators in my_queue
*/
void MessageDecoder::generate_operator_queue(std::string jumbled_str){
    int i = 0;
    while (!my_queue->isFull() && (i < jumbled_str.length())) {
        if ((jumbled_str[i] == '+') || (jumbled_str[i] == '*') || (jumbled_str[i] == '-')) {
            my_queue->enqueue(jumbled_str[i]);
        }
        ++i;
    }

    return;
}

/*
    generate_postfix(string jumbled_str)

    Takes the jumbled string as the input parameter and computes a postfix expression using the populated my_queue
    returns a postfix expression
*/
string MessageDecoder::generate_postfix(std::string jumbled_str){
    //TODO
	string postfix = "";
    int i = 0, c = 0;
    while (i < jumbled_str.length()) {
        if ((c == 2) && (!my_queue->isEmpty())) {
            postfix += my_queue->getQueue()[my_queue->getQueueFront()];
            my_queue->dequeue();
            c = 0;
        } else if (isdigit(jumbled_str[i])) {
            postfix += jumbled_str[i];
            ++c;
        }
        ++i;
    }
    while (!my_queue->isEmpty()) {
        postfix += my_queue->peek();
        my_queue->dequeue();
    }
    return postfix;
}


/* 
    evaluate_postfix(string postfix) 

    Takes the post fix string as an input parameter and evaluates the post fix string. 
    returns an integer after evaluating the postfix expression
*/

int MessageDecoder::evaluate_postfix(std::string postfix) {
    //TODO
    MyStack s;
    int i = 0, x = 0, y = 0;
    while (i < postfix.length()) {
        if (isdigit(postfix[i])) {
            s.push(postfix[i]-'0');
        } else if ((postfix[i] == '-') || (postfix[i] == '*') || (postfix[i] == '+')) {
            switch (postfix[i]) {
                case '-':
                    x = s.peek()->val;
                    s.pop();
                    y = s.peek()->val;
                    s.pop();
                    s.push(y-x);
                    break;
                case '+':
                    x = s.peek()->val;
                    s.pop();
                    y = s.peek()->val;
                    s.pop();
                    s.push(x+y);
                    break;
                case '*':
                    x = s.peek()->val;
                    s.pop();
                    y = s.peek()->val;
                    s.pop();
                    s.push(x*y);
                    break;
            }
        }
        ++i;
    }
    i = s.peek()->val;
    s.~MyStack();
    return i;
}

//For Testing purposes only!
MyQueue* MessageDecoder::getQueue(){
    return my_queue;
}

//For Testing purposes only!
MyStack* MessageDecoder::getStack(){
    return my_stack;
}