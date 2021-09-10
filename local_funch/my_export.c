/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:25 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/10 17:29:22 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		my_export_argv(char *argv, char **env)
{
	int		i;

	i = 0;
	if (!(ft_isalpha(argv[i])) || argv[i] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", argv[i]);
		return (1);
	}
	while (argv[++i])
	{
		if (!(ft_isalnum(argv[i])) || argv[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", argv[i]);
			return (1);
		}
		i++;
	}
	/*необходимо написать функцию добавления аргументов в общий список*/
	return (0);
}

int		my_export(char *argv, char **env)
{
	int		i;

	i = 0;
	if (!argv)
	{
		while (env[i])
		{
			printf("declare -x %s\n", env[i]);
			i++;
		}
	}
	if ((my_export_argv(argv, env)) != 0)
		return (1);
	return (0);
}