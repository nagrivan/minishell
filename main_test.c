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
	tmp->argv = (char **)malloc(sizeof(char *) * 3);
	tmp->argv[0] = "echo";
	tmp->argv[1] = "Bye!";
	tmp->argv[2] = NULL;
	tmp->dother = 0;
	tmp->fd[0] = dup(STDIN_FILENO);
	tmp->fd[1] = dup(STDOUT_FILENO);
	tmp->next = NULL;
	tmp->num_redir = 1;
	tmp->path = NULL;
	tmp->pipe = 0;
	tmp->redir = (t_redirect *)malloc(sizeof(t_redirect) * tmp->num_redir);
	tmp->redir[0].filename = "file2";
	tmp->redir[0].type_redir = DOB_TO;
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

char	**init_env(char **env)
{
	char	**result;
	int		i;
	int		size;

	size = num_argv(env);
	result = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		result[i] = ft_strdup(env[i]);
		if (!result[i])
			return (NULL);
	}
	result[i] = NULL;
	return (result);
}

t_env	*init_struct_pipe(char **env)
{
	t_env *tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->env = init_env(env);
	tmp->argv = NULL;
	tmp->dother = 0;
	tmp->fd[0] = dup(STDIN_FILENO);
	tmp->fd[1] = dup(STDOUT_FILENO);
	tmp->next = NULL;
	tmp->num_redir = 0;
	tmp->path = NULL;
	tmp->pipe = 0;
	tmp->redir = NULL;
	return (tmp);
}


void go_pipe(t_env *tmp, char **env)
{
	char *str;
	char **my_text;
	int size;
	int i = 0;

	str = readline("mini_test$ ");
	// printf("str = %s\n", str);
	if (!(my_text = ft_split(str, '|')))
	{
		free(str);
		exit(28);
	}
	size = num_argv(my_text);
	while (i < size)
	{
		tmp->argv = ft_split(my_text[i], ' ');
		if (!tmp->argv)
		{
			free(str);
			exit(66);
		}
		tmp->pipe = i;
		i++;
		if (i < size)
			tmp->next = init_struct_pipe(env);
		tmp = tmp->next;
	}
	tmp = NULL;
	free(str);
	ft_free(my_text);
}

int main(int argc, char **argv, char **env)
{
	t_env *tmp;
	// int pipes = 0;
	// int status = 0;
	char **tmp_env;

	(void)argc;
	(void)argv;
	int g = 0;
	tmp_env = init_env(env);
	if (!tmp_env)
		return (13);
	while (g < 5)
	{
		tmp = init_struct_pipe(tmp_env);
		go_pipe(tmp, tmp_env);
		start_minishell(tmp);
		// while (pipes < (num_pipe(tmp) + 1))
		// {
		// 	waitpid(0, &status, WUNTRACED);
		// 	pipes++;
		// }
		tmp_env = init_env(tmp->env);
		while(tmp != NULL)
		{
			free(tmp->argv);
			ft_free(tmp->env);
			tmp = tmp->next;
			// free(tmp);
		}
		// system("leaks minitest");
		g++;
	}
	// ft_free(tmp->env); //ошибка valgrind
	return (0);
}