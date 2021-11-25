/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:07:30 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/23 20:47:42 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	match(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*nullstr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (match(s1[i], set) == 1 && s1[i] != '\0')
		i++;
	if (i == j + 1)
	{
		if (!(nullstr = (char *)malloc(1)))
			return (NULL);
		*nullstr = '\0';
		return (nullstr);
	}
	while (match(s1[j], set) == 1 && j >= 0)
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
