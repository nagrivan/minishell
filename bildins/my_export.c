/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:25 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/07 20:07:27 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Проверено Norminette
	Необходимо разбить функции на файлы
	check leaks
*/

int	my_export_argv(char *argv)
{
	int		i;

	i = 1;
	if ((ft_isalpha(argv[0]) == 0) && argv[0] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", argv);
		return (1);
	}
	while (argv[i] && argv[i] != '=')
	{
		if ((ft_isalnum(argv[i]) == 0) && argv[i] != '_' && argv[i] != '+')
		{
			printf("minishell: export: `%s': not a valid identifier\n", argv);
			return (1);
		}
		i++;
	}
	return (0);
}

int	print_exp(t_all *all)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = sort_all(all->env, num_argv(all->env));
	if (!tmp)
		return (1);
	while (tmp[i])
	{
		printf("declare -x %s\n", tmp[i]);
		i++;
	}
	ft_free(tmp);
	return (0);
}

int	write_argv_exp(char *argv, t_all *all)
{
	int		geolock;

	geolock = check_exp(argv, all->env, (check_equals(argv)));
	if (geolock == -1)
	{
		if ((write_env(argv, all)) != 0)
			return (1);
	}
	else
	{
		if (!(ft_strchr(argv, '=')))
			return (1);
		free(all->env[geolock]);
		all->env[geolock] = ft_strdup(argv);
		if (!all->env[geolock])
		{
			printf("minishell %s\n", strerror(errno));
			return (1);
		}
	}
	return (0);
}

int	my_export(t_all *all)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (num_argv(all->argv) == 1)
	{
		if ((print_exp(all)) != 0)
			return (1);
		return (0);
	}
	while (all->argv[++i])
	{
		if ((my_export_argv(all->argv[i])) == 1)
			status = 1;
		else
			if ((write_argv_exp(all->argv[i], all)) != 0)
				status = 1;
	}
	return (status);
}
