/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaman_fd_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:07:58 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/15 16:08:31 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_last_pipe(t_all *all)
{
	if ((dup2(all->fd[1], STDOUT_FILENO)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
		return (1);
	}
	if ((close(all->fd[1])) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
	if ((close(all->fd[0])) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
	return (0);
}

int	last_pipe(t_all *all, int *tmp_fd)
{
	if ((dup2(tmp_fd[1], STDOUT_FILENO)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
		return (1);
	}
	if ((close(tmp_fd[1])) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
	return (0);
}

void	shaman_stdout_fd(t_all *all, int count_pipe, int *tmp_fd)
{
	if (all->pipe != count_pipe)
		if ((not_last_pipe(all)) != 0)
			return ;
	if (all->pipe == count_pipe)
		if ((last_pipe(all, tmp_fd)) != 0)
			return ;
	if (all->num_redir)
		what_is_redir(all);
	if (is_bildins(all))
		exit(0);
	else
	{
		if ((access(all->argv[0], X_OK)) != 0)
			create_path(all);
		execve(all->argv[0], all->argv, all->env);
	}
}

void	shaman_stdin_fd(t_all *all)
{
	signal_on();
	if ((close(all->fd[1])) == -1)
	{
		printf("minishell: Invalid close\n");
		return ;
	}
	if ((dup2(all->fd[0], STDIN_FILENO)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
		return ;
	}
	if ((close(all->fd[0])) == -1)
	{
		printf("minishell: Invalid close\n");
		return ;
	}	
}
