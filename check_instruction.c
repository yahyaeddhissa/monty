#include "monty.h"

/**
 * checkinstruction - monty language interpreter
 *
 * Return: 0 when exiting
 */

stack_td *checkinstruction(char *line, stack_td **stack, int line_number)
{
    char *command[32] = {NULL};
    const char token_delimiter[] = " \t";
    int i = 1;
    instruction_t *cases = get_cases();

    command[0] = strtok(line, token_delimiter);
    if (command[0] == NULL)
        return (*stack);
    else
        command[1] = strtok(NULL, token_delimiter);

    i = 0;
    while (cases[i].opcode != NULL)
    {
        if (strcmp(cases[i].opcode, command[0]) == 0)
        {
            cases[i].f(stack, command[1], line_number);
            break;
        }
        i++;
    }
    if (cases[i].opcode == NULL)
        INVALID_INSTRUCTION_ERROR(line_number, command[0]);

    return (*stack);
}