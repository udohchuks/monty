#include "monty.h"

/**
 * push - Pushes an element onto the stack
 * @stack: Double pointer to the stack
 * @line_number: The line number in the Monty file
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;
	char *argument;
       
	argument = strtok(NULL, " \t\n");
	(void) line_number;
	/* Create a new stack node */
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	/* Set the value of the new node */
	new_node->n = atoi(argument);
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	/* Update the stack pointer */
	*stack = new_node;
}
