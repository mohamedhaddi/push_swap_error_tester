/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:49:40 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 17:04:52 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    free_double_pointer(char **ptr)
{
    int i;

    i = 0;
    while (ptr[i])
		free(ptr[i++]);
    free(ptr);
}

void	check_error(bool is_error)
{
	if (is_error)
	{
		write(2, "Error\n", 6);
		exit(255);
	}
}

