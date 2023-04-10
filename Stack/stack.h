#ifndef MY_STACK_H
#define MY_STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BUF 10

typedef struct {
    int *collection;
    int capacity;
    int size;
} Stack;

Stack *create_stack(int capacity);
void destroy_stack(Stack *stack);
bool is_full(Stack *stack);
bool is_empty(Stack *stack);
bool pop(Stack *stack, int *item);
bool push(Stack *stack, int item);
bool peek(Stack *stack, int *item);
#endif //MY_STACK_H
