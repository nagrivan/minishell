/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:22:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 19:40:15 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	num_pipe(t_all *all)
{
	int		result;

	result = 0;
	while (all != NULL)
	{
		result++;
		all = all->next;
	}
	return (result);
}

void	start_command(t_all *all, int *tmp_fd)
{
	if (all->num_redir)
		what_is_redir(all);
	if (is_bildins(all))
		exit(0);
	else
	{
		close(all->fd[1]);
		close(all->fd[0]);
		close(tmp_fd[0]);
		close(tmp_fd[1]);
		if ((access(all->argv[0], X_OK)) != 0)
			create_path(all);
		if ((execve(all->argv[0], all->argv, all->env)) == -1)
		{
			g_exit_status = errno;
			exit(errno);
		}
	}
}

void	shaman_fd(t_all *all, int count_pipe, int *tmp_fd)
{
	if (all->pipe != count_pipe)
	{
		dup2(all->fd[1], STDOUT_FILENO);
		close(all->fd[1]);
		close(all->fd[0]);
	}
	if (all->pipe == count_pipe)
	{
		dup2(tmp_fd[1], STDOUT_FILENO);
		close(all->fd[1]);
		close(all->fd[0]);
		close(tmp_fd[1]);
	}
	start_command(all, tmp_fd);
}

void	my_pipe(t_all *all, int count_pipe, int *tmp_fd)
{
	close(all->fd[0]);
	close(all->fd[1]);
	pipe(all->fd);
	all->dother = fork();
	if (all->dother == 0)
	{
		shaman_fd(all, count_pipe, tmp_fd);
		close(all->fd[0]);
		close(all->fd[1]);
	}
	else
	{
		signal_on();
		close(all->fd[1]);
		dup2(all->fd[0], STDIN_FILENO);
		close(all->fd[0]);
		close(all->fd[0]);
		close(all->fd[1]);
	}
}
