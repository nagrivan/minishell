/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:12:22 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/13 18:07:04 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	n;
	size_t	len;

	len = ft_strlen(dst);
	i = 0;
	n = 0;
	if (size == 0 || len > size)
		return (ft_strlen(src) + size);
	if (size)
	{
		while (dst[n])
			++n;
		while (src[i] && n < size - 1)
		{
			dst[n] = src[i];
			++n;
			++i;
		}
	}
	dst[n] = '\0';
	return (ft_strlen(src) + len);
}
