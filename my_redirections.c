/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:32:07 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/11 18:38:22 by nagrivan         ###   ########.fr       */
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
		if (!str && !(ft_strncmp(str, argv[1], ft_strlen(str))))
			return ;
	}
}

void	redir_one_from(char **argv, t_env *env)
{
	int		tmp_fd;
	char	*buff;
	size_t	res_read;

	res_read = 0;
	env->file_d = open(argv[1], O_RDONLY);
	if (env->file_d < 0)
	{
		/* вывод ошибки */
		return (1);
	}
	tmp_fd = dup(STDIN);
	if (tmp_fd == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((close(STDIN)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((dup2(env->file_d, STDIN)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((close(env->file_d)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	dup2(tmp_fd, STDIN);
	{
		/* вывод ошибки */
		return (1);
	}
}

void	redir_one_to(char **argv, t_env *env)
{
	int		tmp_fd;

	env->file_d = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
	if (env->file_d < 0)
	{
		/* вывод ошибки */
		return (1);
	}
	tmp_fd = dup(STDOUT);
	if (tmp_fd == -1)
	{
		/* вывод ошибки */
		return (1);
	}	
	if ((close(STDOUT)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((dup2(env->file_d, STDOUT)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((close(env->file_d)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((dup2(tmp_fd, STDOUT)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
}

void	redir_doubble_to(char **argv, t_env *env)
{
	int		tmp_fd;

	env->file_d = open(argv[1], O_WRONLY | O_CREAT | O_APPEND);
	if (env->file_d < 0)
	{
		/* вывод ошибки */
		return (1);
	}
	tmp_fd = dup(STDOUT);
	if ((close(STDOUT)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((dup2(env->file_d, STDOUT)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((close(env->file_d)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
	if ((dup2(tmp_fd, STDOUT)) == -1)
	{
		/* вывод ошибки */
		return (1);
	}
}

void	my_redirect(char **redir, t_env *env)
{
	if (redir[0][0] == '>')
	{
		if (redir[0][1] == '>')
			redir_doubble_to(redir, env);
		else
			redir_one_to(redir, env);
	}
	if (redir[0][0] == '<')
	{
		if (redir[0][1] == '<')
			redir_heredoc(redir, env);
		else
			redir_one_from(redir, env);
	}
}