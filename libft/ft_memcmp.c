/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:14:39 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/11 16:35:47 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	i = 0;
	a1 = (unsigned char *)arr1;
	a2 = (unsigned char *)arr2;
	if (!arr1 && !arr2)
		return (0);
	while (i < n)
	{
		if (a1[i] > a2[i])
			return (a1[i] - a2[i]);
		if (a1[i] < a2[i])
			return (a1[i] - a2[i]);
		++i;
	}
	return (0);
}
