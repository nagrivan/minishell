/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:53:21 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 14:54:30 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	write_pwd(char *pwd, t_all *all)
{
	int		i;
	char	*result;

	i = check_env("PWD", all->env);
	result = ft_strjoin("PWD=", pwd);
	if (!result)
	{
		printf("minishell %s\n", strerror(errno));
		return (1);
	}
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
	if (!result)
	{
		printf("minishell %s\n", strerror(errno));
		return (1);
	}
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

int	write_pwd_oldpwd(t_all *all, char *old_pwd, char *pwd)
{
	if (!pwd)
	{
		printf("minishell %s\n", strerror(errno));
		return (1);
	}
	write_pwd(pwd, all);
	if (old_pwd)
		write_old_pwd(old_pwd, all);
	return (0);
}
