/**
 * @file stack.c
 * @author Andrew Irvine (adi356@umsystem.edu)
 * @brief stack to hold numbers that will be reversed and it's functions 
 * @version 0.1
 * @date 2023-09-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include "stack.h"

//functions
int pop(Stack*);
void push(Stack*, int);
int isFull(Stack*);
int isEmpty(Stack*);

Stack createStack( Stack* stack, int capacity) {
    stack = (Stack*)malloc(sizeof(struct Stack));
    stack -> capacity = capacity;
    stack -> size = -1;
    stack -> array = (int*)malloc(stack->capacity * sizeof(int));

    //pointers to relevant functions
    stack -> pop = &pop;
    stack -> push = &push;
    stack -> isFull = &isFull;
    stack -> isEmpty = &isEmpty;

    return *stack; 
}

int pop(Stack* stack) {
    if(isEmpty(stack) == 1) {
        fprintf(stderr,"process %d: Attempt to pop element off empty stack.\n", getpid());
        return INT_MIN;
    }
    return stack -> array[stack -> size--];
}

void push(Stack* stack, int number) {
    if(isFull(stack)) {
        fprintf(stderr, "process %d: Attempt to push element into full stack.\n", getpid());
        printf("size: %d capacity: %d to be pushed: %d \n", stack -> size, stack -> capacity, number);
        abort();
    }
    stack -> size++;
    stack -> array[stack -> size] = number;
}

int isFull(Stack* self) {
    return self -> size == self -> capacity;
}

int isEmpty(Stack* stack) {
    return stack -> size == -1;
}



