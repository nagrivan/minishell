/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:51:10 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/25 18:55:15 by nagrivan         ###   ########.fr       */
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

char	*get_value(char *str, int *index)
{
	int	i;

	i = 0;
	while (str && str[i] != '=')
		i++;
	*index = ++i;
	return (str + i);
}

void	init_shlvl(char ***env)
{
	int		i;
	int		numb;
	int		len;
	char	*str;
	char	*number;

	i = check_exp("SHLVL=", *(env), 6);
	if (i != -1)
	{
		numb = ft_atoi(get_value((*env)[i], &len));
		str = ft_substr((*env)[i], 0, len);
		number = ft_itoa(++numb);
		free((*env)[i]);
		(*env)[i] = ft_strjoin(str, number);
		free(str);
		free(number);
	}
}

char	**init_env(char **env)
{
	int		i;
	int		size;
	char	**result;

	i = -1;
	size = num_argv(env);
	result = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!result)
		return (NULL);
	while (env[++i])
	{
		result[i] = ft_strdup(env[i]);
		if (!result[i])
		{
			printf("minishell %s\n", strerror(errno));
			return (NULL);
		}
	}
	result[i] = NULL;
	return (result);
}

t_all	*init_struct(char **env)
{
	t_all	*tmp;

	tmp = (t_all *)malloc(sizeof(t_all));
	if (!tmp)
	{
		printf("minishell %s\n", strerror(errno));
		return (NULL);
	}
	tmp->env = init_env(env);
	tmp->argv = NULL;
	tmp->dother = 0;
	tmp->fd[0] = dup(STDIN_FILENO);
	if (tmp->fd[0] == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return (NULL);
	}
	tmp->fd[1] = dup(STDOUT_FILENO);
	if (tmp->fd[1] == -1)
	{
		printf("minishell %s\n", strerror(errno));
		return (NULL);
	}
	tmp->next = NULL;
	tmp->num_redir = 0;
	tmp->path = NULL;
	tmp->pipe = 0;
	tmp->redir = NULL;
	tmp->status = 0;
	return (tmp);
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
	init_shlvl(&tmp_env); // leaks
	signal_on();
	while (1)
	{
		/*all = init_struct(tmp_env);*/
		/*if (!all)*/
		/*{*/
			/*ft_free(tmp_env);*/
			/*return (errno);*/
		/*}*/
		str = readline("☠️  $ ");
		if (str)
			add_history(str);
		else
		{
			rl_on_new_line();
			rl_redisplay();
			write(1, "\033[Aexit\n", 9);
			exit(0);
		}
		/* Здесь должен быть парсер.
			А могла быть ваша реклама. */
		/*printf("|%s|\n", str);*/
		parser(&str, env, &all);
		/*start_minishell(all);*/
		/*tmp_env = init_env(all->env);*/
		if (!tmp_env)
			printf("minishell %s\n", strerror(errno));
		if (str)
			free(str);
		/*while (all != NULL)*/
		/*{*/
			/*free(all->argv);*/
			/*ft_free(all->env);*/
			/*all = all->next;*/
			/*// free(tmp);*/
		/*}*/
		free_struct(&all);
		 /*system("leaks minishell");// для проверки утечек*/
	}
	clear_history();
	/*ft_free(tmp_env);*/
	return (0);
}
