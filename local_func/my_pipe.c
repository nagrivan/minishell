/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:22:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/15 16:08:36 by nagrivan         ###   ########.fr       */
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
		shaman_stdout_fd(all, count_pipe, tmp_fd);
	else
		shaman_stdin_fd(all);
}
