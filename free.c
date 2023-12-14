#include "monty.h"

/**
 * free_stack - free memory allocated for stack
 * @stack: ptr to stack (linked list)
 * Return: void
 */

void free_stack(stack_t **stack)
{
    if (!(stack) || !(*stack))
    {
        return;
    }
    free_stack(&((*stack)->next));
    free(*stack);
    *stack = NULL;
}