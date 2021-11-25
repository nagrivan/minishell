/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:13:56 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/25 19:42:20 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (haystack == needle || (*needle == '\0' && len == 0))
		return ((char *)haystack);
	if ((!needle && !haystack) || len == 0)
		return (NULL);
	while (i <= len - ft_strlen(needle) && haystack[i] != '\0')
	{
		if (ft_memcmp(haystack + i, needle, ft_strlen(needle)) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
