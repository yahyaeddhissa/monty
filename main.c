#include "monty.h"

FILE *fd = NULL;

/**
 * main - runs monty bytecode interpreter
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
    void (*f)(stack_t **, unsigned int) = NULL;
    char *buffer = NULL, op[50] = {'\0'}, pushNum[50] = {'\0'}, *token = NULL;
    size_t length = 0;
    stack_t *stack = NULL;
    unsigned int line_number = 1;

    if (argc != 2)
        fprintf(stderr, "USAGE: monty file\n"), exit(EXIT_FAILURE);
    fd = fopen(argv[1], "r");
    if (!fd)
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]), exit(EXIT_FAILURE);
    for (; getline(&buffer, &length, fd) != EOF; line_number++)
    {
        token = strtok((buffer), " \t\n");
        if (!token)
        {
            free(buffer), buffer = NULL;
            continue;
        }
        strcpy(op, token);
        f = get_func(&stack, line_number, op);
        if (!f)
            fprintf(stderr, "Error: malloc failed\n"), close_error();
        if (strcmp(op, "push") == 0)
        {
            token = strtok(NULL, " \t\n");
            if (!token)
            {
                free(buffer), buffer = NULL, free_stack(&stack);
                fprintf(stderr, "L%d: usage: push integer\n", line_number), close_error();
            }
            strcpy(pushNum, token);
        }
        free(buffer), buffer = NULL;
        f(&stack, line_number);
        if (strcmp(op, "push") == 0)
            pushOp(&stack, line_number, pushNum);
    }
    free(buffer), fclose(fd), free_stack(&stack);
    return (EXIT_SUCCESS);
}

/**
 * get_func - finds function to use to execute the desired opcode
 * @stack: stack to operate on
 * @code: string used to find correct function
 * @l: line number of current opcode
 * Return: pointer to desired function
 */
void (*get_func(stack_t **stack, int l, char *code))(stack_t **, unsigned int)
{
    instruction_t instruction[] = {
        {"push", push},
        {"pall", pall},
        {"pint", pint},
        {"pop", pop},
        {"swap", swap},
        {"add", add},
        {"nop", nop}};
    int i = 0;

    while (strcmp(code, instruction[i].opcode) != 0)
    {
        i++;
        if (i > 7)
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", l, code);
            free_stack(stack);
            close_error();
        }
    }
    return (instruction[i].f);
}

/**
 * close_error - error handler
 */
void close_error(void)
{
    fclose(fd);
    exit(EXIT_FAILURE);
}

/**
 * pushOp - helper for push operation; sets value for new node
 * @stack: linked list stack to push to
 * @line_number: current line number of bytecode file
 * @pushNum: number to add to new node
 */
void pushOp(stack_t **stack, unsigned int line_number, char *pushNum)
{
    if (strcmp(pushNum, "0") == 0)
        (*stack)->n = 0;
    if (strcmp(pushNum, "0") != 0)
    {
        (*stack)->n = atoi(pushNum);
        if ((*stack)->n == 0 || (pushNum[0] != '-' && (*stack)->n == -1))
        {
            fprintf(stderr, "Error: L%d: usage: push integer\n", line_number);
            free_stack(stack);
            close_error();
        }
    }
}