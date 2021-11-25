/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:19:47 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/05 14:15:01 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (!src && !dst)
		return (NULL);
	if (src < dst)
	{
		while (len--)
			d[len] = s[len];
	}
	if (src > dst)
	{
		while (i < len)
		{
			d[i] = s[i];
			++i;
		}
	}
	return (dst);
}
