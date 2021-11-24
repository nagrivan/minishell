# include "minishell.h"

static char	*clean_quotes(char *str, int first/*1 кавычка*/, int last/*последняя кавычка*/)
{
	char *res;
	char *tmp;
	char *strdup;

	res = 0;
	str[first] = 0;
	str[last] = 0;
	res = ft_strdup(str);
	tmp = res;
	strdup = ft_strdup(str + first + 1);
	res = ft_strjoin(tmp, strdup);
	free(tmp);
	free(strdup);
	strdup = 0;
	tmp = 0;
	if (ft_strlen(str) - 1 != last)
	{
		tmp = res;
		strdup = ft_strdup(str + last + 1);
		res = ft_strjoin(tmp, strdup);
		free(tmp);
		free(strdup);
	}
	return res;
}

static char	*single_quotes(char *str, int *i, char *token)
{
	int		first;
	int		last;
	char	*res;

	char *tmp = ft_strdup(str);
	if (str != token)
		free(str);
	first = *i;
	while (tmp[first] != '\'')
		first++; // нашли 1 кавычку
	last = first + 1;
	while (tmp[last] != '\'')
		last++; // нашли 2 кавычку
	res = clean_quotes(tmp, first, last);
	*i = last - 1;
	free(tmp);
	return (res);
}

static char	*double_quotes(char *str, int *i, char *token)
{
	int		first;
	int		last;
	char	*res;

	char *tmp = ft_strdup(str);
	if (str != token)
		free(str);
	first = *i;
	while (tmp[first] != '\"')
		first++; // нашли 1 кавычку
	last = first + 1;
	while (tmp[last] != '\"')
		last++; // нашли 2 кавычку
	res = clean_quotes(tmp, first, last);
	*i = last - 1;
	free(tmp);
	return (res);
}

static char *clean_all_quotes(char *token)
{
	int i;
	int prev_i;
	char *res;
	/*char *tmp;*/

	i = 0;
	res = token;
	while (i < ft_strlen(res) && res[i])
	{
		prev_i = i;
		if (res[i] == '\"')
			res = double_quotes(res, &i, token);
		else if (res[i] == '\'')
			res = single_quotes(res, &i, token);
		if (i == prev_i)
			i++;
	}
	return res;
}

static int quotes_or_not(char *token)
{
	int i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char **clear_tokens(char **tokens, int num)
{
	int i;
	char **result;

	i = -1;
	result = malloc(sizeof(char*) * (num + 1));
	while (++i < num + 1)
		result[i] = 0;
	i = 0;
	while (tokens[i])
	{
		if (quotes_or_not(tokens[i]))
			result[i] = clean_all_quotes(tokens[i]);
		else
			result[i] = ft_strdup(tokens[i]);
		i++;
	}
	free_all(tokens, num);
	return (result);
}
