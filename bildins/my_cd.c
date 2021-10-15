/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:06 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/15 13:39:53 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	При подаче нескольких аргументов - работает только с первым
	Разбить функции на несколько файлов
	Соответствует Norminette
	check leaks
	++++
*/

int	write_env(char *result, t_env *env)
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

int	check_env(char *argv, char **env)
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
	}
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

char	*check_where_cd(char *argv, t_env *env)
{
	char	*result;
	int		i;

	if (!argv)
	{
		i = check_env("HOME", env->env);
		result = ft_strtrim(env->env[i], "HOME=");
	}	
	else if (argv[0] == '-' && (ft_strlen(argv)) == 1)
	{
		i = check_env("OLDPWD", env->env);
		result = ft_strtrim(env->env[i], "OLDPWD=");
	}
	else
		result = ft_strdup(argv);
	return (result);
}

void	cd_error(char *result, char *old_pwd)
{
	printf("minishell: cd: %s: No such file or directory\n", result);
	free(result);
	free(old_pwd);
}

int	my_cd(t_env *env)
{
	char			*result;
	int				size;
	char			*old_pwd;
	char			*pwd;
	struct stat		stati;

	pwd = NULL;
	old_pwd = NULL;
	size = num_argv(env->argv);
	old_pwd = getcwd(old_pwd, 1024);
	result = check_where_cd(env->argv[1], env);
	if ((stat(result, &stati)) == -1)
	{
		cd_error(result, old_pwd);
		return (1);
	}
	chdir(result);
	pwd = getcwd(pwd, 1024);
	write_pwd(pwd, env);
	write_old_pwd(old_pwd, env);
	free(result);
	free(old_pwd);
	free(pwd);
	return (0);
}
