#include "stack.h"

Stack *create_stack(int capacity) {
    if(capacity <= 0) return NULL;

    Stack *stack = malloc(sizeof(Stack));
    // if malloc fails then return NULL
    if(stack == NULL) return NULL;

    stack->collection = malloc(sizeof(int) * capacity);
    if(stack->collection == NULL) {
        free(stack);
        return NULL;
    }
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

void destroy_stack(Stack *stack) {
    free(stack->collection);
    free(stack);
}

bool is_full(Stack *stack) {
    return stack->capacity == stack->size;
}

bool is_empty(Stack *stack) {
    return stack->size == 0;
}

bool push(Stack *stack, int item) {
    if (is_full(stack) == true) {
        int* tmp = realloc(stack->collection, (stack->capacity + BUF) * sizeof(int));
        if(tmp == NULL) {
            free(stack);
            fprintf(stderr, "Error while reallocating memory for stack");
            return false;
        } else {
            stack->collection = tmp;
            stack->capacity += BUF;
        }
    };
    stack->collection[stack->size] = item;
    stack->size++;
    return true;
}

bool peek(Stack *stack, int *item) {
    if(is_empty(stack)) return false;
    *item = stack->collection[stack->size - 1];
    return true;
}

bool pop(Stack *stack, int *item) {
    if(is_empty(stack)) return false;
    stack->size--;
    *item = stack->collection[stack->size];
    return true;
}