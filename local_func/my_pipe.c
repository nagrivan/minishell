/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:22:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/29 17:35:32 by nagrivan         ###   ########.fr       */
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

void	shaman_fd(t_all *all, int count_pipe, int *tmp_fd)
{
	if (all->pipe != count_pipe)
	{
		if ((dup2(all->fd[1], STDOUT_FILENO)) == -1)
		{
			printf("minishell %s\n", strerror(errno));
			exit_status = errno;
			return ;
		}
		if ((close(all->fd[1])) == -1)
		{
			printf("minishell: Invalid close\n");
			exit_status = errno;
			return ;
		}
		if ((close(all->fd[0])) == -1)
		{
			printf("minishell: Invalid close\n");
			exit_status = errno;
			return ;
		}
	}
	if (all->pipe == count_pipe)
	{
		if ((dup2(tmp_fd[1], STDOUT_FILENO)) == -1)
		{
			printf("minishell %s\n", strerror(errno));
			exit_status = errno;
			return ;
		}
		if ((close(tmp_fd[1])) == -1)
		{
			printf("minishell: Invalid close\n");
			exit_status = errno;
			return ;
		}
	}
	if (all->num_redir)
		what_is_redir(all);
	if (is_bildins(all))
		exit(0);
	else
	{
		if ((access(all->argv[0], X_OK)) != 0)
			create_path(all);
		if ((execve(all->argv[0], all->argv, all->env)) == -1)
		{
			exit_status = errno;
			exit(errno);
		}
	}
}

void	my_pipe(t_all *all, int count_pipe, int *tmp_fd)
{
	if ((pipe(all->fd)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return ;
	}
	all->dother = fork();
	if (all->dother == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return ;
	}
	if (all->dother == 0)
		shaman_fd(all, count_pipe, tmp_fd);
	else
	{
		// signal_off();
		// waitpid(all->dother, &all->status, WUNTRACED); //отловить в какой момент это необходимо
		// if (WIFSIGNALED(all->status))
		// 	signal_dother(all->status);
		signal_on();
		if ((close(all->fd[1])) == -1)
		{
			printf("minishell: Invalid close\n");
			return ;
		}
		if ((dup2(all->fd[0], STDIN_FILENO)) == -1)
		{
			printf("minishell %s\n", strerror(errno));
			exit_status = errno;
			return ;
		}
		if ((close(all->fd[0])) == -1)
		{
			printf("minishell: Invalid close\n");
			return ;
		}
	}
}
