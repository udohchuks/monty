#include "monty.h"

/**
 * opcode_mod - mod top 2 node
 * @stack: stack
 * @line_number: line number
 */

void opcode_mod(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
	free_stack(*stack);
	free(globalData.buffer);
	fclose(globalData.file);
	exit(EXIT_FAILURE);
    }
    if ((*stack)->n == 0)
    {
	    fprintf(stderr, "L%d: division by zero\n", line_number);
	    free_stack(*stack);
	    free(globalData.buffer);
	    fclose(globalData.file);
	    exit(EXIT_FAILURE);
    }

    (*stack)->next->n %= (*stack)->n;
    pop(stack, line_number);
}
