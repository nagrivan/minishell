/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:06 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/05 18:29:32 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	При подаче нескольких аргументов - работает только с первым
	OLD_PWD изменить;
	PWD ;
	Проверить, есть ли такая директория;
	cd -;
	chdir, stat, lstat, fstat
*/

int		write_env(char *result, t_env *env)
{
	int		i;
	char	**tmp;
	char	**free_env;

	free_env = env->env;
	i = num_argv(env->env);
	tmp = (char **)ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (env->env[i])
	{
		tmp[i] = ft_strdup(env->env[i]);
		i++;
	}
	tmp[i] = ft_strdup(result);
	tmp[++i] = NULL;
	env->env = tmp;
	ft_free(free_env);
	return (0);
}

int		check_env(char *argv, char **env)
{
	char	*patch;
	int		i;
	
	i = 0;
	while (env[i])
	{
		patch = ft_strnstr(env[i], argv, ft_strlen(argv));
		if (patch)
			break ;
		i++;
	};
	if (!patch)
		return (-1);
	return (i);
}

int	write_pwd(char *pwd, t_env *env)
{
	int		i;
	char	*result;

	i = check_env("PWD", env->env);
	result = ft_strjoin("PWD=", pwd);
	if (i != -1)
	{
		free(env->env[i]);
		env->env[i] = result;
	}
	else
	{
		if ((write_env(result, env)) != 0)
			return (1);
	}
	return (0);
}

int	write_old_pwd(char *old_pwd, t_env *env)
{
	int		i;
	char	*result;

	i = check_env("OLDPWD", env->env);
	result = ft_strjoin("OLDPWD=", old_pwd);
	if (i != -1)
	{
		free(env->env[i]);
		env->env[i] = result;
	}
	else
	{
		if ((write_env(result, env)) != 0)
			return (1);
	}
	return (0);
}

int		my_cd(char **argv, t_env *env) /*Попробовать так*/
{
	int		i;
	char	*result = NULL;
	int		size;
	char	*old_pwd = NULL;
	char	*pwd = NULL;
	struct stat	stati;

	size = num_argv(argv);
	old_pwd = getcwd(old_pwd, 1024);
	if (size == 1) /*возврат на HOME*/
	{
		i = check_env("HOME", env->env);
		result = ft_strtrim(env->env[i], "HOME=");
		if ((stat(result, &stati)) == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n", result);
			return (1);
		}
		chdir(result);
	}
	else
	{
		if (argv[1][0] == '-' && (ft_strlen(argv[1])) == 1) /* Возвращает на OLDPWD*/
		{
			i = check_env("OLDPWD", env->env);
			result = ft_strtrim(env->env[i], "OLDPWD=");
			if ((stat(result, &stati)) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n", result);
				return (1);
			}
			chdir(result);
		}
		else
		{
			if ((stat(argv[1], &stati)) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n", argv[1]);
				return (1);
			}
			chdir(argv[1]);
		}
	}
	pwd = getcwd(pwd, 1024);
	write_pwd(pwd, env);
	write_old_pwd(old_pwd, env);
	free(result);
	return (0);
}