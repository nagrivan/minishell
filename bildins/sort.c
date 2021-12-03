/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:58:42 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/14 15:59:25 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**create_new(char **env, int len)
{
	int		i;
	char	**new;

	new = (char **)ft_calloc(sizeof(char *), (len + 1));
	if (!new)
	{
		printf("minishell %s\n", strerror(errno));
		return (NULL);
	}
	new[len] = NULL;
	i = -1;
	while (env[++i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
		{
			printf("minishell %s\n", strerror(errno));
			return (NULL);
		}
	}
	return (new);
}

char	**sort_all(char **env, int len)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;

	new = create_new(env, len);
	if (!new)
		return (NULL);
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
