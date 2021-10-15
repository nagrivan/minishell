/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:06:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/15 13:50:06 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_patch(t_env *env)
{
	int		i;

	i = -1;
	while (env->path[++i])
	{
		env->path[i] = ft_strjoin(env->path[i], "/");
		if (!env->path[i])
			return (-1);
	}
	i = -1;
	while (env->path[++i])
	{
		env->path[i] = ft_strjoin(env->path[i], env->argv[0]);
		if (!env->path[i])
			return (-1);
		if (!(access(env->path[i], X_OK)))
		{
			env->argv[0] = ft_strdup(env->path[i]);
			return (0);
		}
	}
	return (1);
}

int	create_path(t_env *env)
{
	int			geolock;
	char		*paths;

	paths = NULL;
	geolock = check_env("PATH", env->env);
	if (geolock == -1)
	{
		printf("minishell: %s: No such file or directory\n", env->argv[0]);
		return (127);
	}
	paths = ft_strtrim(env->env[geolock], "PATH=");
	if (!paths)
	{
		printf("minishell: %s: No such file or directory\n", env->argv[0]);
		return (127);
	}
	env->path = ft_split(paths, ':');
	if (!env->path)
		return (-1);
	if ((check_patch(env)))
		return (-1);
	return (0);
}

int	check_execve(t_env *env)
{
	pid_t		pid;
	int			fd[2];
	if ((create_path(env)))
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
		execve(env->argv[0], env->argv, env->env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		close(fd[0]);
	}
	return (0);
}

int	is_bildins(t_env *env)
{
	if (!(ft_strncmp(env->argv[0], "echo", 5))
		|| !(ft_strncmp(env->argv[0], "Echo", 5)))
		my_echo(env->argv);
	if (!(ft_strncmp(env->argv[0], "cd", 3)))
		my_cd(env);
	if (!(ft_strncmp(env->argv[0], "exit", 5)))
		my_exit(env);
	if (!(ft_strncmp(env->argv[0], "env", 4)))
		my_env(env);
	if (!(ft_strncmp(env->argv[0], "export", 7)))
		my_export(env);
	if (!(ft_strncmp(env->argv[0], "pwd", 4)))
		my_pwd();
	if (!(ft_strncmp(env->argv[0], "unset", 6)))
		my_unset(env);
	else
		return (0);
	return (1);
}

void	start_minishell(t_env *env)
{
	while (env->next != NULL)
	{
		my_pipe(env);
		if (env->next != NULL)
			start_minishell(env->next);
		what_is_redir(env);
		if (!(is_bildins(env)) && (access(env->argv[0], X_OK)))
			if ((check_execve(env)))
				exit(127);
		env = env->next;
	}
}