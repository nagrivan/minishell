/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:14:06 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/03 16:14:09 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_struct_sanya(char **env, t_all **tmp)
{
	*tmp = (t_all *)malloc(sizeof(t_all));
	(*tmp)->env = init_env(env);
	(*tmp)->argv = NULL;
	(*tmp)->dother = 0;
	(*tmp)->fd[0] = dup(STDIN_FILENO);
	if ((*tmp)->fd[0] == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return ;
	}
	(*tmp)->fd[1] = dup(STDOUT_FILENO);
	if ((*tmp)->fd[1] == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return ;
	}
	(*tmp)->next = NULL;
	(*tmp)->num_redir = 0;
	(*tmp)->num_argv = 0;
	(*tmp)->path = NULL;
	(*tmp)->pipe = 0;
	(*tmp)->redir = NULL;
	(*tmp)->status = 0;
}

static void	init_node(t_all **node, char **tokens, char **env)
{
	init_struct_sanya(env, node);
	num_of_redir(tokens, *node);
	num_of_argv(tokens, *node);
	fill_argv(tokens, *node);
	if ((*node)->num_redir != 0)
		fill_redir(tokens, *node);
}

void	fill_new_node(char **tokens, t_all **all, char **env)
{
	int		pipe_n;
	t_all	*tmp;
	t_all	*node;

	init_node(&node, tokens, env);
	if (*all == 0)
	{
		*all = node;
		(*all)->pipe = 1;
		(*all)->next = NULL;
	}
	else
	{
		tmp = *all;
		pipe_n = 2;
		while (tmp->next)
		{
			tmp = tmp->next;
			pipe_n++;
		}
		tmp->next = node;
		tmp = tmp->next;
		tmp->pipe = pipe_n;
		tmp->next = NULL;
	}
}

char	**trim_tokens(char **str)
{
	char	**tmp_jopa;
	char	**new_str;
	int		i;
	int		old_i;
	int		new_tokens_num;

	new_str = NULL;
	tmp_jopa = str;
	i = 0;
	while (tmp_jopa[i] && tmp_jopa[i][0] != '|')
		i++;
	if (tmp_jopa[i])
	{
		new_tokens_num = 0;
		old_i = i + 1;
		while (tmp_jopa[++i])
			new_tokens_num++;
		new_str = malloc(sizeof(char *) * (new_tokens_num + 1));
		new_str[new_tokens_num] = 0;
		i = 0;
		while (tmp_jopa[old_i])
			new_str[i++] = ft_strdup(tmp_jopa[old_i++]);
		free_split(str);
	}
	return (new_str);
}
