/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:32:07 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/29 19:44:27 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	bash-3.2$ echo HELLO > > echo
	bash: syntax error near unexpected token `>'
	bash-3.2$ echo $?
	258
	bash-3.2$ <<
	bash: syntax error near unexpected token `<'
	bash-3.2$ < <<
	bash: syntax error near unexpected token `<<'
	bash-3.2$ <
	bash: syntax error near unexpected token `newline'
	bash-3.2$
*/

void	redir_heredoc(t_all *all, int i)
{
	char	*str;
	int		fd[2];

	str = NULL;
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
	if (all->dother == 0) // вынести в отдельную функцию
	{
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
	else
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
}

int	replace_fd(t_all *all, int num, int fd)
{
	// printf("1.3\n");
	all->redir[num].tmp_fd = 0;
	all->redir[num].tmp_fd = dup(fd);
	if (all->redir[num].tmp_fd == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return (1);
	}
	if ((close(fd)) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
	if ((dup2(all->redir[num].file_d, fd)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return (1);
	}
	if ((close(all->redir[num].file_d)) == -1)
	{
		printf("minishell: Invalid close\n");
		return (1);
	}
	all->redir[num].fd = fd;
	// printf("end 1.3\n");
	return (0);
}

void	open_file(t_all *all, int i)
{
	// printf("1.2\n");
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
	// printf("end 1.2\n");
}

void	what_is_redir(t_all *all)
{
	int		i;

	i = -1;
	while (++i < all->num_redir)
	{
		// printf("1.1\n");
		if (all->redir[i].type_redir == HEREDOC && all->redir[i].filename)
			redir_heredoc(all, i);
		else
		{
			open_file(all, i);
			if (all->redir[i].type_redir == ONE_FROM)
				replace_fd(all, i, STDIN_FILENO);
			else
				replace_fd(all, i, STDOUT_FILENO);
		}
		// printf("end 1.1\n");
	}
}
