/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:51:10 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/15 13:53:04 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free(char **my_text)
{
	int	i = 0;

	if (my_text)
	{
		while (my_text[i])
		{
			free(my_text[i]);
			i++;
		}
	}
	if (my_text)
		free(my_text);
}

int main(int argc, char **argv, char **env)
{
	char *str;
	char **my_text;
	t_env tmp;

	(void)argc;
	(void)argv;
	if ((init_struct(&tmp, env)) != 0)
		return (1);
	int g = 0;
	while (g < 10)
	{
		str = readline("mini_test$ ");
		if (!(my_text = ft_split(str, ' ')))
		{
			free(str);
			return (1);
		}
		check_redir(my_text, &env);
		if ((check_argv(my_text, &tmp)) != 0)
		{
			free(str);
			ft_free(my_text);
			return (1);
		}
		ft_free(my_text);
		free(str);
		g++;
		system("leaks minitest");
	}
	return (0);
}