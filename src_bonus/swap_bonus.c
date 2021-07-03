/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:00:50 by mhaddi            #+#    #+#             */
/*   Updated: 2021/07/03 19:04:51 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	swap(t_stack *stack)
{
	int	tmp;
	int	tmp_simplified;

	if (stack->top > 0)
	{
		tmp = stack->values[stack->top];
		tmp_simplified = stack->simplified_values[stack->top];
		stack->values[stack->top] = stack->values[stack->top - 1];
		stack->simplified_values[stack->top]
			= stack->simplified_values[stack->top - 1];
		stack->values[stack->top - 1] = tmp;
		stack->simplified_values[stack->top - 1] = tmp_simplified;
	}
}

void	swap_and_print(t_stack *stack, char *operation)
{
	swap(stack);
	printf("%s\n", operation);
}
