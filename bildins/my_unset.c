/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:50 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/15 13:47:51 by nagrivan         ###   ########.fr       */
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

int	delete_env(t_env *env, int geolock)
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

int	my_unset(t_env *env)
{
	int		i;
	int		geolock;
	int		status;

	i = 0;
	status = 0;
	if ((num_argv(env->argv)) == 1)
		return (0);
	while (env->argv[++i])
	{
		if ((my_export_argv(env->argv[i])) == 1)
			status = 1;
		else
		{
			geolock = check_exp(env->argv[i], env->env,
					(check_equals(env->argv[i])));
			if (geolock != -1)
				delete_env(env, geolock);
		}
	}
	return (status);
}
