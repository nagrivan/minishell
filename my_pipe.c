/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:22:15 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/19 18:58:56 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_pipe(t_env *env)
{
	int		result = 0;
	
	while(env->next != NULL)
	{
		result++;
		env = env->next;
	}
	return (result);
}

void	shaman_fd(t_env *env)
{
	int		count_pipe;
	int		tmp_fd[2];

	count_pipe = num_pipe(env);
	if (env->pipe != 0)
	{
		tmp_fd[0] = dup(STDIN);
		if ((close(STDIN)) == -1)
			return ;
		if ((dup2(env->fd[0], STDIN)) == -1)
			return ;
		if ((close(env->fd[0])) == -1)
			return ;
		if ((close(env->fd[1])) == -1)
			return ;
	}
	if (env->pipe != count_pipe)
	{
		tmp_fd[0] = dup(STDOUT);
		if ((close(STDOUT)) == -1)
			return ;
		if ((dup2(env->fd[1], STDOUT)) == -1)
			return ;
		if ((close(env->fd[1])) == -1)
			return ;
		if ((close(env->fd[0])) == -1)
			return ;
	}
}

void	my_pipe(t_env *env)
{
	if ((pipe(env->fd)) == -1)
		return ;
	// env->dother = fork();
	if (env->dother == -1)
		return ;
	if (env->dother == 0)
		shaman_fd(env);
	else
	{
		waitpid(env->dother, &env->status, WUNTRACED);
		if (env->fd[0] != STDIN)
		{
			dup2(env->fd[0], STDIN);
			close(env->fd[0]);
		}
		if (env->fd[0] != STDOUT)
		{
			dup2(env->fd[1], STDOUT);
			close(env->fd[1]);
		}
	}
}
