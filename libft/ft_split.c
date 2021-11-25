/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:01:09 by ralverta          #+#    #+#             */
/*   Updated: 2020/11/23 20:56:32 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_words(char *s, char c)
{
	int				i;
	unsigned int	num;

	i = 0;
	num = 0;
	if (c == '\0' && s[0] != '\0')
		return (1);
	if (s[0] == '\0')
		return (0);
	while (s[i] == c)
		++i;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c) || s[i + 1] == '\0')
			num++;
		i++;
	}
	return (num);
}

static int	len_of_word(char const *s, char c, unsigned int *j)
{
	size_t	len;

	len = 0;
	while (s[*j] != c && s[*j] != '\0')
	{
		len++;
		(*j)++;
	}
	return (len);
}

static void	*mem_free(char **words, unsigned int i)
{
	while (i--)
		free(words[i]);
	free(words);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char			**words;
	unsigned int	i;
	unsigned int	j;
	unsigned int	count;

	if (!s)
		return (NULL);
	count = num_of_words((char *)s, c);
	i = 0;
	j = 0;
	if (!(words = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		while (s[j] == c && s[j])
			j++;
		if (s[j])
			words[i] = ft_substr(s, j, len_of_word(s, c, &j));
		if (words[i] == NULL)
			return (mem_free(words, i));
		i++;
	}
	words[i] = 0;
	return (words);
}
