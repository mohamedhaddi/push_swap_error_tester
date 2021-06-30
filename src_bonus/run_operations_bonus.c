/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_operations_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 03:59:37 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/30 04:10:43 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

bool	is_swap_a(char *operation)
{
	return (ft_strcmp(operation, "sa") == 0
		|| ft_strcmp(operation, "ss") == 0);
}

bool	is_swap_b(char *operation)
{
	return (ft_strcmp(operation, "sb") == 0
		|| ft_strcmp(operation, "ss") == 0);
}

bool	is_push_a(char *operation)
{
	return (ft_strcmp(operation, "pa") == 0);
}

bool	is_push_b(char *operation)
{
	return (ft_strcmp(operation, "pb") == 0);
}

void	run_operations(
		t_stack *stack_a, t_stack *stack_b, char **user_ops, int count_ops)
{
	int	i;

	i = 0;
	while (i < count_ops)
	{
		if (is_swap_a(user_ops[i]))
			swap(stack_a);
		if (is_swap_b(user_ops[i]))
			swap(stack_b);
		if (is_rotate_a(user_ops[i]))
			rotate_up(stack_a);
		if (is_rotate_b(user_ops[i]))
			rotate_up(stack_b);
		if (is_reverse_rotate_a(user_ops[i]))
			rotate_down(stack_a);
		if (is_reverse_rotate_b(user_ops[i]))
			rotate_down(stack_b);
		if (is_push_a(user_ops[i]))
			push(stack_a, pop(stack_b).value);
		if (is_push_b(user_ops[i]))
			push(stack_b, pop(stack_a).value);
		i++;
	}
}
