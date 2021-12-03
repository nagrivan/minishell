/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:22:22 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/03 19:22:24 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	num_of_redir(char **str, t_all *tmp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], ">")
			|| !ft_strcmp(str[i], "<")
			|| !ft_strcmp(str[i], ">>")
			|| !ft_strcmp(str[i], "<<"))
			tmp->num_redir++;
		if (ft_strcmp(str[i], "|") == 0)
			break ;
		i++;
	}
}

void	num_of_argv(char **str, t_all *tmp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") == 0)
			break ;
		if (!ft_strcmp(str[i], ">")
			|| !ft_strcmp(str[i], "<")
			|| !ft_strcmp(str[i], ">>")
			|| !ft_strcmp(str[i], "<<"))
		{
			i += 2;
			continue ;
		}
		if (tmp)
			tmp->num_argv++;
		i++;
	}
}

void	fill_argv(char **tokens, t_all *node)
{
	int	i;
	int	j;

	node->argv = malloc(sizeof(char *) * (node->num_argv + 1));
	node->argv[node->num_argv] = 0;
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			break ;
		if (!ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], "<")
			|| !ft_strcmp(tokens[i], ">>")
			|| !ft_strcmp(tokens[i], "<<"))
		{
			i += 2;
			continue ;
		}
		node->argv[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
}

static int	defined_redir(t_all *node, int key, int *j, char *token)
{
	if (key == 1)
		node->redir[*j].type_redir = ONE_TO;
	else if (key == 2)
		node->redir[*j].type_redir = DOB_TO;
	else if (key == 3)
		node->redir[*j].type_redir = ONE_FROM;
	else
		node->redir[*j].type_redir = HEREDOC;
	node->redir[*j].filename = ft_strdup(token);
	*j += 1;
	return (2);
}

void	fill_redir(char **tokens, t_all *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	node->redir = ft_calloc(sizeof(t_redirect), node->num_redir + 1);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			break ;
		if (!ft_strcmp(tokens[i], ">"))
			i += defined_redir(node, 1, &j, tokens[i + 1]);
		else if (!ft_strcmp(tokens[i], ">>"))
			i += defined_redir(node, 2, &j, tokens[i + 1]);
		else if (!ft_strcmp(tokens[i], "<"))
			i += defined_redir(node, 3, &j, tokens[i + 1]);
		else if (!ft_strcmp(tokens[i], "<<"))
			i += defined_redir(node, 4, &j, tokens[i + 1]);
		else
			i++;
	}
}
