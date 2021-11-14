/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:50 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/14 16:16:09 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	bash-3.2$ unset ""
	bash: unset: `': not a valid identifier
	Если переменной нет - ничего не удалять
	Удаляет сразу несколько переменных, при встрече с невалидным ведет себя 
	как export
	bash: unset: `1235': not a valid identifier
	bash-3.2$ echo $?
	1
	Проверено Norminette
*/

char	**write_tmp(t_all *all, int i, int geolock)
{
	int		j;
	char	**tmp;

	tmp = (char **)ft_calloc(sizeof(char *), i);
	if (!tmp)
	{
		printf("minishell %s\n", strerror(errno));
		return (NULL);
	}
	i = -1;
	j = -1;
	while (all->env[++i])
	{
		if (i != geolock)
		{
			tmp[++j] = ft_strdup(all->env[i]);
			if (!tmp[j])
			{
				printf("minishell %s\n", strerror(errno));
				return (NULL);
			}
		}
	}
	tmp[j] = NULL;
	return (tmp);
}

int	delete_env(t_all *all, int geolock)
{
	int		i;
	char	**tmp;
	char	**free_env;

	free_env = all->env;
	i = num_argv(all->env);
	tmp = write_tmp(all, i, geolock);
	if (!tmp)
		return (1);
	all->env = tmp;
	ft_free(free_env);
	return (0);
}

int	my_unset(t_all *all)
{
	int		i;
	int		geolock;
	int		status;

	i = 0;
	status = 0;
	if ((num_argv(all->argv)) == 1)
		return (0);
	while (all->argv[++i])
	{
		if ((my_export_argv(all->argv[i])) == 1)
			status = 1;
		else
		{
			geolock = check_exp(all->argv[i], all->env,
					(check_equals(all->argv[i])));
			if (geolock != -1)
				if ((delete_env(all, geolock)) != 0)
					status = 1;
		}
	}
	return (status);
}
