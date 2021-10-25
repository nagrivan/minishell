/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:06:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/25 12:36:36 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_patch(t_env *env)
{
	int		i;
	char	*free_str;

	i = -1;
	while (env->path[++i])
	{
		free_str = env->path[i];
		env->path[i] = ft_strjoin(env->path[i], "/");
		free(free_str);
		if (!env->path[i])
			return (-1);
	}
	i = -1;
	while (env->path[++i])
	{
		free_str = env->path[i];
		env->path[i] = ft_strjoin(env->path[i], env->argv[0]);
		free(free_str);
		if (!env->path[i])
			return (-1);
		if (!(access(env->path[i], X_OK)))
		{
			free_str = env->argv[0];
			env->argv[0] = ft_strdup(env->path[i]);
			free(free_str);
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
	ft_free(env->path);
	free(paths);
	return (0);
}

int	check_execve(t_env *env)
{
	pid_t		pid;
	int			fd[2];
	
	if ((access(env->argv[0], X_OK)) != 0)
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
		// dup2(fd[1], STDOUT_FILENO);
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
	if (!(ft_strncmp(env->argv[0], "echo", 5)))
		my_echo(env->argv);
	else if (!(ft_strncmp(env->argv[0], "cd", 3)))
		my_cd(env->argv, env);
	else if (!(ft_strncmp(env->argv[0], "exit", 5)))
		my_exit(env->argv);
	else if (!(ft_strncmp(env->argv[0], "env", 4)))
		my_env(env->argv, env);
	else if (!(ft_strncmp(env->argv[0], "export", 7)))
		my_export(env->argv, env);
	else if (!(ft_strncmp(env->argv[0], "pwd", 4)))
		my_pwd();
	else if (!(ft_strncmp(env->argv[0], "unset", 6)))
		my_unset(env->argv, env);
	else
		return (0);
	return (1);
}

void	start_minishell(t_env *env)
{
	int		i;
	int		count_pipe;
	int		tmp_fd[2];
	int		status;

	i = -1;
	count_pipe = num_pipe(env);
	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	while (env != NULL)
	{
		if (env->pipe <= count_pipe && env->pipe)
			my_pipe(env, count_pipe, tmp_fd);
		// if (env->next != NULL)
		// 	my_pipe(env->next, count_pipe);
		if (env->redir)
			what_is_redir(env);
		// if (!(is_bildins(env)))
		// 	if (!env->redir || env->redir[env->num_redir - 1].file_d != -1)
		// 		check_execve(env);
		while (++i < env->num_redir)
		{
			if ((close(env->redir[i].fd)) == -1)
				return ;
			if ((dup2(env->redir[i].tmp_fd, env->redir[i].fd)) == -1)
				return ;
		}
		env = env->next;
	}
	for (int k = 0; k <= count_pipe; k++)
		waitpid(0, &status, WUNTRACED);
	dup2(tmp_fd[0], STDIN_FILENO);
}