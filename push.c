#include "monty.h"

void pushfunct(stack_td **stack, char *content, int line_number)
{
    stack_td *newnode = malloc(sizeof(stack_td));
    int num = 0;

    if (newnode == NULL)
        MALLOC_ERROR();

    if ((content != NULL && isdigit(content[0])) || (content != NULL && content[0] == '-' && isdigit(content[1])))
    {
        num = atoi(content);

        newnode->prev = NULL;
        newnode->n = num;
        newnode->next = (*stack);

        if ((*stack) != NULL && stack != NULL)
            (*stack)->prev = newnode;

        (*stack) = newnode;
        return;
    }
    else
        PUSH_USAGE_ERROR(line_number);
}