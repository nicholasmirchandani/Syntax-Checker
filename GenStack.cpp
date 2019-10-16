/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 3: Syntax Checker
Genstack is the stack class that auto resizes for more data and works with any data type using templates.
*/
#include "GenStack.h"
#include <iostream>

//Default constructor
template <typename T>
GenStack<T>::GenStack() {
    myArray = new T[128];
    size = 128;
    top = -1;
}

//Overloaded constructor
template <typename T>
GenStack<T>::GenStack(int maxSize) {
    myArray = new T[maxSize];
    size = maxSize;
    top = -1;
}

//Destructor
template <typename T>
GenStack<T>::~GenStack() {
    delete[] myArray;
}

/*
    Pushes value to the stack
    d: data value to push to the stack
*/
template <typename T>
void GenStack<T>::push(T d) {
    if(isFull()) {
        T* newArray = new T[size * 2]; //Doubles size every time you reach the limit
        for(int i = 0; i <= top; ++i) {
            newArray[i] = myArray[i];
        }
        myArray = 0; //Setting myArray to 0 for security reasons
        delete[] myArray;
        myArray = newArray;
        size = size * 2;
    }
    myArray[++top] = d;
}

/*
    Pops value off of the stack
    Returns value popped off of the stack
*/
template <typename T>
T GenStack<T>::pop() {
    if(isEmpty()) {
        throw StackError::STACK_EMPTY;
        return 0;
    }
    return myArray[top--];
}

/*
    Peeks at the top value of the stack
    Returns value at the top of the stack without popping it
*/
template <typename T>
T GenStack<T>::peek() {
    if(isEmpty()) {
        throw StackError::STACK_EMPTY;
        return 0;
    }
    return myArray[top];
}

/*
    Checks if the stack is full
    Returns true if full, false otherwise
*/
template <typename T>
bool GenStack<T>::isFull() {
    return (top == size-1);
}

/*
    Checks if the stack is empty
    Returns true if empty, false otherwise
*/
template <typename T>
bool GenStack<T>::isEmpty() {
    return (top == -1);
}