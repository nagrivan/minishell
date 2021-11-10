/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:25 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/10 18:09:22 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Проверено Norminette
	Необходимо разбить функции на файлы
	check leaks
*/

char	**sort_all(char **env, int len)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;

	new = (char **)ft_calloc(sizeof(char *), (len + 1));
	if (!new)
	{
		printf("minishell %s\n", strerror(errno));
		exit_status = errno;
		return (NULL);
	}
	new[len] = NULL;
	i = -1;
	while (env[++i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
		{
			printf("minishell %s\n", strerror(errno));
			exit_status = errno;
			return (NULL);
		}
	}
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len - 1)
		{
			if (ft_strncmp(new[j], new[j + 1], ft_strlen(new[j]) + 1) > 0)
			{
				tmp = new[j + 1];
				new[j + 1] = new[j];
				new[j] = tmp;
			}
		}
	}
	return (new);
}

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
		printf("%d declare -x %s\n", i, tmp[i]);
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
		if ((write_env(argv, all)) != 0)
			return (1);
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
