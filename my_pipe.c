/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:22:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/25 12:38:15 by nagrivan         ###   ########.fr       */
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
	}
	if (env->pipe == count_pipe)
	{
		dup2(tmp_fd[1], STDOUT_FILENO);
		close(tmp_fd[1]);
	}
	if (!is_bildins(env))
	{
		if ((access(env->argv[0], X_OK)) != 0)
			create_path(env);
		execve(env->argv[0], env->argv, env->env);
	}
	
}

void	my_pipe(t_env *env, int count_pipe, int *tmp_fd)
{
	
	if ((pipe(env->fd)) == -1)
		return ;
	env->dother = fork(); //начинается задвоение в редиректах, какого??
	if (env->dother == -1)
		return ;
	if (env->dother == 0)
		shaman_fd(env, count_pipe, tmp_fd);
	else
	{
		waitpid(env->dother, &env->status, WUNTRACED);
		if (env->pipe != 0) //не первый
		{
			// printf("OOPS..\n\n");
			// if ((close(STDIN)) == -1)
			// 	return ;
			if ((dup2(env->fd[0], STDIN_FILENO)) == -1)
				return ;
			if ((close(env->fd[0])) == -1)
				return ;
			if ((close(env->fd[1])) == -1)
				return ;
		}
		
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
