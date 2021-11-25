/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:12:52 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/17 16:58:16 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		num_of_dig(int n)
{
	int		i;

	if (n == 0 || n == -0)
		return (1);
	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int		abs_(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (!(str = (char *)malloc(num_of_dig(n) + 1)))
		return (NULL);
	i = num_of_dig(n) - 1;
	if (n < 0)
		str[0] = '-';
	str[i + 1] = '\0';
	if (n == 0 || n == -0)
		str[i] = '0';
	while (i >= 0 && n != 0)
	{
		str[i] = abs_(n % 10) + '0';
		n /= 10;
		i--;
	}
	return (str);
}
