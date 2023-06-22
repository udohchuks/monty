#include "monty.h"

FileData globalData = {NULL, NULL};

/**
 * main - Entry point
 * @argc: number of arg
 * @argv: arg vector
 * Return: 0
 */
int main(int argc, char *argv[])
{
	/*char *buffer;*/
	size_t buffer_size;
	ssize_t read;
	/*FILE *file;*/
	stack_t *stack = NULL;
	unsigned int line_number;
	char *opcode;
	void (*func)(stack_t **, unsigned int);
	char *rest;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	globalData.file = fopen(argv[1], "r");
	if (globalData.file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
        }

	globalData.buffer = NULL;
	buffer_size = 0;

	stack = NULL;
	line_number = 0;

	while ((read = getline(&globalData.buffer, &buffer_size, globalData.file)) != -1)
	{
		line_number++;

		/* Skip blank lines */
		if (read == 1 || (read == 2 && globalData.buffer[0] == ' '))
                        continue;

		/* Extract the opcode and its argument */
		opcode = strtok(globalData.buffer, " \t\n");
		/* Check if opcode is valid */
		if (opcode == NULL || opcode[0] == '#')
			continue;

		/* Get the opcode function */
		func = op_func(opcode);
		if (func == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			free_stack(stack);
			free(globalData.buffer);
			fclose(globalData.file);
			return (EXIT_FAILURE);
		}
	
		/* Execute the opcode function */
		func(&stack, line_number);

		rest = strtok(NULL, " \t\n");
		if (handle_additional_text(rest, line_number))
		{
			free_stack(stack);
			free(globalData.buffer);
			fclose(globalData.file);
			return (EXIT_FAILURE);
		}

	}
	free_stack(stack);
	free(globalData.buffer);
	fclose(globalData.file);
	return (EXIT_SUCCESS);
}

/**
 * handle_additional_text - handles extra text
 * @rest: rest
 * @line_number: line number
 * Return: 1 / 0
 */

int handle_additional_text(char *rest, unsigned int line_number)
{
	if (rest != NULL && rest[0] != '#' && rest[0] != '\n')
	{
		fprintf(stderr, "L%d: unexpected text after instruction\n", line_number);
		return (1);
	}
	return (0);
}
