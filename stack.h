/**
 * @file stack.h
 * @author Andrew Irvine (adi356@umsystem.edu)
 * @brief stack typedef struct
 * @version 0.1
 * @date 2023-09-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STACK_H
#define STACK_H

struct Stack;

typedef struct Stack {
    int size;
    int capacity;
    int *array;

    int isPtrFull;
    int isPtrEmpty;

    int(*pop)(struct Stack*);
    void(*push)(struct Stack*, int);
    int(*isFull)(struct Stack*);
    int(*isEmpty)(struct Stack*);
}Stack;

Stack createStack(Stack*, int);

#endif 