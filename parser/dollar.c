/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:54:17 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/02 19:51:22 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_not_exist(char **str, int *i, int j)
{
	char	*dst;
	char	*dst2;
	char	*res;

	dst = ft_substr(*str, 0, j);
	dst2 = ft_strdup(*str + *i);
	res = ft_strjoin(dst, dst2);
	free(dst);
	free(dst2);
	*i -= *i - j;
	free(*str);
	return (res);
}

static char	*dollar_question(char **str, int *i, int j)
{
	char	*arg;
	char	*number;

	(*i) += 2;
	number = ft_itoa(g_exit_status);
	arg = swap(str, number, i, j);
	free(number);
	(*i)--;
	free(*str);
	return (arg);
}

char	*dollar(char **str, int *i, char **env)
{
	int		j;
	char	*val;
	char	*arg;

	(void)env;
	j = *i;
	if ((*str)[*i + 1] == '?')
		return (dollar_question(str, i, j));
	while ((*str)[++(*i)])
		if (!valid_sym((*str)[*i]))
			break ;
	if (*i == j + 1)
		return (*str);
	arg = ft_substr(*str, j + 1, *i - j - 1);
	val = get_env(env, arg);
	free(arg);
	if (!val)
		return (env_not_exist(str, i, j));
	arg = swap(str, val, i, j);
	free(*str);
	if ((*i - j) > ft_strlen(val))
		*i -= *i - j - ft_strlen(val);
	else
		*i += ft_strlen(val) - (*i - j);
	return (arg);
}

static char	*double_quotes(char **str, char **env, int *i)
{
	(*i)++;
	while ((*str)[*i] != '\"' && (*str)[*i] != '\0')
	{
		if ((*str)[*i] == '$')
			*str = dollar(str, i, env);
		if ((*str)[*i] == '\"')
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	return (*str);
}

char	*env_variables(char *str, char **env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			str = double_quotes(&str, env, &i);
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '$')
			str = dollar(&str, &i, env);
		else
			i++;
	}
	return (str);
}
