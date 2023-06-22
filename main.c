#include "monty.h"
/**
 * main - Entry point
 * @argc: number of arg
 * @argv: arg vector
 * Return: 0
 */
int main(int argc, char *argv[])
{
	char *buffer;
	size_t buffer_size;
	ssize_t read;
	FILE *file;
	stack_t *stack = NULL;
	unsigned int line_number;
	char *opcode;
	void (*func)(stack_t **, unsigned int);

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
        }

	buffer = NULL;
	buffer_size = 0;

	stack = NULL;
	line_number = 0;

	while ((read = getline(&buffer, &buffer_size, file)) != -1)
	{
		line_number++;

		/* Skip blank lines */
		if (read == 1 || (read == 2 && buffer[0] == ' '))
                        continue;

		/* Extract the opcode and its argument */
		opcode = strtok(buffer, " \t\n");
		/* Check if opcode is valid */
		if (opcode == NULL || opcode[0] == '#')
			continue;

		/* Get the opcode function */
		func = op_func(opcode);
		if (func == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			free_stack(stack);
			free(buffer);
			fclose(file);
			return (EXIT_FAILURE);
		}

		/* Execute the opcode function */
		func(&stack, line_number);
	}
	free_stack(stack);
	free(buffer);
	fclose(file);
	return (EXIT_SUCCESS);
}
