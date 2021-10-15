/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:06 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/15 16:50:42 by nagrivan         ###   ########.fr       */
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

int	write_env(char *result, t_all *all)
{
	int		i;
	char	**tmp;
	char	**free_env;

	free_env = all->env;
	i = num_argv(all->env);
	tmp = (char **)ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (all->env[i])
	{
		tmp[i] = ft_strdup(all->env[i]);
		i++;
	}
	tmp[i] = ft_strdup(result);
	tmp[++i] = NULL;
	all->env = tmp;
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

int	write_pwd(char *pwd, t_all *all)
{
	int		i;
	char	*result;

	i = check_env("PWD", all->env);
	result = ft_strjoin("PWD=", pwd);
	if (i != -1)
	{
		free(all->env[i]);
		all->env[i] = result;
	}
	else
	{
		if ((write_env(result, all)) != 0)
			return (1);
	}
	return (0);
}

int	write_old_pwd(char *old_pwd, t_all *all)
{
	int		i;
	char	*result;

	i = check_env("OLDPWD", all->env);
	result = ft_strjoin("OLDPWD=", old_pwd);
	if (i != -1)
	{
		free(all->env[i]);
		all->env[i] = result;
	}
	else
	{
		if ((write_env(result, all)) != 0)
			return (1);
	}
	return (0);
}

char	*check_where_cd(char *argv, t_all *all)
{
	char	*result;
	int		i;

	if (!argv)
	{
		i = check_env("HOME", all->env);
		result = ft_strtrim(all->env[i], "HOME=");
	}	
	else if (argv[0] == '-' && (ft_strlen(argv)) == 1)
	{
		i = check_env("OLDPWD", all->env);
		result = ft_strtrim(all->env[i], "OLDPWD=");
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

int	my_cd(t_all *all)
{
	char			*result;
	int				size;
	char			*old_pwd;
	char			*pwd;
	struct stat		stati;

	pwd = NULL;
	old_pwd = NULL;
	size = num_argv(all->argv);
	old_pwd = getcwd(old_pwd, 1024);
	result = check_where_cd(all->argv[1], all);
	if ((stat(result, &stati)) == -1)
	{
		cd_error(result, old_pwd);
		return (1);
	}
	chdir(result);
	pwd = getcwd(pwd, 1024);
	write_pwd(pwd, all);
	write_old_pwd(old_pwd, all);
	free(result);
	free(old_pwd);
	free(pwd);
	return (0);
}
