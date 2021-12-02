/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:51:10 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 19:42:48 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline_str(void)
{
	char		*str;

	str = NULL;
	str = readline("minishell ");
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

char	**preparation(int argc, char **argv, char **env)
{
	char		**tmp_env;

	(void)argc;
	(void)argv;
	tmp_env = init_env(env);
	if (!tmp_env)
	{
		printf("minishell %s\n", strerror(errno));
		exit(errno);
	}
	init_shlvl(&tmp_env);
	signal_on();
	return (tmp_env);
}

void	start(t_all *all, char *str, char **tmp_env)
{
	parser(&str, tmp_env, &all);
	start_minishell(all);
}

void	free_main(t_all *all, char *str)
{
	t_all		*alll;

	if (str)
		free(str);
	alll = all;
	while (alll)
	{
		ft_free(alll->argv);
		alll = alll->next;
	}
	free_struct(&all);
}

int	main(int argc, char **argv, char **env)
{
	char		*str;
	char		**tmp_env;
	t_all		*all;

	str = NULL;
	all = 0;
	tmp_env = preparation(argc, argv, env);
	while (1)
	{
		str = readline_str();
		if (mini_preparser(str))
		{
			free(str);
			continue ;
		}
		start(all, str, tmp_env);
		if (tmp_env)
			free_split(tmp_env);
		tmp_env = (all->env);
		if (!tmp_env)
			printf("minishell %s\n", strerror(errno));
		free_main(all, str);
	}
	clear_history();
	return (0);
}
