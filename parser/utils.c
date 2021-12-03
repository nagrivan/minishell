/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:48:17 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/03 15:48:21 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_token(char *start, char *end)
{
	char	*tmp;
	char	*token;

	token = malloc(sizeof(char) * (end - start) + 1);
	tmp = start;
	while (tmp != end)
	{
		token[tmp - start] = *tmp;
		++tmp;
	}
	token[tmp - start] = '\0';
	return (token);
}

int	find_pipe(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_struct(t_all **all)
{
	int	i;

	if ((*all)->next)
		free_struct(&(*all)->next);
	if ((*all)->num_redir != 0)
	{
		i = 0;
		while (i < (*all)->num_redir)
			free((*all)->redir[i++].filename);
		free((*all)->redir);
	}
	free(*all);
	*all = NULL;
}

void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
