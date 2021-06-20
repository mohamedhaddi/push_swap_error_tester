/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 19:48:52 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/21 00:34:00 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EMPTY -1
#define LEFT -1
#define RIGHT 1

typedef struct s_stack {
	int *values;
	int size;
	int top;
} t_stack;

typedef struct s_pop {
	int value;
	bool error;
} t_pop;

bool push(t_stack *stack, int value)
{
	if (stack->top >= stack->size - 1)
		return false;
	stack->top++;
	stack->values[stack->top] = value;
	return true;
}

t_pop pop(t_stack *stack)
{
	t_pop pop;

	if (stack->top == EMPTY)
		pop.error = true;
	else
	{
		pop.value = stack->values[stack->top];
		stack->top--;
		pop.error = false;
	}
	return pop;
}

void swap(t_stack *stack)
{
	int tmp;

	if (stack->size > 1)
	{
		tmp = stack->values[stack->top];
		stack->values[stack->top] = stack->values[stack->top - 1];
		stack->values[stack->top - 1] = tmp;
	}
}

void shift_down(t_stack *stack)
{
	int tmp;
	int i;
	
	i = 0;
	tmp = stack->values[i];
	while (i < stack->size - 1)
	{
		stack->values[i] = stack->values[i + 1];
		i++;
	}
	stack->values[i] = tmp;
}

void shift_up(t_stack *stack)
{
	int tmp;
	int i;
	
	i = stack->top;
	tmp = stack->values[i];
	while (i)
	{
		stack->values[i] = stack->values[i - 1];
		i--;
	}
	stack->values[i] = tmp;
}

void	check_error(bool is_error, char *error_msg, size_t msg_size)
{
	if (is_error)
	{
		write(2, error_msg, msg_size);
		exit(EXIT_FAILURE);
	}
}

t_stack create_stack(size_t size)
{
	t_stack stack;

	stack.values = malloc(sizeof(stack.values) * size);
	check_error(!stack.values, "Error\n", 7);
	stack.size = size;
	stack.top = -1;
	return stack;
}

void populate_stack(t_stack *stack, char **values)
{
	int value_num;
	int	new_value;
	bool push_status;

	push_status = true;
	value_num = stack->size;
	while (push_status)
	{
		new_value = atoi(values[value_num]);
		push_status = push(stack, new_value);
		value_num--;
	}
}

int main(int argc, char **argv)
{
	t_stack stack_a;
	t_stack stack_b;
	size_t stack_size;

	// TO-DO: consider using pop and push inside of swap and rotate, if current ones are slow.
	/* TO-DO: check if all arguments are valid:
	 * - if no arguments
	 * - if argument isn't int
	 * - if argument is overflow/underflow
	 * - if there are duplicates
	 */
	// TO-DO: free stacks before all exits
	// TO-DO: replace atoi
	// TO-DO: make immutable variables const
	/* TO-DO: when pop and push check if stacks are empty:
	 * - if pop returns false don't push
	 */

	stack_size = argc - 1;
	stack_a = create_stack(stack_size);
	stack_b = create_stack(stack_size);
	populate_stack(&stack_a, argv);

	// sort(&stack_a, &stack_b);

	// while (stack_b.top != EMPTY)
	//	push(&stack_a, pop(&stack_b).value);
	// TO-DO: print both stacks to check
	// while (stack_a.top != EMPTY)
	//	printf("%d\n", pop(&stack_a).value); // TO-DO: rmv printf
	// TO-DO: sort into stack a (b empty)
}
