/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:06 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/09 01:47:00 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*Подумать над тем, какие еще случаи нужно обработать и как*/

int		check_env(char *argv, char **env)
{
	char	*patch;
	int		i;
	
	i = 0;
	while (env[i])
	{
		patch = strnstr(env[i], argv, ft_strlen(argv));
		if (patch)
			break ;
		i++;
	}
	if (!patch && (chdir(patch)) == -1)
		return (1);
	return (0);
}

int		my_cd(char *argv, char **env)
{
	if (!argv)
		if ((check_env("HOME=", env)) != 0)
			return (1);
	else
		if ((check_env(argv, env)) != 0)
			return (1);
	return (0);
}