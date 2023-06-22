#include "monty.h"

/**
 * sub - add top 2 node
 * @stack: stack
 * @line_number: line number
 */

void sub(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
	free_stack(*stack);
	free(globalData.buffer);
	fclose(globalData.file);
	exit(EXIT_FAILURE);
    }

    (*stack)->next->n -= (*stack)->n;
    pop(stack, line_number);
}
