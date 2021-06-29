/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:56:53 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 17:05:55 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void populate_stack(t_stack *stack, char **values)
{
	int value_num;
	t_value	new_value;
	bool push_status;

	new_value.simplified_value = -1;
	push_status = true;
	value_num = stack->size - 1;
	while (value_num >= 0)
	{
		new_value.real_value = ft_atoi(values[value_num]);
		push_status = push(stack, new_value);
		value_num--;
	}
}

t_stack create_stack(size_t size)
{
	t_stack stack;

	stack.values = malloc(sizeof(*stack.values) * size);
	check_error(!stack.values);
	stack.simplified_values = malloc(sizeof(*stack.values) * size);
	check_error(!stack.simplified_values);
	stack.size = size;
	stack.top = -1;
	return stack;
}

void	simplify_stack(t_stack *stack)
{
	t_value value;

	int i = 0;
	while (i < stack->size)
	{
		int j = 0;
		value.simplified_value = 0;
		while (j < stack->size)
		{
			if (stack->values[i] > stack->values[j])
				value.simplified_value++;
			j++;
		}
		stack->simplified_values[i] = value.simplified_value;
		i++;
	}
}

void	destroy_stack(t_stack *stack)
{
	free(stack->values);
	free(stack->simplified_values);
}

