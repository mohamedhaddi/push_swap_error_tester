/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:28:50 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 17:53:19 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*bgn_trimmer(char *str1, char const *set)
{
	size_t	i;
	size_t	set_len;

	set_len = ft_strlen(set);
	while (*str1)
	{
		i = 0;
		while (i < set_len)
		{
			if (*str1 == set[i])
			{
				str1++;
				break ;
			}
			i++;
		}
		if (i == set_len)
			break ;
	}
	return (str1);
}

static char	*end_trimmer(char *str2, char const *set)
{
	size_t	i;
	size_t	set_len;

	set_len = ft_strlen(set);
	while (*str2)
	{
		i = 0;
		while (i < set_len)
		{
			if (*str2 == set[i])
			{
				str2--;
				break ;
			}
			i++;
		}
		if (i == set_len)
			break ;
	}
	return (str2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str1;
	char	*str2;
	char	*str;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set || !*set || !*s1)
		return (ft_strdup(s1));
	str1 = (char *)s1;
	str1 = bgn_trimmer(str1, set);
	if (!*(str1))
		return (ft_strdup(""));
	str2 = (char *)s1 + ft_strlen(s1) - 1;
	str2 = end_trimmer(str2, set);
	len = str2 - str1 + 1;
	str = malloc((sizeof(char) * len) + sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = *(str1++);
	str[len] = '\0';
	return (str);
}
