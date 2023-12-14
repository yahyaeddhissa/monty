#include "monty.h"

void pallfunct(stack_td **stack, __attribute__((unused)) char *content, __attribute__((unused)) int line_number)
{
    stack_td *currentnode = (*stack);

    while (currentnode != NULL)
    {
        printf("%d\n", currentnode->n);
        currentnode = currentnode->next;
    }

    return;
}