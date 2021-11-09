/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:22:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/26 19:39:46 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return ;
		if ((close(all->fd[1])) == -1)
			return ;
		if ((close(all->fd[0])) == -1)
			return ;
	}
	if (all->pipe == count_pipe)
	{
		if ((dup2(tmp_fd[1], STDOUT_FILENO)) == -1)
			return ;
		if ((close(tmp_fd[1])) == -1)
			return ;
	}
	if (all->num_redir) // вынести в отдельную функцию
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

void	my_pipe(t_all *all, int count_pipe, int *tmp_fd)
{
	if ((pipe(all->fd)) == -1)
		return ;
	all->dother = fork();
	if (all->dother == -1)
		return ;
	if (all->dother == 0)
		shaman_fd(all, count_pipe, tmp_fd);
	else
	{
		signal_off();
		waitpid(all->dother, &all->status, WUNTRACED);
		if (WIFSIGNALED(env->status))
			signal_dother(env->status);
		signal_on();
		if ((dup2(all->fd[0], STDIN_FILENO)) == -1)
			return ;
		if ((close(all->fd[0])) == -1)
			return ;
		if ((close(all->fd[1])) == -1)
			return ;
	}
}
