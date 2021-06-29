/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_over_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:26:16 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 19:05:01 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_index(int *i, bool is_negative)
{
	*i = 0;
	if (is_negative)
		*i = 1;
}

void	set_last_digit(char *last_digit, bool is_negative)
{
	*last_digit = '7';
	if (is_negative)
		*last_digit = '8';
}

bool	check_every_digit(int i, int len, char last_digit, char **strings)
{
	int		j;
	char	*str;
	char	*max_int;

	str = strings[0];
	max_int = strings[1];
	j = 0;
	while (i < len - 1)
	{
		if (str[i] > max_int[j])
			return (true);
		else if (str[i] < max_int[j])
			return (false);
		i++;
		j++;
	}
	if (str[i] > last_digit)
		return (true);
	return (false);
}

bool	is_over_int(char *str)
{
	char	*max_int;
	int		len;
	bool	is_negative;
	int		i;
	char	last_digit;

	max_int = "2147483647";
	len = ft_strlen(str);
	is_negative = str[0] == '-';
	init_index(&i, is_negative);
	set_last_digit(&last_digit, is_negative);
	if ((is_negative && len > 11) || (!is_negative && len > 10))
		return (true);
	if ((is_negative && len < 11) || (!is_negative && len < 10))
		return (false);
	return (check_every_digit(i, len, last_digit, (char *[2]){str, max_int}));
}
