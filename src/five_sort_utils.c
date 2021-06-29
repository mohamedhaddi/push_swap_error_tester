/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_sort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:11:15 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 17:12:09 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_smallest_val_index(t_stack *stack)
{
	int i;
	int smallest;
	int smallest_index;

	i = 0;
	smallest_index = 0;
	smallest = 2147483647;
	while (i <= stack->top)
	{
		if (stack->values[i] < smallest)
		{
			smallest = stack->values[i];
			smallest_index = i;
		}
		i++;
	}
	return smallest_index;
}

void bring_smallest_to_top(t_stack *stack_a, int smallest_val_index)
{
	if (smallest_val_index == 0)
		rotate_down_and_print(stack_a, "rra");
	else if (smallest_val_index == 1)
	{
		rotate_down_and_print(stack_a, "rra");
		rotate_down_and_print(stack_a, "rra");
	}
	else if (smallest_val_index == 2)
	{
		if (stack_a->top == 4)
			rotate_up_and_print(stack_a, "ra");
		swap_and_print(stack_a, "sa");
	}
	else if (stack_a->top == 4 && smallest_val_index == 3)
		swap_and_print(stack_a, "sa");
}

