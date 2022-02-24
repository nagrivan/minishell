/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:42:45 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/03 15:42:48 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cleaning(char *str, int first, int last)
{
	char	*res;
	char	*tmp;
	char	*strdup;

	res = 0;
	str[first] = 0;
	str[last] = 0;
	res = ft_strdup(str);
	tmp = res;
	strdup = ft_strdup(str + first + 1);
	res = ft_strjoin(tmp, strdup);
	free(tmp);
	free(strdup);
	strdup = 0;
	tmp = 0;
	if (ft_strlen(str) - 1 != last)
	{
		tmp = res;
		strdup = ft_strdup(str + last + 1);
		res = ft_strjoin(tmp, strdup);
		free(tmp);
		free(strdup);
	}
	return (res);
}

static char	*single_quotes(char *str, int *i, char *token)
{
	int		first;
	int		last;
	char	*res;
	char	*tmp;

	tmp = ft_strdup(str);
	if (str != token)
		free(str);
	first = *i;
	while (tmp[first] != '\'')
		first++;
	last = first + 1;
	while (tmp[last] != '\'')
		last++;
	res = cleaning(tmp, first, last);
	*i = last - 1;
	free(tmp);
	return (res);
}

static char	*double_quotes(char *str, int *i, char *token)
{
	int		first;
	int		last;
	char	*res;
	char	*tmp;

	tmp = ft_strdup(str);
	if (str != token)
		free(str);
	first = *i;
	while (tmp[first] != '\"')
		first++;
	last = first + 1;
	while (tmp[last] != '\"')
		last++;
	res = cleaning(tmp, first, last);
	*i = last - 1;
	free(tmp);
	return (res);
}

char	*clean_all_quotes(char *token)
{
	int		i;
	int		prev_i;
	char	*res;

	i = 0;
	res = token;
	while (i < ft_strlen(res) && res[i])
	{
		prev_i = i;
		if (res[i] == '\"')
			res = double_quotes(res, &i, token);
		else if (res[i] == '\'')
			res = single_quotes(res, &i, token);
		if (i == prev_i)
			i++;
	}
	return (res);
}

int	quotes_or_not(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}
