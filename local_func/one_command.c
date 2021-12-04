/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 06:18:02 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/04 06:18:05 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	daughter(t_all *all, int *fd)
{
	if ((close(fd[0])) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
	if ((close(fd[1])) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
	execve(all->argv[0], all->argv, all->env);
	return (0);
}

static int	parent(int *fd)
{
	if ((close(fd[1])) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
	if ((dup2(fd[0], STDIN)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
		return (1);
	}
	if ((close(fd[0])) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
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
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
		return (1);
	}
	if (pid == 0)
		return (daughter(all, fd));
	else
		return (parent(fd));
}

int	is_bildins(t_all *all)
{
	if (!(ft_strncmp(all->argv[0], "echo", 5)))
		g_exit_status = my_echo(all->argv);
	else if (!(ft_strncmp(all->argv[0], "cd", 3)))
		g_exit_status = my_cd(all);
	else if (!(ft_strncmp(all->argv[0], "exit", 5)))
		g_exit_status = my_exit(all);
	else if (!(ft_strncmp(all->argv[0], "env", 4)))
		g_exit_status = my_env(all);
	else if (!(ft_strncmp(all->argv[0], "export", 7)))
		g_exit_status = my_export(all);
	else if (!(ft_strncmp(all->argv[0], "pwd", 4)))
		g_exit_status = my_pwd();
	else if (!(ft_strncmp(all->argv[0], "unset", 6)))
		g_exit_status = my_unset(all);
	else
		return (0);
	return (1);
}

int	one_command(t_all *all)
{
	int	i;

	i = all->num_redir;
	if (all->redir)
		what_is_redir(all);
	if (all->argv && all->argv[0] && !(is_bildins(all)))
		if (!all->redir || all->redir[all->num_redir - 1].file_d != -1)
			check_execve(all);
	while (--i >= 0)
	{
		if (all->redir[i].tmp_fd != -1 && all->redir[i].fd != -1)
		{
			close(all->redir[i].fd);
			if ((dup2(all->redir[i].tmp_fd, all->redir[i].fd)) == -1)
			{
				printf("minishell %s\n", strerror(errno));
				return (1);
			}
			close(all->redir[i].tmp_fd);
		}
	}
	close(all->fd[0]);
	close(all->fd[1]);
	return (0);
}
