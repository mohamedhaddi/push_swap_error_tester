/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:50:30 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 17:48:26 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isfullyoccupied(const char *s, size_t size)
{
	int	itis;

	itis = 1;
	while (size--)
	{
		if (!*s)
			itis = 0;
		s++;
	}
	return (itis);
}

void	check_size(size_t *size, int *len, size_t dstlen, size_t srclen)
{
	if (*size >= dstlen)
	{
		*len = dstlen + srclen;
		*size -= dstlen;
	}
	else
	{
		*len = srclen + *size;
		*size = 0;
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		len;
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dst && !size)
		return (srclen);
	if (isfullyoccupied(dst, size))
		return (srclen + size);
	dstlen = ft_strlen(dst);
	check_size(&size, &len, dstlen, srclen);
	dst += dstlen;
	*dst = '\0';
	while (size-- > 1 && *src)
		*(dst++) = *(src++);
	*dst = '\0';
	return (len);
}
