/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:32:07 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/11 14:10:05 by nagrivan         ###   ########.fr       */
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
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if ()
			return ;
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
	close(STDIN);
	dup2(env->file_d, STDIN);
	close(env->file_d);
	while () // пока строчки в файле для прочтения не закончатся
	{
		read(env->file_d, argv[1], 1000);
	}
	dup2(tmp_fd, STDIN);
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
	close(STDOUT);
	dup2(env->file_d, STDOUT);
	close(env->file_d);
	while () // пока все строчки длля внесения в файл не закончатся
	{
		write(env->file_d, "", ft_strlen(""));
	}
	dup2(tmp_fd, STDOUT);
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
	close(STDOUT);
	dup2(env->file_d, STDOUT); //
	close(env->file_d);
	while () // пока все строчки длля внесения в файл не закончатся
	{
		write(env->file_d, "", ft_strlen(""));
	}
	dup2(tmp_fd, STDOUT);
}

// void	my_redirect(char **redir, t_fd *fd)
// {
// 	if (redir[0][0] == '>')
// 	{
// 	}
// 	if (redir[0][0] == '<')
// 	{
// 		if (redir[0][1] == )
// 	}
// }