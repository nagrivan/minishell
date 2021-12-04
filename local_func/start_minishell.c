/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:06:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/01 19:06:22 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_operations(int count_pipe)
{
	int	i;
	int	status;

	i = -1;
	while (++i <= count_pipe)
	{
		signal_off();
		if (WIFSIGNALED(status))
			signal_dother(status);
		else
			if (count_pipe || WEXITSTATUS(status))
				g_exit_status = WEXITSTATUS(status);
		waitpid(0, &status, WUNTRACED);
		signal_on();
	}
}

int	dup_fd_check(int *fd0, int *fd1, int *count_pipe, t_all *all)
{
	*count_pipe = num_pipe(all);
	*fd0 = dup(STDIN_FILENO);
	if (*fd0 == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
		return (1);
	}
	*fd1 = dup(STDOUT_FILENO);
	if (*fd1 == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
		return (1);
	}
	return (0);
}

void	start_minishell(t_all *all)
{
	int		count_pipe;
	int		tmp_fd[2];

	if (dup_fd_check(&tmp_fd[0], &tmp_fd[1], &count_pipe, all) == 1)
		return ;
	while (all != NULL)
	{
		if (count_pipe > 1)
		{
			my_pipe(all, count_pipe, tmp_fd);
			close(all->fd[0]);
			close(all->fd[1]);
		}
		else if (one_command(all) == 1)
			return ;
		all = all->next;
	}
	signal_operations(count_pipe);
	if ((dup2(tmp_fd[0], STDIN_FILENO)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
	}
	close(tmp_fd[0]);
	close(tmp_fd[1]);
}
