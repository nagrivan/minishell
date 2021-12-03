/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:45:42 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 19:13:46 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_heredoc(t_all *all, int *fd)
{
	signal_off();
	wait(NULL);
	signal_on();
	if (all->argv[0])
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	dother_heredoc(t_all *all, int *fd, int i)
{
	char	*str;

	str = NULL;
	signal_off();
	signal_on_her();
	while (1)
	{
		str = readline("> ");
		if (str && (!(ft_strncmp(str, all->redir[i].filename,
						ft_strlen(str)))))
			exit(0);
		ft_putendl_fd(str, fd[1]);
		free(str);
	}
}

void	redir_heredoc(t_all *all, int i)
{
	int		fd[2];

	pipe(fd);
	all->dother = fork();
	if (all->dother == 0)
		dother_heredoc(all, fd, i);
	else
		parent_heredoc(all, fd);
}
