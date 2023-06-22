#include "monty.h"
/**
 * pint - Pushes an element onto the stack
 * @stack: Double pointer to the stack
 * @line_number: The line number in the Monty file
 */
void pint(stack_t **stack, unsigned int line_number)
{
	int value;
	if (*stack == NULL)
	{
		fprintf(stderr,"L%d: can't pint, stack empty\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	value = (*stack)->n;
	printf("%d\n", value);
}
