#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "monty.h"

#define BUFFER_SIZE 1024

/**
 * error_usage - prints usage message and exits
 *
 * Return: nothing
 */
void error_usage(void)
{
    fprintf(stderr, "USAGE: monty file\n");
    exit(EXIT_FAILURE);
}

/**
 * file_error - prints file error message and exits
 * @argv: argv given by main
 *
 * Return: nothing
 */
void file_error(char *argv)
{
    fprintf(stderr, "Error: Can't open file %s\n", argv);
    exit(EXIT_FAILURE);
}

int status = 0;

/**
 * main - entry point
 * @argv: list of arguments passed to our program
 * @argc: amount of args
 *
 * Return: nothing
 */
int main(int argc, char **argv)
{
    FILE *file;
    char buffer[BUFFER_SIZE];
    char *str = NULL;
    stack_t *stack = NULL;
    unsigned int line_cnt = 1;

    global.data_struct = 1;
    if (argc != 2)
        error_usage();

    file = fopen(argv[1], "r");

    if (!file)
        file_error(argv[1]);

    while (fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
        if (status)
            break;
        if (*buffer == '\n')
        {
            line_cnt++;
            continue;
        }
        str = strtok(buffer, " \t\n");
        if (!str || *str == '#')
        {
            line_cnt++;
            continue;
        }
        global.argument = strtok(NULL, " \t\n");
        opcode(&stack, str, line_cnt);
        line_cnt++;
    }
    fclose(file);
    free_stack(stack);
    exit(status);
}
