/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:15:04 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/15 16:49:42 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Проверено Norminette
	check leaks
	+++
*/

int	my_env(t_all *all)
{
	int		i;

	i = 0;
	if ((num_argv(all->argv)) != 1)
	{
		printf("env: %s: No such file or directory\n", all->argv[1]);
		return (127);
	}
	while (all->env[i])
	{
		if ((ft_strchr(all->env[i], '=')))
			ft_putendl_fd(all->env[i], 1);
		i++;
	}
	return (0);
}
