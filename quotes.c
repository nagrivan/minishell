# include "minishell.h"

static char	*clean_quotes(char **str, int *i, int j)
{
	char	*res;
	char	*res2;
	char	*res3;
	char	*tmp;

	res = ft_substr(*str, 0, j);
	res2 = ft_substr(*str, j + 1, *i - j - 1);
	res3 = ft_strdup(*str + *i + 1);
	tmp = res;
	res = ft_strjoin(res, res2);
	free(tmp);
	free(res2);
	tmp = res;
	res = ft_strjoin(res, res3);
	free(tmp);
	free(res3);
	return (res);
}

char	*single_quotes(char **str, int *i)
{
	int		j;
	char	*res;

	j = *i;
	while ((*str)[++(*i)])
		if ((*str)[*i] == '\'')
			break ;
	res = clean_quotes(str, i, j);
	free(*str);
	printf("i=%d single res = %s\n", *i,res);
	*i -= 1;
	return (res);
}

char	*double_quotes(char **str, int *i, char **env)
{
	int		j;
	char	*res;

	j = *i;
	while ((*str)[++(*i)])
	{
		if ((*str)[*i] == '$')
			*str = dollar(str, i, env);
		if ((*str)[*i] == '\"')
			break ;
	}
	res = clean_quotes(str, i, j);
	free(*str);
	printf("i=%d double res = %s\n",*i, res);
	*i -= 1;
	return (res);
}
