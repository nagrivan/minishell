/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:45:42 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/14 16:51:56 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_heredoc(t_all *all, int fd[2])
{
	signal_off();
	wait(NULL);
	signal_on();
	if (all->argv[0])
	{
		if ((close(fd[1])) == -1)
		{
			printf("minishell: Invalid close\n");
			return ;
		}
		if ((dup2(fd[0], STDIN_FILENO)) == -1)
		{
			printf("minishell %s\n", strerror(errno));
			return ;
		}
		if ((close(fd[0])) == -1)
		{
			printf("minishell: Invalid close\n");
			return ;
		}
	}
}

void	dother_heredoc(t_all *all, int fd[2], int i)
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

	if ((pipe(fd)) == -1)
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
		dother_heredoc(all, fd[2], i);
	else
		parent_heredoc(all, fd);
}
