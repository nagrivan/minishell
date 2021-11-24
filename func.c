# include "minishell.h"

/*t_env   *init_struct_pipe(char **env)*/
/*{*/
    /*t_env *tmp;*/
    /*tmp = (t_env *)malloc(sizeof(t_env));*/
    /*tmp->env = init_env(env);*/
    /*tmp->argv = NULL;*/
    /*tmp->dother = 0;*/
    /*tmp->fd[0] = dup(STDIN_FILENO);*/
    /*tmp->fd[1] = dup(STDOUT_FILENO);*/
    /*tmp->next = NULL;*/
    /*tmp->num_redir = 0;*/
    /*tmp->path = NULL;*/
    /*tmp->pipe = 0;*/
    /*tmp->redir = NULL;*/
    /*return (tmp);*/
/*}*/

t_all	*init_struct(char **env)
{
	t_all	*tmp;

	(void)env;
	tmp = (t_all *)malloc(sizeof(t_all));
	/*if (!tmp)*/
	/*{*/
		/*printf("minishell %s\n", strerror(errno));*/
		/*return (NULL);*/
	/*}*/
	/*tmp->env = init_env(env);*/
	tmp->argv = NULL;
	tmp->dother = 0;
	/*tmp->fd[0] = dup(STDIN_FILENO);*/
	/*if (tmp->fd[0] == -1)*/
	/*{*/
		/*printf("minishell %s\n", strerror(errno));*/
		/*return (NULL);*/
	/*}*/
	/*tmp->fd[1] = dup(STDOUT_FILENO);*/
	/*if (tmp->fd[1] == -1)*/
	/*{*/
		/*printf("minishell %s\n", strerror(errno));*/
		/*return (NULL);*/
	/*}*/
	tmp->next = NULL;
	tmp->num_redir = 0;
	tmp->num_argv = 0;
	tmp->path = NULL;
	tmp->pipe = 0;
	tmp->redir = NULL;
	tmp->status = 0;
	return (tmp);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return 1;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return 1;
		i++;
	}
	return 0;
}

void	num_of_redir(char **str, t_all *tmp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], ">") ||
			!ft_strcmp(str[i], "<") ||
			!ft_strcmp(str[i], ">>") ||
			!ft_strcmp(str[i], "<<"))
			tmp->num_redir++;
		if (ft_strcmp(str[i], "|") == 0)
			break;
		i++;
	}
}

void	num_of_argv(char **str, t_all *tmp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") == 0)
			break;
		if (!ft_strcmp(str[i], ">") ||
			!ft_strcmp(str[i], "<") ||
			!ft_strcmp(str[i], ">>") ||
			!ft_strcmp(str[i], "<<"))
		{
			i += 2;
			continue;
		}
		tmp->num_argv++;
		i++;
	}
}

void	free_split(char **s)
{
	int i = 0;

	while (s[i])
		free(s[i++]);
	free(s);
}

void	fill_argv(char **tokens, t_all *tmp)
{
	int	i;
	int	j;

	tmp->argv = malloc(sizeof(char *) * (tmp->num_argv + 1));
	tmp->argv[tmp->num_argv] = 0;
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			break;
		if (!ft_strcmp(tokens[i], ">") ||
			!ft_strcmp(tokens[i], "<") ||
			!ft_strcmp(tokens[i], ">>") ||
			!ft_strcmp(tokens[i], "<<"))
		{
			i += 2;
			continue;
		}
		tmp->argv[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
}

char**	trim_tokens(char **str, t_all *tmp)
{
	char **tmp_jopa = str;
	char **new_str;
	int i_ = 0;
	while (tmp_jopa[i_] && tmp_jopa[i_][0] != '|')
		i_++;
	if (tmp_jopa[i_])
	{
		i_++;
		int new_tokens_num = 0;
		int old_i = i_;
		while (tmp_jopa[i_])
		{
			new_tokens_num++;
			i_++;
		}
		new_str = malloc(sizeof(char *) * (new_tokens_num + 1));
		new_str[new_tokens_num] = 0;
		int i = 0;
		while (tmp_jopa[old_i])
		{
			new_str[i] = ft_strdup(tmp_jopa[old_i]);
			i++;
			old_i++;
		}
		free_split(str);
	}
	return (new_str);
}
