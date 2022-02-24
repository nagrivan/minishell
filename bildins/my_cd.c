/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:06 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 14:54:26 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!result)
	{
		printf("minishell %s\n", strerror(errno));
		return (NULL);
	}
	return (result);
}

void	cd_error_free(int error, char *result, char *old_pwd, char *pwd)
{
	if (error == 1)
		printf("minishell: cd: %s: No such file or directory\n", result);
	if (result)
		free(result);
	if (old_pwd)
		free(old_pwd);
	if (pwd)
		free(pwd);
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
	if (!result)
		return (1);
	if ((stat(result, &stati)) == -1)
	{
		cd_error_free(1, result, old_pwd, NULL);
		return (1);
	}
	chdir(result);
	pwd = getcwd(pwd, 1024);
	if ((write_pwd_oldpwd(all, old_pwd, pwd)) != 0)
		return (1);
	cd_error_free(0, result, old_pwd, pwd);
	return (0);
}
