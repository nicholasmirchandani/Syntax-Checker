#include "GenStack.h"
#include <iostream>
template <typename T>
GenStack<T>::GenStack() {
    myArray = new T[128];
    size = 128;
    top = -1;
}

template <typename T>
GenStack<T>::GenStack(int maxSize) {
    myArray = new T[maxSize];
    size = maxSize;
    top = -1;
}

template <typename T>
GenStack<T>::~GenStack() {
    delete[] myArray;
}

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

template <typename T>
T GenStack<T>::pop() {
    if(isEmpty()) {
        throw StackError::STACK_EMPTY;
        return 0;
    }
    return myArray[top--];
}

template <typename T>
T GenStack<T>::peek() {
    if(isEmpty()) {
        throw StackError::STACK_EMPTY;
        return 0;
    }
    return myArray[top];
}

template <typename T>
bool GenStack<T>::isFull() {
    return (top == size-1);
}

template <typename T>
bool GenStack<T>::isEmpty() {
    return (top == -1);
}