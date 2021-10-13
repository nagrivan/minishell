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

int	check_execve(char **my_text, t_env *env)
{
	int			geolock;
	char		*paths;

	paths = NULL;
	geolock = check_env("PATH", env->env);
	if (geolock == -1)
	{
		printf("minishell: %s: No such file or directory\n", my_text[0]);
		return (127);
	}
	paths = ft_strtrim(env->env[geolock], "PATH=");
	if (!paths)
	{
		printf("minishell: %s: No such file or directory\n", my_text[0]);
		return (127);
	}
	env->path = ft_split(paths, ':');
	if (!env->path)
		return (-1);
	execve(my_text[0], my_text, env->path);
	return (0);
}

int	check_argv(char **my_text, t_env *env)
{
	what_is_redir(env);
	if (!(ft_strncmp(my_text[0], "echo", 5)))
		my_echo(my_text);
	if (!(ft_strncmp(my_text[0], "cd", 3)))
		my_cd(my_text, env);
	if (!(ft_strncmp(my_text[0], "exit", 5)))
		my_exit(my_text);
	if (!(ft_strncmp(my_text[0], "env", 4)))
		my_env(my_text, env);
	if (!(ft_strncmp(my_text[0], "export", 7)))
		my_export(my_text, env);
	if (!(ft_strncmp(my_text[0], "pwd", 4)))
		my_pwd();
	if (!(ft_strncmp(my_text[0], "unset", 6)))
		my_unset(my_text, env);
	else
		if ((check_execve(my_text[0], env)) != 0)
			return (1);
	return (0);
}

// int	check_redir(char **my_text, t_env *env)
// {
// 	int i = 0;
// 	int j = 0;
// 	int num_redir = 0;
// 	while (my_text[i])
// 	{
// 		if (my_text[i][0] == '>' || my_text[i][0] == '<')
// 			num_redir++;
// 		i++;
// 	}
// 	if (num_redir == 0)
// 		return (0);
// 	env->redir = (t_redirect *)ft_calloc(sizeof(t_redirect), num_redir);
// 	i = -1;
// 	j = -1;
// 	while (++i < num_redir)
// 	{
// 		if (my_text[++j][0] == '>' || my_text[++j][0] == '<')
// 		{
// 			if (!(ft_strncmp(my_text[j], ">", 2)))
// 				env->redir[i].type_redir = ONE_TO;
// 			if (!(ft_strncmp(my_text[j], ">>", 3)))
// 				env->redir[i].type_redir = DOB_TO;
// 			if (!(ft_strncmp(my_text[j], "<", 2)))
// 				env->redir[i].type_redir = ONE_FROM;
// 			if (!(ft_strncmp(my_text[j], "<<", 3)))
// 				env->redir[i].type_redir = HEREDOC;
// 			env->redir[i].filename = ft_strdup(my_text[j + 1]);
// 			env->redir[i].file_d = 0;
// 		}
// 	}
// 	return (0);
// }

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
		if ((check_argv(my_text, &tmp)) != 0) //ошибка valgrind
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
	// ft_free(tmp.env); //ошибка valgrind
	return (0);
}