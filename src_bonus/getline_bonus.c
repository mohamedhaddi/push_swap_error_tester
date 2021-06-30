/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 03:58:18 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/30 04:11:45 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

char	*ft_getline(void)
{
	char	c;
	char	*line;
	char	*tmp;

	line = malloc(1);
	*line = '\0';
	while (1)
	{
		if (!read(0, &c, 1))
		{
			tmp = line;
			line = ft_strjoin(tmp, "EOF");
			free(tmp);
			return (line);
		}
		tmp = line;
		line = ft_strjoin(tmp, (char [2]){c, '\0'});
		free(tmp);
		if (c == '\n')
			return (line);
	}
}
