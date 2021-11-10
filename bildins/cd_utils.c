/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:10:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/10 17:51:42 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	write_env(char *result, t_all *all)
{
	int		i;
	char	**tmp;
	char	**free_env;

	free_env = all->env;
	i = num_argv(all->env);
	tmp = (char **)ft_calloc(sizeof(char *), i + 2);
	if (!tmp)
	{
		printf("minishell %s\n", strerror(errno));
		exit_status = errno;
		return (1);
	}
	i = 0;
	while (all->env[i])
	{
		tmp[i] = ft_strdup(all->env[i]);
		if (!tmp[i])
		{
			printf("minishell %s\n", strerror(errno));
			exit_status = errno;
			return (1);
		}
		i++;
	}
	tmp[i] = ft_strdup(result);
	if (!tmp[i])
	{
		printf("minishell %s\n", strerror(errno));
		exit_status = errno;
		return (1);
	}
	tmp[++i] = NULL;
	all->env = tmp;
	ft_free(free_env);
	return (0);
}

int	check_env(char *argv, char **env)
{
	char	*patch;
	int		i;

	i = 0;
	while (env[i])
	{
		patch = ft_strnstr(env[i], argv, ft_strlen(argv));
		if (patch)
			break ;
		i++;
	}
	if (!patch)
		return (-1);
	return (i);
}
