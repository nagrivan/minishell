# include "minishell.h"

char	*env_variables(char *str, char **env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i] != '\0')
			{
				if (str[i] == '$')
					str = dollar(&str, &i, env);
				if (str[i] == '\"')
				{
					i++;
					break ;
				}
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '$')
			str = dollar(&str, &i, env);
		else 
			i++;
	}
	return (str);
}

int		tokens_number(char	*str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]) && str[i] != '\0')
		{
			i = ft_strchr(str + i + 1, str[i]) + 1 - str;
			if (ft_strchr(" \t><|\0", str[i]))
				num++;
			continue;
		}
		if (!ft_strchr(" \t><|\0", str[i]) && ft_strchr(" \t><|\0", str[i + 1]))
			num++;
		if (ft_strchr("<>|", str[i]) && str[i] != '\0')
			i += (num++ && str[i + 1] == str[i]);
		i += (str[i] != '\0');
	}
	return (num);
}

char *new_token(char *start, char *end)
{
	char	*tmp;
	char	*token;

	token = malloc(sizeof(char) * (end - start) + 1);
	tmp = start;
	while(tmp != end)	
	{
		token[tmp - start] = *tmp;
		++tmp;
	}
	token[tmp - start] = '\0';
	return token;
}

char	**split_tokens(char *str, int num)
{
	char	**tokens;
	int		i;
	int 	j; // start
	int		n;

	tokens = (char **)malloc(sizeof(char *) * (num + 1));
	i = 0;
	while (i < num + 1)
		tokens[i++] = 0;
	n = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		while (str[i] && ft_strchr("\"\'", str[i]) && str[i] == str[i + 1] && ft_strchr("\'\" \t><|\0", str[i + 2]))
			i += 2;
		if (!ft_strchr(" \t><|\0", str[i]))
		{
			j = i;
			while (!ft_strchr(" \t><|\0", str[i]))
			{
				if (ft_strchr("\"\'", str[i]))
					i = ft_strchr(str + i + 1, str[i]) - str;
				i++;
				if (ft_strchr(" \t><|\0", str[i]))
					tokens[n++] = new_token(str + j, str + i);
			}
		}
		if (ft_strchr("<>|", str[i]) && str[i] != '\0')
		{
			j = i;
			i += 1 + (str[i + 1] == str[i]);
			tokens[n++] = new_token(str + j, str + i);
		}
	}
	return (tokens);
}

int find_pipe(char **tokens)
{
	int i = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "|") == 0)
			return 1;
		i++;
	}
	return 0;
}

void	fill_new_node(char **tokens, t_all **all, char **env)
{
	t_all	*tmp;
	int		pipe_n;
	t_all	*node;
	
	node = init_struct_sanya(env);
	num_of_redir(tokens, node);
	num_of_argv(tokens, node);
	fill_argv(tokens, node);
	if (node->num_redir != 0)
		fill_redir(tokens, node);
	if (*all == 0)
	{
		*all = node;
		(*all)->pipe = 1;
	}
	else
	{
		tmp = *all;
		pipe_n = 2;
		while (tmp->next)
		{
			tmp = tmp->next;
			pipe_n++;
		}
		tmp->next = node;
		tmp = tmp->next;
		tmp->pipe = pipe_n;
	}
}

void	parser(char **str, char **env, t_all **all)
{
	int		i;
	int		num;
	char	**tokens;

	i = 0;
	*str = env_variables(*str, env);
	num = tokens_number(*str);
	tokens = split_tokens(*str, num);
	tokens = clear_tokens(tokens, num);
	while (find_pipe(tokens))
	{
		fill_new_node(tokens, all, env);
		tokens = trim_tokens(tokens);
	}
	fill_new_node(tokens, all, env);
	
	//ВЫВОД
	/*printf_node(*all);*/
	free_split(tokens);
}

void free_struct(t_all **all)
{
	t_all *plist;
	t_all *ptmp;

	if (!*all)
		return ;
	plist = *all;
	/*printf("in free %p\n", plist);*/
	ptmp = *all;
	while (plist)
	{
		ptmp = plist->next;
		free_split(plist->argv);
		int i = 0;
		while (i < plist->num_redir)
		{
			free(plist->redir[i].filename);
			i++;
		}
		free(plist->redir);
		free(plist);
		plist = ptmp;
	}
	*all = 0;
}
