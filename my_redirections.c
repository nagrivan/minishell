/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:32:07 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/17 16:05:04 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	redir_heredoc(t_env *env, int i)
{
	char	*str;
	int		fd[2];

	str = NULL;
	if ((pipe(fd)) == -1)
		return ;
	env->dother = fork();
	if (env->dother == -1)
		return ;
	if (env->dother == 0)
	{
		while (1)
		{
			str = readline("> ");
			if (str && (!(ft_strncmp(str, env->redir[i].filename, ft_strlen(str)))))
				exit(0);
			ft_putendl_fd(str, fd[1]);
			free(str);
		}
	}
	else
	{
		wait(NULL);
		if (env->argv[0])
		{			
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
	}
}

int	replace_fd(t_env *env, int num, int fd)
{
	int		tmp_fd;

	tmp_fd = 0;
	tmp_fd = dup(fd);
	if ((close(fd)) == -1)
		return (1);
	if ((dup2(env->redir[num].file_d, fd)) == -1)
		return (1);
	if ((close(env->redir[num].file_d)) == -1)
		return (1);
	return (0);


		// if ((dup2(tmp_fd, fd)) == -1)
		// 	return (1);	
}

void	what_is_redir(t_env *env)
{
	int		i;
	
	i = -1;
	while (++i < env->num_redir)
	{
		if 	(env->redir[i].type_redir == HEREDOC && env->redir[i].filename)
			redir_heredoc(env, i);
		if (env->redir[i].type_redir == ONE_FROM && env->redir[i].filename)
		{
			env->redir[i].file_d = open(env->redir[i].filename, O_RDONLY);
			if (env->redir[i].file_d == -1)
				printf("minishell: %s: No such file or directory\n", env->redir[i].filename);
			replace_fd(env, i, STDIN);
		}
		if (env->redir[i].type_redir == ONE_TO && env->redir[i].filename)
		{
			env->redir[i].file_d = open(env->redir[i].filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (env->redir[i].file_d == -1)
				printf("minishell: %s: No such file or directory\n", env->redir[i].filename);
			replace_fd(env, i, STDOUT);
		}
		if (env->redir[i].type_redir == DOB_TO && env->redir[i].filename)
		{
			env->redir[i].file_d = open(env->redir[i].filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (env->redir[i].file_d == -1)
				printf("minishell: %s: No such file or directory\n", env->redir[i].filename);
			replace_fd(env, i, STDOUT);
		}
	}
}
