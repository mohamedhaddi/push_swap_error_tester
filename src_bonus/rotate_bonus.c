/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:01:15 by mhaddi            #+#    #+#             */
/*   Updated: 2021/07/04 03:52:26 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	rotate_down(t_stack *stack)
{
	int	tmp;
	int	tmp_simplified;
	int	i;

	i = 0;
	tmp = stack->values[i];
	tmp_simplified = stack->simplified_values[i];
	while (i < stack->top)
	{
		stack->values[i] = stack->values[i + 1];
		stack->simplified_values[i] = stack->simplified_values[i + 1];
		i++;
	}
	stack->values[i] = tmp;
	stack->simplified_values[i] = tmp_simplified;
}

void	rotate_down_and_print(t_stack *stack, char *operation)
{
	rotate_down(stack);
	printf("%s\n", operation);
}

void	rotate_up(t_stack *stack)
{
	int	tmp;
	int	tmp_simplified;
	int	i;

	if (stack->top >= 0)
	{
		i = stack->top;
		tmp = stack->values[i];
		tmp_simplified = stack->simplified_values[i];
		while (i)
		{
			stack->values[i] = stack->values[i - 1];
			stack->simplified_values[i] = stack->simplified_values[i - 1];
			i--;
		}
		stack->values[i] = tmp;
		stack->simplified_values[i] = tmp_simplified;
	}
}

void	rotate_up_and_print(t_stack *stack, char *operation)
{
	rotate_up(stack);
	printf("%s\n", operation);
}
