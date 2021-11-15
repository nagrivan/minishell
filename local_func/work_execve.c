/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:47:07 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/15 15:47:44 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dother_execve(t_all *all, int fd[2])
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

int	parent_execve(t_all *all, int fd[2])
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
		dother_execve(all, fd[2]);
	else
		parent_execve(all, fd[2]);
	return (0);
}
