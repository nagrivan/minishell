/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:15:24 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 14:44:38 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	it_is_num(char *argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '+' || argv[i] == '-' || (ft_isdigit(argv[i])))
			i++;
		else
			return (1);
	}
	return (0);
}

int	num_argv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	my_exit(t_all *all)
{
	ft_putendl_fd("exit", 1);
	if (num_argv(all->argv) == 1)
		exit(0);
	else
	{
		if (!(it_is_num(all->argv[1])))
		{
			if ((num_argv(all->argv)) > 2)
			{
				ft_putendl_fd("minishell: exit: too many arguments", 1);
				return (1);
			}
			if ((ft_atoi(all->argv[1])) < 0 && (ft_atoi(all->argv[1])) > 255)
				exit((unsigned int) ft_atoi(all->argv[1]) % 256);
			exit(ft_atoi(all->argv[1]));
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				all->argv[1]);
			exit(255);
		}
	}
	return (0);
}
