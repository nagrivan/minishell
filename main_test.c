/*
Это тестовый main, который предназначен
для тестирования различных функций до написания основного парсера
*/

#include "minishell.h"

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

void	init_test_struct(t_env *tmp)
{
	tmp->argv = NULL;
	tmp->dother = 0;
	tmp->fd[0] = dup(STDIN_FILENO);
	tmp->fd[1] = dup(STDOUT_FILENO);
	tmp->next = NULL;
	tmp->num_redir = 0;
	tmp->path = NULL;
	tmp->pipe = 0;
	tmp->redir = NULL;
	tmp->status = 0;
}

int	init_struct(t_env *tmp, char **env)
{
	int	i = 0;
	int size = num_argv(env);

	tmp->env = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!tmp->env)
		return (1);
	while (env[i])
	{
		tmp->env[i] = ft_strdup(env[i]);
		if (!tmp->env[i])
			return (1);
		i++;
	}
	tmp->env[i] = NULL;
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char *str;
	// char **my_text;
	t_env tmp;

	(void)argc;
	(void)argv;
	if ((init_struct(&tmp, env)) != 0)
		return (1);
	int g = 0;
	while (g < 1)
	{
		init_test_struct(&tmp);
		str = readline("mini_test$ ");
		if (!(tmp.argv = ft_split(str, ' ')))
		{
			free(str);
			return (1);
		}
		start_minishell(&tmp);
		// ft_free(tmp.argv);
		// free(str);
		g++;
		// system("leaks minitest");
	}
	// ft_free(tmp.env); //ошибка valgrind
	return (0);
}