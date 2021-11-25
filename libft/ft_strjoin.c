/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:48:46 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/16 21:10:30 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sum;
	size_t	size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(sum = (char *)malloc(size + 1)))
		return (NULL);
	while (s1[i])
	{
		sum[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		sum[i] = s2[j];
		i++;
		j++;
	}
	sum[i] = '\0';
	return (sum);
}
