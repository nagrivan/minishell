/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:14:50 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/10 17:29:07 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		my_unset(char *argv, char **env)
{
	int		i;

	i = 0;
	if (!argv)
		return (0);
	while (env[i])
	{
		if (strnstr(env[i], argv, ft_strlen(argv)))
		{
			/*Подумать и реализовать принцип удаления переменной окружения*/
			free(env[i]);
			return (0);
		}
		i++;
	}
	return (1);
}