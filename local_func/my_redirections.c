/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:32:07 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 19:10:28 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_fd(t_all *all, int num, int fd)
{
	all->redir[num].tmp_fd = 0;
	all->redir[num].tmp_fd = dup(fd);
	close(fd);
	dup2(all->redir[num].file_d, fd);
	close(all->redir[num].file_d);
	all->redir[num].fd = fd;
	return (0);
}

void	open_file(t_all *all, int i)
{
	if (all->redir[i].type_redir == ONE_FROM && all->redir[i].filename)
		all->redir[i].file_d = open(all->redir[i].filename, O_RDONLY);
	if (all->redir[i].type_redir == ONE_TO && all->redir[i].filename)
		all->redir[i].file_d = open(all->redir[i].filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (all->redir[i].type_redir == DOB_TO && all->redir[i].filename)
		all->redir[i].file_d = open(all->redir[i].filename,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (all->redir[i].file_d == -1)
		printf("minishell: %s: No such file or directory\n",
			all->redir[i].filename);
}

void	what_is_redir(t_all *all)
{
	int		i;

	i = -1;
	while (++i < all->num_redir)
	{
		all->redir[i].tmp_fd = -1;
		all->redir[i].fd = -1;
		if (all->redir[i].type_redir == HEREDOC && all->redir[i].filename)
			redir_heredoc(all, i);
		else
		{
			open_file(all, i);
			if (all->redir[i].file_d == -1)
				continue ;
			if (all->redir[i].type_redir == ONE_FROM)
				replace_fd(all, i, STDIN_FILENO);
			else
				replace_fd(all, i, STDOUT_FILENO);
		}
	}
}
