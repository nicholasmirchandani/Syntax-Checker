#include <iostream>
#ifndef GENSTACK_H
#define GENSTACK_H

enum StackError {STACK_FULL = 1, STACK_EMPTY};

template <typename T>
class GenStack {
    public:
        GenStack<T>();
        GenStack<T>(int maxSize);
        ~GenStack<T>();

        void push(T d);
        T pop();
        T peek();

        bool isFull();
        bool isEmpty();

        int size;
        int top;
        T *myArray;
};
#endif