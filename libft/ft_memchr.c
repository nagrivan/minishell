/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:54:43 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/05 16:10:34 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t	i;
	char	*a;

	i = 0;
	a = (char *)arr;
	while (i < n)
	{
		if (a[i] == (char)c)
			return (a + i);
		++i;
	}
	return (NULL);
}
