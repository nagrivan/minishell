/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:37:52 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/23 20:36:07 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*subs;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len <= ft_strlen(s) - start)
		subs = (char *)malloc(len + 1);
	else
		subs = (char *)malloc(ft_strlen(s) - start + 1);
	if (!subs)
		return (NULL);
	while (s[i] && i < start + len)
	{
		subs[j] = s[i];
		i++;
		j++;
	}
	subs[j] = '\0';
	return (subs);
}
