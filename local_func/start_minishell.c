/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:06:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/16 14:37:26 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_patch(t_all *all)
{
	int		i;

	i = -1;
	while (all->path[++i])
	{
		all->path[i] = ft_strjoin(all->path[i], "/");
		if (!all->path[i])
			return (-1);
	}
	i = -1;
	while (all->path[++i])
	{
		all->path[i] = ft_strjoin(all->path[i], all->argv[0]);
		if (!all->path[i])
			return (-1);
		if (!(access(all->path[i], X_OK)))
		{
			all->argv[0] = ft_strdup(all->path[i]);
			return (0);
		}
	}
	return (1);
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
	if (!all->path)
		return (-1);
	if ((check_patch(all)))
		return (-1);
	return (0);
}

int	check_execve(t_all *all)
{
	pid_t		pid;
	int			fd[2];
	if ((create_path(all)))
		return (1);
	if ((pipe(fd)) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		close(fd[1]);
		execve(all->argv[0], all->argv, all->env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		close(fd[0]);
	}
	return (0);
}

int	is_bildins(t_all *all)
{
	if (!(ft_strncmp(all->argv[0], "echo", 5))
		|| !(ft_strncmp(all->argv[0], "Echo", 5)))
		my_echo(all->argv);
	if (!(ft_strncmp(all->argv[0], "cd", 3)))
		my_cd(all);
	if (!(ft_strncmp(all->argv[0], "exit", 5)))
		my_exit(all);
	if (!(ft_strncmp(all->argv[0], "env", 4)))
		my_env(all);
	if (!(ft_strncmp(all->argv[0], "export", 7)))
		my_export(all);
	if (!(ft_strncmp(all->argv[0], "pwd", 4)))
		my_pwd();
	if (!(ft_strncmp(all->argv[0], "unset", 6)))
		my_unset(all);
	else
		return (0);
	return (1);
}

void	start_minishell(t_all *all)
{
	while (all->next != NULL)
	{
		my_pipe(all);
		if (all->next != NULL)
			start_minishell(all->next);
		what_is_redir(all);
		if (!(is_bildins(all)) && (access(all->argv[0], X_OK)))
			if ((check_execve(all)))
				exit(127);
		all = all->next;
	}
}