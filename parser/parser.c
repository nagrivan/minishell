/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:15:22 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/03 15:16:14 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokens_number(char	*str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]) && str[i] != '\0')
		{
			i = ft_strchr(str + i + 1, str[i]) + 1 - str;
			if (ft_strchr(" \t><|\0", str[i]))
				num++;
			continue ;
		}
		if (!ft_strchr(" \t><|\0", str[i]) && ft_strchr(" \t><|\0", str[i + 1]))
			num++;
		if (ft_strchr("<>|", str[i]) && str[i] != '\0')
			i += (num++ && str[i + 1] == str[i]);
		i += (str[i] != '\0');
	}
	return (num);
}

char	**fill_tokens(char **tokens, char *str, int *i, int *n)
{
	int	j;

	j = 0;
	if (!ft_strchr(" \t><|\0", str[*i]))
	{
		j = *i;
		while (!ft_strchr(" \t><|\0", str[*i]))
		{
			if (ft_strchr("\"\'", str[*i]))
				*i = ft_strchr(str + *i + 1, str[*i]) - str;
			(*i)++;
			if (ft_strchr(" \t><|\0", str[*i]))
				tokens[(*n)++] = new_token(str + j, str + *i);
		}
	}
	if (ft_strchr("<>|", str[*i]) && str[*i] != '\0')
	{
		j = *i;
		*i += 1 + (str[*i + 1] == str[*i]);
		tokens[(*n)++] = new_token(str + j, str + *i);
	}
	return (tokens);
}

char	**split_tokens(char *str, int num)
{
	char	**tokens;
	int		i;
	int		n;

	tokens = (char **)malloc(sizeof(char *) * (num + 1));
	if (!tokens)
		error_malloc();
	i = 0;
	while (i < num + 1)
		tokens[i++] = 0;
	n = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		while (str[i] && ft_strchr("\"\'", str[i]) && str[i] == str[i + 1]
			&& ft_strchr("\'\" \t><|\0", str[i + 2]))
			i += 2;
		tokens = fill_tokens(tokens, str, &i, &n);
	}
	return (tokens);
}

char	**clean_tokens(char **tokens, int num)
{
	int		i;
	char	**result;

	i = -1;
	result = malloc(sizeof(char *) * (num + 1));
	if (!result)
		error_malloc();
	while (++i < num + 1)
		result[i] = 0;
	i = 0;
	while (tokens[i])
	{
		if (quotes_or_not(tokens[i]))
			result[i] = clean_all_quotes(tokens[i]);
		else
			result[i] = ft_strdup(tokens[i]);
		i++;
	}
	free_split(tokens);
	return (result);
}

void	parser(char **str, char **env, t_all **all)
{
	int		i;
	int		num;
	char	**tokens;

	i = 0;
	*str = env_variables(*str, env);
	num = tokens_number(*str);
	tokens = split_tokens(*str, num);
	tokens = clean_tokens(tokens, num);
	while (find_pipe(tokens))
	{
		fill_new_node(tokens, all, env);
		tokens = trim_tokens(tokens);
	}
	fill_new_node(tokens, all, env);
	free_split(tokens);
}
