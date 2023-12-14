#include "monty.h"

instruction_t cases[] = {
    {"push", pushfunct},
    {"pall", pallfunct},
    {NULL, NULL}};

instruction_t *get_cases()
{
    return (cases);
}