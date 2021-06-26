/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:13:13 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 17:51:09 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strncmp_mod(const char *s1, const char *s2, size_t n)
{
	while (n && *s2)
	{
		if (*(unsigned char *)s1++ != *(unsigned char *)s2++)
			return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
		n--;
	}
	if (!*s2)
		return (0);
	else
		return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*hs;

	if (!haystack && !len && needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	hs = haystack;
	while (*hs && len)
	{
		if (*hs == *needle)
			if (!ft_strncmp_mod(hs, needle, len))
				return ((char *)hs);
		hs++;
		len--;
	}
	return (NULL);
}
