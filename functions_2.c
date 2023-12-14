#include "monty.h"

/**
 * push - adds an element to a stack
 * @stack: linked list stack to push to
 * @line_number: current line number of bytecode file
 */
void push(stack_t **stack, unsigned int line_number)
{
    stack_t *newNode;

    newNode = malloc(sizeof(stack_t));

    if (!newNode)
    {
        fprintf(stderr, "Error: malloc failed\n");
        free_stack(stack);
        close_error();
    }
    (void)line_number;

    if (*stack)
        (*stack)->prev = newNode;

    newNode->prev = NULL;
    newNode->next = *stack;
    newNode->n = 0;
    *stack = newNode;
}

/**
 * pop - removes the first element of the stack
 * @stack: linked list stack to pop
 * @line_number: current line number of bytecode file
 */
void pop(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

    temp = *stack;
    if (!(*stack))
    {
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
        fclose(fd);
        free_stack(stack);
        exit(EXIT_FAILURE);
    }

    *stack = temp->next;
    if (*stack)
        (*stack)->prev = NULL;
    free(temp);
}

/**
 * swap - swaps the two top elements of a stack
 * @stack: linked list stack to swap
 * @line_number: current line number of bytecode file
 */
void swap(stack_t **stack, unsigned int line_number)
{
    int temp = (*stack)->n;

    if (!(*stack) || !(*stack)->next)
    {
        fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
        close_error();
        exit(EXIT_FAILURE);
    }

    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = temp;
}

/**
 * add - adds the first two elements of a stack, replaces both with sum
 * @stack: linked list stack to add
 * @line_number: current line number of bytecode file
 */
void add(stack_t **stack, unsigned int line_number)
{
    stack_t *temp = *stack;

    if (!temp || !temp->next)
    {
        fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
        free_stack(stack);
        close_error();
    }

    temp->next->n += temp->n;
    *stack = temp->next;
    (*stack)->prev = NULL;
    free(temp);
}