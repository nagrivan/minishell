/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:15:04 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/06 16:54:02 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Проверено Norminette
	check leaks
	+++
*/

int	my_env(char **argv, t_env *env)
{
	int		i;

	i = 0;
	if ((num_argv(argv)) != 1)
	{
		printf("env: %s: No such file or directory\n", argv[1]);
		return (127);
	}
	while (env->env[i])
	{
		if ((ft_strchr(env->env[i], '=')))
			ft_putendl_fd(env->env[i], 1);
		i++;
	}
	return (0);
}
