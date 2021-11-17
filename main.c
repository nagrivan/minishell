# include "minishell.h"

char	*env_variables(char **str, char **env)
{
	int	i;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] != '\'' && (*str)[i] != '\0')
				i++;
		}
		if ((*str)[i] == '$')
			*str = dollar(str, &i, env);
		if ((*str)[i] == '\0')
			break ;
	}
	return (*str);
}


char *new_token(char *start, char *end)
{
	char	*tmp;
	char	*token;
	
	token = malloc(sizeof(char) *(end - start));
	tmp = start;
	while(tmp != end)	
	{
		*token[tmp - start] = *tmp;
		++tmp;
	}
	token[tmp - start] = '\0';
	return token;
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
			i = ft_strchr(str + i + 1, str[i]) - str;
			num++;
		}
		else if (ft_strchr("<>|", str[i]) && str[i] != '\0')
		{
			i += (str[i + 1] == str[i]);
			num++;
		}
		else if (!ft_strchr(" \t><|\0", str[i]) && ft_strchr(" \t><|\0", str[i + 1]))
			num++;
		i += (str[i] != '\0');
	}
	return (num);
}

void	parser(char **str, char **env, t_all **all)
{
	int		i;
	char	**tokens;
	int		num;

	i = -1;
	*str = env_variables(str, env);
	num = tokens_number(*str);
	printf("FINAL NUMBER OF TOKENS IS %d\n", tokens_number(*str));
	tokens = (char **)malloc(sizeof(char *) * num + 1);
	while (++i < num)
	{
		tokens[i] = (char *)malloc(sizeof(char) *
	}

}

int	main(int argc, char **argv, char **env)
{
	t_all *all;
	char *str = ft_strdup("\'1 TOKEN\'\"2 TOKEN\"ls <> 1");

	printf("str = %s\n", str);
	parser(&str, env, &all);
	//env_variables(&str, env);
	printf("result = %s\n", str);
	free(str);
	//while (1);
}

/*void	parser(char **str, char **env)
{
	int	i;
						// МЫ НЕ СОЗДАЕМ ЗДЕСЬ tmp, ЧТОБЫ ОЧИЩАТЬ str, КОТОРЫЙ ПЕРЕЗАПИСЫВАЕТСЯ
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\'')
		{
			*str = single_quotes(str, &i);
			printf("index = %d\n", i);
		}
		if ((*str)[i] == '\"')
			*str = double_quotes(str, &i, env);
		if ((*str)[i] == '$')
			*str = dollar(str, &i, env);
		if (((*str)[i] == ' ' || (*str)[i] == '\t') && ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\t'))
		{
			*str = space(str, &i);
			printf("index = %d\n", i);
		}
		if ((*str)[i] == '\0')
			break ;
	}
}*/
