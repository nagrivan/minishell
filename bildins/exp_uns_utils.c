/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_uns_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:14:17 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/27 14:15:07 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	check_equals(char *argv)
{
	size_t		i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	return (i);
}

int	check_exp(char *argv, char **env, size_t size)
{
	int		res;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!(ft_strchr(env[i], '=')))
			size = ft_strlen(env[i]);
		res = ft_strncmp(env[i], argv, size);
		if (res == 0)
			break ;
		i++;
	}
	if (res != 0)
		return (-1);
	return (i);
}
