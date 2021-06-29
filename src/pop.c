/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:00:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 17:00:44 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_pop pop(t_stack *stack)
{
	t_pop pop;

	if (stack->top == EMPTY)
		pop.error = true;
	else
	{
		pop.value.real_value = stack->values[stack->top];
		pop.value.simplified_value = stack->simplified_values[stack->top];
		stack->top--;
		pop.error = false;
	}
	return pop;
}

