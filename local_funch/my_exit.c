/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:15:24 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/08 20:40:07 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		it_is_num(char *argv)
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

int		num_argv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int		my_exit(char **argv)
{
	ft_putendl_fd("Exit", 1);
	if (num_argv(argv) == 0)
		exit(0);
	else
	{
		if (!(it_is_num(argv[0])))
		{
			if ((num_argv(argv)) > 1)
			{
				ft_putendl_fd("minishell: exit: too many arguments", 1);
				return (1);
			}
			exit(ft_atoi(argv[0]));
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", argv[0]);
			exit(255);
		}
	}
	return (0);
}