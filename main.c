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

void	parser(char **str, char **env, t_all *tmp)
{
	int		i;
	int		num;
	char	**tokens;

	i = 0;
	*str = env_variables(*str, env);
	num = tokens_number(*str);
	printf("FINAL NUMBER OF TOKENS IS %d\n", num);
	tokens = split_tokens(*str, num);
	tokens = clear_tokens(tokens, num);
	/*while (tokens[i])*/
	/*{*/
		/*printf("Token number %d is \t|\033[32m%s\033[0m|\n", i + 1, tokens[i]);*/
		/*i++;*/
	/*}*/

	while (find_pipe(tokens))
	{
		num_of_redir(tokens, tmp);
		num_of_argv(tokens, tmp);
		fill_argv(tokens, tmp);
		printf("\n");
		printf("NUM OF REDIR = %d\n", tmp->num_redir);
		printf("NUM OF ARGV = %d\n", tmp->num_argv);
		i = 0;
		while (ft_strcmp(tokens[i], "|"))
		{
			printf("Token number %d is \t|\033[32m%s\033[0m|\n", i + 1, tokens[i]);
			i++;
		}
		tokens = trim_tokens(tokens, tmp);
		tmp->num_redir = 0;
		tmp->num_argv = 0;
	}
	num_of_redir(tokens, tmp);
	num_of_argv(tokens, tmp);
	printf("\n");
	printf("NUM OF REDIR = %d\n", tmp->num_redir);
	printf("NUM OF ARGV = %d\n", tmp->num_argv);
	tmp->num_redir = 0;
	tmp->num_argv = 0;
	i = 0;
	while (tokens[i])
	{
		printf("Token number %d is \t|\033[32m%s\033[0m|\n", i + 1, tokens[i]);
		i++;
	}

	/*tokens = fill_struct(tokens, tmp);*/
	/*i = 0;*/
	/*while (tokens[i])*/
	/*{*/
		/*printf("Token number %d is \t|\033[32m%s\033[0m|\n", i + 1, tokens[i]);*/
		/*i++;*/
	/*}*/
	free_split(tokens);
	/*free_all(tokens, num);*/
}

void	free_all(char **token, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		free(token[i]);
	free(token);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_all *tmp;
	int jopa = 1;
	int kota = 0;
	int	i = 0;
	tmp = init_struct(env);
	while (!0 && 1 == 1 && jopa != kota/*бескоечный цикл*/)
	{
		char *promt = "💀$ ";
		write(1, promt, ft_strlen(promt));
		char *str = malloc(sizeof(char) * 1000);
		for (int i = 0; i < 1000; i++)
			str[i] = 0;
		int r = read(0, str, 1000);
		if (r != 0)
			str[r - 1] = 0;
		else
		{
			free(str);
			return 0;
		}
		parser(&str, env, tmp);
		while (tmp->argv[i])
		{
			printf("\nARGV %d is \t|\033[32m%s\033[0m|\n", i + 1, tmp->argv[i]);
			i++;
		}
		free(str);
	}
}
