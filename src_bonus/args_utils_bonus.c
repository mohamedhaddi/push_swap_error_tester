/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:53:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 20:05:09 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

bool	is_integer(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1])
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

char	*strip_one_plus(char *s)
{
	if (s[0] == '+')
		s++;
	return (s);
}

bool	is_duplicate(int len, char **args)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_strcmp(args[i], args[len]) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	*remove_trailing_zeros(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '0')
		i++;
	if (i && s[i] == '\0')
		return (s + (i - 1));
	return (s + i);
}
