/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ops_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 04:01:15 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/30 04:01:33 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

bool	is_rotate_a(char *operation)
{
	return (ft_strcmp(operation, "ra") == 0
		|| ft_strcmp(operation, "rr") == 0);
}

bool	is_rotate_b(char *operation)
{
	return (ft_strcmp(operation, "rb") == 0
		|| ft_strcmp(operation, "rr") == 0);
}

bool	is_reverse_rotate_a(char *operation)
{
	return (ft_strcmp(operation, "rra") == 0
		|| ft_strcmp(operation, "rrr") == 0);
}

bool	is_reverse_rotate_b(char *operation)
{
	return (ft_strcmp(operation, "rrb") == 0
		|| ft_strcmp(operation, "rrr") == 0);
}
