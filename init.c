/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:37:56 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/07 19:15:57 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_malloc(void)
{
	printf("minishell %s\n", strerror(errno));
	exit(errno);
}

char	**init_env(char **env)
{
	int		i;
	int		size;
	char	**result;
	char	*free_tmp;

	i = -1;
	size = num_argv(env);
	result = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!result)
		return (NULL);
	while (env[++i])
	{
		free_tmp = result[i];
		result[i] = ft_strdup(env[i]);
		free(free_tmp);
		if (!result[i])
		{
			printf("minishell %s\n", strerror(errno));
			free_split(result);
			return (NULL);
		}
	}
	result[i] = NULL;
	return (result);
}

char	*get_value(char *str, int *index)
{
	int	i;

	i = 0;
	while (str && str[i] != '=')
		i++;
	*index = ++i;
	return (str + i);
}

void	init_shlvl(char ***env)
{
	int		i;
	int		numb;
	int		len;
	char	*str;
	char	*number;

	i = check_exp("SHLVL=", *(env), 6);
	if (i != -1)
	{
		numb = ft_atoi(get_value((*env)[i], &len));
		str = ft_substr((*env)[i], 0, len);
		if (!str)
			error_malloc();
		number = ft_itoa(++numb);
		if (!number)
			error_malloc();
		free((*env)[i]);
		(*env)[i] = ft_strjoin(str, number);
		if (!(*env)[i])
			error_malloc();
		free(str);
		free(number);
	}
}

t_all	*init_struct(char **env)
{
	t_all	*tmp;

	tmp = (t_all *)malloc(sizeof(t_all));
	if (!tmp)
	{
		printf("minishell %s\n", strerror(errno));
		exit(errno);
	}
	tmp->env = init_env(env);
	tmp->argv = NULL;
	tmp->dother = 0;
	tmp->fd[0] = dup(STDIN_FILENO);
	tmp->fd[1] = dup(STDOUT_FILENO);
	if (tmp->fd[0] == -1 || tmp->fd[1] == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return (NULL);
	}
	tmp->next = NULL;
	tmp->num_redir = 0;
	tmp->path = NULL;
	tmp->pipe = 0;
	tmp->redir = NULL;
	tmp->status = 0;
	return (tmp);
}
