/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:44:56 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/30 13:33:43 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_patch(t_all *all, int i)
{
	char	*free_str;

	if (!(access(all->path[i], X_OK)))
	{
		free_str = all->argv[0];
		all->argv[0] = ft_strdup(all->path[i]);
		free(free_str);
		if (!all->argv[0])
		{
			printf("minishell %s\n", strerror(errno));
			return (-1);
		}
		return (0);
	}
	return (1);
}

int	write_patch(t_all *all)
{
	int		i;
	char	*free_str;

	i = -1;
	while (all->path[++i])
	{
		free_str = all->path[i];
		all->path[i] = ft_strjoin(all->path[i], "/");
		free(free_str);
		if (!all->path[i])
		{
			printf("minishell %s\n", strerror(errno));
			return (-1);
		}
	}
	return (0);
}

int	check_patch(t_all *all)
{
	int		i;
	char	*free_str;

	if ((write_patch(all)) != 0)
		return (-1);
	i = -1;
	while (all->path[++i])
	{
		free_str = all->path[i];
		all->path[i] = ft_strjoin(all->path[i], all->argv[0]);
		free(free_str);
		if (!all->path[i])
		{
			printf("minishell %s\n", strerror(errno));
			return (-1);
		}
		if (!(search_patch(all, i)))
			return (0);
	}
	return (1);
}

void	error_path(t_all *all)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(all->argv[0], 2);
	ft_putendl_fd(": command not found", 2);
	g_exit_status = 127;
}

int	create_path(t_all *all)
{
	int			geolock;
	char		*paths;

	paths = NULL;
	geolock = check_env("PATH", all->env);
	if (geolock == -1)
	{
		printf("minishell: %s: No such file or directory\n", all->argv[0]);
		return (127);
	}
	paths = ft_strtrim(all->env[geolock], "PATH=");
	if (!paths)
	{
		printf("minishell: %s: No such file or directory\n", all->argv[0]);
		return (127);
	}
	all->path = ft_split(paths, ':');
	if (!all->path || (check_patch(all)))
	{
		error_path(all);
		return (-1);
	}
	ft_free(all->path);
	free(paths);
	return (0);
}
