#include <stdlib.h>
#include <assert.h>
#include "stack.h"

t_stack createStack(int size)
{
    // the size of the stack must be positive
    assert(size > 0);
    t_stack stack;
    stack.size = size;
    stack.nbElts = 0;
    stack.values = (int *)malloc(size * sizeof(int));
    return stack;
}

void push(t_stack *p_stack, int value)
{
    // the stack must not be full
    assert(p_stack->nbElts < p_stack->size);
    p_stack->values[p_stack->nbElts] = value;
    p_stack->nbElts++;
    return;
}

int pop(t_stack *p_stack)
{
    // the stack must not be empty
    assert(p_stack->nbElts > 0);
    p_stack->nbElts--;
    return p_stack->values[p_stack->nbElts];
}

int top(t_stack stack)
{
    // the stack must not be empty
    assert(stack.nbElts > 0);
    return stack.values[stack.nbElts - 1];
}
