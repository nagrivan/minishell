/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:25 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/05 17:55:40 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	**sort_env(char **env, int len)
{
    int     i;
    int     j;
    char    **new;
    char    *tmp;

	new = (char **)ft_calloc(sizeof(char *), (len + 1));
    new[len] = NULL;
    i = -1;
    while (env[++i])
	{
        new[i] = ft_strdup(env[i]);	
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

size_t		check_equals(char *argv)
{
	size_t 	i;

	i = 0;
	while(argv[i] && argv[i] != '=')
		i++;
	i += 1;
	return (i);
}

int		check_exp(char *argv, char **env, size_t size)
{
	int		res;
	int		i;
	
	i = 0;
	while (env[i])
	{
		res = ft_strncmp(env[i], argv, size);
		if (res == 0)
			break ;
		i++;
	};
	if (res != 0)
		return (-1);
	return (i);
}

int		my_export_argv(char *argv)
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

int		my_export(char **argv, t_env *env)
{
	int		i;
	char	**tmp;
	int		geolock;
	int		status; //должна быть общая переменная для возвращения кода ошибки

	i = 0;
	status = 0;
	if (num_argv(argv) == 1)
	{
		tmp = sort_env(env->env, num_argv(env->env));
		while (tmp[i])
		{
			printf("%d declare -x %s\n", i, tmp[i]);
			i++;
		}
		ft_free(tmp);
		return (0);
	}
	while (argv[++i])
	{
		if ((my_export_argv(argv[i])) == 1)
			status = 1;
		else
		{
			geolock = check_exp(argv[i], env->env, (check_equals(argv[i])));
			if (geolock == -1)
				write_env(argv[i], env);
			else
			{
				free(env->env[geolock]);
				env->env[geolock] = ft_strdup(argv[i]);
			}			
		}
	}
	return (status);
}