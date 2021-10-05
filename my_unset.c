/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:50 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/05 17:07:05 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
	bash-3.2$ unset ""
	bash: unset: `': not a valid identifier
	Если переменной нет - ничего не удалять
	Удаляет сразу несколько переменных, при встрече с невалидным ведет себя 
	как export
	bash: unset: `1235': not a valid identifier
	bash-3.2$ echo $?
	1
*/

int		delete_env(t_env *env, int geolock)
{
	int		i;
	int		j;
	char	**tmp;
	char	**free_env;

	free_env = env->env;
	i = num_argv(env->env);
	tmp = (char **)ft_calloc(sizeof(char *), i);
	i = 0;
	j = 0;
	while (env->env[i])
	{
		if (i != geolock)
		{
			tmp[j] = ft_strdup(env->env[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	env->env = tmp;
	ft_free(free_env);
	return (0);
}

int		my_unset(char **argv, t_env *env)
{
	int		i;
	int		geolock;
	int		status; //должна быть общая переменная для хранения возвращаемых значений функциями

	i = 0;
	status = 0;
	if ((num_argv(argv)) == 1)
		return (0);
	while (argv[++i])
	{
		if ((my_export_argv(argv[i])) == 1)
			status = 1;
		else
		{
			geolock = check_exp(argv[i], env->env, (check_equals(argv[i])));
			if (geolock != -1)
				delete_env(env, geolock);
		}
	}
	return (status);
}