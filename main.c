#include "monty.h"

/**
 * main - monty language interpreter
 * @argc: argument count
 * @argv: argument values
 *
 * Return: 0 when exiting
 */

int main(int argc, char **argv)
{
    stack_td *stack = NULL;
    ssize_t readBytes;
    char *file_content = calloc(30000, 1), *lines[4000] = {NULL}, *filepath = NULL;
    const char line_delimiter[] = "\n";
    int i = 1, fd;

    if (file_content == NULL)
        MALLOC_ERROR();
    if (argc == 2)
    {
        filepath = argv[1];
        fd = open(filepath, O_RDONLY);
        if (fd < 0)
            OPEN_ERROR(filepath);

        readBytes = read(fd, file_content, 1024);
        if (readBytes < 0)
        {
            close(fd);
            return (0);
        }

        lines[0] = strtok(file_content, line_delimiter);
        if (lines[0] == NULL)
            free(file_content);
        else
        {
            for (i = 1; lines[i - 1] != NULL; i++)
            {
                lines[i] = strtok(NULL, line_delimiter);
            }

            for (i = 0; lines[i] != NULL; i++)
            {
                checkinstruction(lines[i], (&stack), (i + 1));
            }
            free(file_content);
            freestack(stack);
            close(fd);
        }
    }
    if (argc != 2)
    {
        free(file_content);
        free(stack);
        USAGE_ERROR();
    }
    return (0);
}