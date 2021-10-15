/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:22:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/15 16:49:42 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	num_pipe(t_all *all)
{
	int		result;
	
	while(all->next != NULL)
	{
		result++;
		all = all->next;
	}
	return (result);
}

void	shaman_fd(t_all *all)
{
	int		count_pipe;
	int		tmp_fd[2];

	count_pipe = num_pipe(all);
	if (all->pipe != 0)
	{
		tmp_fd[0] = dup(STDIN);
		if ((close(STDIN)) == -1)
			return ;
		if ((dup2(all->fd[0], STDIN)) == -1)
			return ;
		if ((close(all->fd[0])) == -1)
			return ;
		if ((close(all->fd[1])) == -1)
			return ;
	}
	if (all->pipe != count_pipe)
	{
		tmp_fd[0] = dup(STDOUT);
		if ((close(STDOUT)) == -1)
			return ;
		if ((dup2(all->fd[1], STDOUT)) == -1)
			return ;
		if ((close(all->fd[1])) == -1)
			return ;
		if ((close(all->fd[0])) == -1)
			return ;
	}
}

void	my_pipe(t_all *all)
{
	if ((pipe(all->fd)) == -1)
		return ;
	all->dother = fork();
	if (all->dother == -1)
		return ;
	if (all->dother == 0)
		shaman_fd(all);
	else
	{
		waitpid(all->dother, &all->status, WUNTRACED);
		if (all->fd[0] != STDIN)
		{
			dup2(all->fd[0], STDIN);
			close(all->fd[0]);
		}
		if (all->fd[0] != STDOUT)
		{
			dup2(all->fd[1], STDOUT);
			close(all->fd[1]);
		}
	}
}
