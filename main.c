/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:51:10 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/03 21:58:49 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
void ft_print(char **my_text)
{
	int i;
	i = 0;
	while (my_text[i])
	{
		printf("i = %d %s\n", i, my_text[i]);
		i++;
	}
	printf("\n\n");
}
//

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

	// (void)argc;
	// (void)argv;
	str = NULL;
	all = 0;
	// tmp_env = init_env(env);
	// if (!tmp_env)
	// {
	// 	printf("minishell %s\n", strerror(errno));
	// 	return (errno);
	// }
	// init_shlvl(&tmp_env);
	// signal_on();
	tmp_env = preparation(argc, argv, env);
	while (1)
	{
		/*all = init_struct(tmp_env);*/
		/*if (!all)*/
		/*{*/
			/*ft_free(tmp_env);*/
			/*return (errno);*/
		/*}*/
		// str = readline("☠️  $ ");
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
		/* Здесь есть парсер.*/
		/*printf("|%s|\n", str);*/
		if (mini_preparser(str))
		{
			free(str);
			continue ;
		}
		parser(&str, tmp_env, &all);
		/*А здесть нет. */
		start_minishell(all);
		if (tmp_env)
			free_split(tmp_env);
		tmp_env = (all->env);
		if (!tmp_env)
			printf("minishell %s\n", strerror(errno));
		if (str)
			free(str);

		t_all *all_s = all;
		while (all_s)
		{
			ft_free(all_s->argv);
			// ft_free(all->env);
			all_s = all_s->next;
			// free(tmp);
		}
		free_struct(&all);
		// system("leaks minishell");// для проверки утечек
	}
	clear_history();
	/*ft_free(tmp_env);*/
	return (0);
}
