/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:32:07 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/10 18:40:27 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	bash-3.2$ echo HELLO > > echo
	bash: syntax error near unexpected token `>'
	bash-3.2$ echo $?
	258
*/

void	redir_heredoc(char **argv, t_env *env)
{
	while (1)
	{
		readline("> ");
	}
}

void	redir_one_from(char **argv, t_env *env)
{
	int		tmp_fd;

	env->file_d = open(argv[1], O_RDONLY);
	if (env->file_d < 0)
	{
		return (1);
	} /* вывод ошибки */
	tmp_fd = dup(STDIN);
	dup2(env->fd.in, STDIN);
	close(tmp_fd);
	dup2(tmp_fd, STDIN);
	close(env->fd.in);
}

void	redir_one_to(char **argv, t_env *env)
{
	int		tmp_fd;

	env->file_d = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
	if (env->file_d < 0)
	{
		return (1); /* вывод ошибки */
	}
	tmp_fd = dup(STDOUT);
	dup2(env->fd.out, STDOUT);
	close(tmp_fd);
	dup2(tmp_fd, STDOUT);
	close(env->fd.out);
}

void	redir_doubble_to(char **argv, t_env *env)
{
	int		tmp_fd;

	env->file_d = open(argv[1], O_WRONLY | O_CREAT | O_APPEND);
	if (env->file_d < 0)
	{
		return (1); /* вывод ошибки */
	}
	tmp_fd = dup(STDOUT);
	dup2(env->fd.out, STDOUT);
	close(tmp_fd);
	dup2(tmp_fd, STDOUT);
	close(env->fd.out);
}

// void	my_redirect(char **redir, t_fd *fd)
// {}