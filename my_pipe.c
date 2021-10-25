/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:22:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/25 17:30:11 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_pipe(t_env *env)
{
	int		result = 0;
	
	while(env != NULL)
	{
		result++;
		env = env->next;
	}
	return (result);
}

void	shaman_fd(t_env *env, int count_pipe, int *tmp_fd)
{
	// if (env->num_redir)
	// 	what_is_redir(env);
	// else
	// {
		if (env->pipe != count_pipe)// не последний
		{
			// printf("oops..\n\n");
			// if ((close(STDOUT)) == -1)
			// 	return ;
			if ((dup2(env->fd[1], STDOUT_FILENO)) == -1)
				return ;
			if ((close(env->fd[1])) == -1)
				return ;
			if ((close(env->fd[0])) == -1)
				return ;

			//
			// ft_putstr_fd(env->argv[0], 2);
			// ft_putstr_fd("       ", 2);
			// ft_putnbr_fd(STDOUT_FILENO, 2);
			// ft_putchar_fd('\n', 2);
			//
		}
		if (env->pipe == count_pipe)
		{
			dup2(tmp_fd[1], STDOUT_FILENO);
			close(tmp_fd[1]);
			
			//
			// ft_putstr_fd(env->argv[0], 2);
			// ft_putstr_fd("       ", 2);
			// ft_putnbr_fd(STDOUT_FILENO, 2);
			// ft_putchar_fd('\n', 2);
			//
			// printf("stdin = %d\n", STDIN_FILENO);
		}
		if (env->num_redir)
			what_is_redir(env);
	// }
	if (is_bildins(env))
		exit(0);
	else
	{
		if ((access(env->argv[0], X_OK)) != 0)
			create_path(env);
		// ft_putendl_fd("before execve", 2);
		execve(env->argv[0], env->argv, env->env);
	}
	
}

void	my_pipe(t_env *env, int count_pipe, int *tmp_fd)
{
	if ((pipe(env->fd)) == -1)
		return ;
	// ft_putstr_fd("2.0", 2);
	// ft_putendl_fd(env->argv[0], 2);
	env->dother = fork(); //начинается задвоение в редиректах, какого??
	if (env->dother == -1)
		return ;
	if (env->dother == 0)
		shaman_fd(env, count_pipe, tmp_fd);
	else
	{
		waitpid(env->dother, &env->status, WUNTRACED);
		// ft_putstr_fd("2.1", 2);
		// ft_putendl_fd(env->argv[0], 2);
		// if (env->pipe != 0) //не первый //fix
		// {
			// printf("env->pipe=%d\n", env->pipe);
			// printf("OOPS..\n\n");
			// if ((close(STDIN)) == -1)
			// 	return ;
			if ((dup2(env->fd[0], STDIN_FILENO)) == -1)
				return ;
			if ((close(env->fd[0])) == -1)
				return ;
			if ((close(env->fd[1])) == -1)
				return ;
		// }
		
		// if (env->fd[0] != STDIN_FILENO)
		// {
		// 	dup2(env->fd[0], STDIN_FILENO);
		// 	close(env->fd[0]);
		// }
		// if (env->fd[0] != STDOUT_FILENO)
		// {
		// 	dup2(env->fd[1], STDOUT_FILENO);
		// 	close(env->fd[1]);
		// }
	}
}
