/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:06:33 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/30 16:06:05 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_sorted(t_stack stack)
{
	int	i;

	i = 0;
	while (i < stack.top)
	{
		if (stack.values[i] < stack.values[i + 1])
			return (false);
		i++;
	}
	return (true);
}

void	three_sort(t_stack *stack_a)
{
	if (smaller_in_top(stack_a->values))
	{
		rotate_down_and_print(stack_a, "rra");
		swap_and_print(stack_a, "sa");
	}
	else if (smaller_in_middle(stack_a->values))
	{
		if (bigger_in_top(stack_a->values))
			rotate_up_and_print(stack_a, "ra");
		else if (bigger_in_bottom(stack_a->values))
			swap_and_print(stack_a, "sa");
	}
	else
	{
		if (bigger_in_middle(stack_a->values))
			rotate_down_and_print(stack_a, "rra");
		else if (bigger_in_top(stack_a->values))
		{
			rotate_up_and_print(stack_a, "ra");
			swap_and_print(stack_a, "sa");
		}
	}
}

void	five_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	i;
	int	smallest_val_index;

	while (!is_sorted(*stack_a))
	{
		i = 0;
		while (i < stack_a->size - 3)
		{
			smallest_val_index = get_smallest_val_index(stack_a);
			bring_smallest_to_top(stack_a, smallest_val_index);
			push_and_print(stack_b, pop(stack_a).value, "pb");
			i++;
		}
		if (!is_sorted(*stack_a))
			three_sort(stack_a);
		while (i)
		{
			push_and_print(stack_a, pop(stack_b).value, "pa");
			i--;
		}
	}
}

/*
 * max_num: the biggest number in stack_a (simplified) is stack_a->size - 1
 *
 * Then in a while loop, we shift right until all bits are 000000s,
 * we do this to know how many bits we have to check. so we will do max_bits
 * iterations, first iteration we'll start from sending the zeros in least
 * significant bit to stack_b, keep the ones in stack_a; and for each
 * iteration we'll move to the more significant bit.
 *
 * So in the next while loop, we loop max_bits times, at the first iteration,
 * i == 0, so the number isn't right-shifted; we & it with 1 (00000001)
 * so that all bits other than the last one (least significant one) becomes 0,
 * that way we can know if the last one is actually 0 or 1 (00000 or 00001),
 * if 0, we push it to stack_b, else it stays (rotate up) in stack_a.
 *
 * In the following iteration, we shift the number i times, so that the bit
 * that we want to check against &1 is now the least significant one.
 */
void	radix_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	max_num;
	int	max_bits;
	int	i;
	int	j;

	max_num = stack_a->size - 1;
	max_bits = 0;
	while ((max_num >> max_bits) != 0)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < stack_a->size)
		{
			if (((stack_a->simplified_values[stack_a->top] >> i) & 1) == 1)
				rotate_up_and_print(stack_a, "ra");
			else
				push_and_print(stack_b, pop(stack_a).value, "pb");
			j++;
		}
		while (stack_b->top != EMPTY)
			push_and_print(stack_a, pop(stack_b).value, "pa");
		i++;
	}
}

void	sort(t_stack *stack_a, t_stack *stack_b, int stack_size)
{
	if (stack_size > 5)
		radix_sort(stack_a, stack_b);
	else if (stack_size > 3)
		five_sort(stack_a, stack_b);
	else if (stack_size == 3)
		three_sort(stack_a);
	else if (stack_size == 2)
		rotate_up_and_print(stack_a, "ra");
}
