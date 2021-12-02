/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_adds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:54:43 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/02 12:54:46 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*swap(char **str, char *val, int *i, int j)
{
	char	*dst;
	char	*dst2;
	char	*tmp;

	dst = ft_substr(*str, 0, j);
	dst2 = ft_strdup(*str + *i);
	tmp = dst;
	dst = ft_strjoin(dst, val);
	free(tmp);
	tmp = dst;
	dst = ft_strjoin(dst, dst2);
	free(tmp);
	free(dst2);
	return (dst);
}

int	valid_sym(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

static int	find_arg(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '=' && s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

static int	find_name(char **env, char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (find_arg(env[i], arg))
			return (i + 1);
		i++;
	}
	return (0);
}

char	*get_env(char **env, char *arg)
{
	int		index;
	int		i;
	char	*ret;

	i = -1;
	index = find_name(env, arg) - 1;
	if (index != -1)
	{
		ret = env[index];
		while (env[index] && env[index][++i] != '=')
			ret++;
		return (++ret);
	}
	return (0);
}
