/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:00:02 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 18:18:05 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	push(t_stack *stack, t_value value)
{
	if (stack->top >= stack->size - 1)
		return (false);
	stack->top++;
	stack->values[stack->top] = value.real_value;
	stack->simplified_values[stack->top] = value.simplified_value;
	return (true);
}

void	push_and_print(t_stack *stack, t_value value, char *operation)
{
	push(stack, value);
	printf("%s\n", operation);
}
