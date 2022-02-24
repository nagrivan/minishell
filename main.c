/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:51:10 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/01 19:29:09 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **my_text)
{
	int		i;

	i = 0;
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

char	*get_readline(char *str)
{
	str = readline("minishell$ ");
	if (str)
	{
		if (str && *str)
			add_history(str);
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "\033[Aexit\n", 9);
		exit(0);
	}
	return (str);
}

int	poihali(char **str, char ***tmp_env, t_all **all)
{
	if (mini_preparser(*str))
	{
		free(*str);
		return (1);
	}
	parser(str, *tmp_env, all);
	start_minishell(*all);
	if (*tmp_env)
		free_split(*tmp_env);
	*tmp_env = ((*all)->env);
	if (!*tmp_env)
		printf("minishell %s\n", strerror(errno));
	if (*str)
		free(*str);
	free_struct(all);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char		*str;
	char		**tmp_env;
	t_all		*all;

	(void)argc;
	(void)argv;
	str = NULL;
	all = 0;
	tmp_env = init_env(env);
	if (!tmp_env)
	{
		printf("minishell %s\n", strerror(errno));
		return (errno);
	}
	init_shlvl(&tmp_env);
	signal_on();
	while (1)
	{
		str = get_readline(str);
		if (poihali(&str, &tmp_env, &all) == 1)
			continue ;
	}
	clear_history();
	return (0);
}
