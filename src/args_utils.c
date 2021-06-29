/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:53:14 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 16:54:08 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_integer(char *str)
{
	int i;

	i = 0;
	if (str[0] == '-' && str[1]) i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

bool	is_over_int(char *str)
{
	int i;
	int j;
	int len;
	bool is_negative;
	char* max_int = "2147483647";
	char last_digit = '7';

	i = 0;
	j = 0;
	len = ft_strlen(str);
	is_negative = str[i] == '-';
	if (is_negative) last_digit = '8';
	if (is_negative) i++;
	if (is_negative && len > 11) return true;
	if (is_negative && len < 11) return false;
	if (!is_negative && len > 10) return true;
	if (!is_negative && len < 10) return false;

	while (i < len - 1)
	{
		if (str[i] > max_int[j]) return true;
		else if (str[i] < max_int[j]) return false;
		i++;
		j++;
	}

	if (str[i] > last_digit) return true;

	return false;
}

char	*strip_one_plus(char *s)
{
	if (s[0] == '+')
		s++;
	return s;
}

bool	is_duplicate(int len, char **args)
{
	int i;	

	i = 0;
	while (i < len)
	{
		if (ft_strcmp(args[i], args[len]) == 0)
			return true;
		i++;
	}
	return false;
}

char *remove_trailing_zeros(char *s)
{
	int i;

	i = 0;
	while (s[i] == '0')
		i++;
	if (i && s[i] == '\0')
		return s + (i - 1);
	return s + i;
}
