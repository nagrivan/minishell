/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:06:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/27 19:43:55 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_patch(t_all *all)
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
			return (-1);
	}
	i = -1;
	while (all->path[++i])
	{
		free_str = all->path[i];
		all->path[i] = ft_strjoin(all->path[i], all->argv[0]);
		free(free_str);
		if (!all->path[i])
			return (-1);
		if (!(access(all->path[i], X_OK)))
		{
			free_str = all->argv[0];
			all->argv[0] = ft_strdup(all->path[i]);
			free(free_str);
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
	ft_free(all->path);
	free(paths);
	return (0);
}

int	check_execve(t_all *all)
{
	pid_t		pid;
	int			fd[2];

	if ((access(all->argv[0], X_OK)) != 0)
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
		// dup2(fd[1], STDOUT_FILENO);
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
	if (!(ft_strncmp(all->argv[0], "echo", 5)))
		my_echo(all->argv);
	else if (!(ft_strncmp(all->argv[0], "cd", 3)))
		my_cd(all);
	else if (!(ft_strncmp(all->argv[0], "exit", 5)))
		my_exit(all);
	else if (!(ft_strncmp(all->argv[0], "env", 4)))
		my_env(all);
	else if (!(ft_strncmp(all->argv[0], "export", 7)))
		my_export(all);
	else if (!(ft_strncmp(all->argv[0], "pwd", 4)))
		my_pwd();
	else if (!(ft_strncmp(all->argv[0], "unset", 6)))
		my_unset(all);
	else
		return (0);
	return (1);
}

int	what_bild(t_all *all)
{
	if (!(ft_strncmp(all->argv[0], "echo", 5))
		|| !(ft_strncmp(all->argv[0], "cd", 3))
		|| !(ft_strncmp(all->argv[0], "exit", 5))
		|| !(ft_strncmp(all->argv[0], "env", 4))
		|| !(ft_strncmp(all->argv[0], "export", 7))
		|| !(ft_strncmp(all->argv[0], "pwd", 4))
		|| !(ft_strncmp(all->argv[0], "unset", 6)))
		return (1);
	return (0);
}

void	bildin_exec(t_all *all)
{
	if (all->next)
	{
		if ((pipe(all->fd)) == -1)
			return ;
		if ((dup2(all->fd[1], STDOUT_FILENO)) == -1)
			return ;
		if ((close(all->fd[1])) == -1)
			return ;
		is_bildins(all);
		if ((dup2(all->fd[0], STDIN_FILENO)) == -1)
			return ;
		if ((close(all->fd[0])) == -1)
			return ;
	}
	else
		is_bildins(all);
}

void	start_minishell(t_all *all)
{
	int		i;
	int		count_pipe;
	int		tmp_fd[2];
	int		status;

	i = -1;
	count_pipe = num_pipe(all);
	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	while (all != NULL)
	{
		if (count_pipe > 1)
			my_pipe(all, count_pipe, tmp_fd);
		else // вынести в отдельную функцию
		{
			if (all->redir)
				what_is_redir(all);
			if (all->argv[0] && !(is_bildins(all)))
				if (!all->redir || all->redir[all->num_redir - 1].file_d != -1)
					check_execve(all);
			while (++i < all->num_redir)
			{
				if ((close(all->redir[i].fd)) == -1)
					return ;
				if ((dup2(all->redir[i].tmp_fd, all->redir[i].fd)) == -1)
					return ;
			}
		}
		all = all->next;
	}
	i = -1;
	while (++i <= count_pipe)
	{
		signal_off();
		waitpid(0, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			signal_dother(status);
		signal_on();
	}
	dup2(tmp_fd[0], STDIN_FILENO);
}
