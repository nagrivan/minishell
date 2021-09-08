/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:15:04 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/08 23:30:48 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*Необходимо подумать и обсудить, в каком виде будут подаваться 
	переменные окружения в функцию*/

int		my_env(char *argv, char **env)
{
	int		i;

	i = 0;
	if (argv != NULL)
	{
		printf("env: %s: No such file or directory\n", argv);
		return (127);
	}
	while (env[i])
	{
		if ((ft_strchr(env[i], '=')))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}