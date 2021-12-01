#include "minishell.h"

static int	valid_sym(char c)
{
	if (c == '_' || ft_isalnum(c))
		return 1;
	return 0;
}

static char	*swap(char **str, char *val, int *i, int j)
{
	char	*dst;
	char	*dst2;
	char	*tmp;

	dst = ft_substr(*str, 0, j);
	dst2 = ft_strdup(*str + *i);
	tmp = dst;
	dst = ft_strjoin(dst, val);
	free(tmp);
	tmp = dst;
	dst = ft_strjoin(dst, dst2);
	free(tmp);
	free(dst2);
	return (dst);
}

static char	*env_not_exist(char **str, int *i, int j)
{
	char	*dst;
	char	*dst2;
	char	*res;

	dst = ft_substr(*str, 0, j);
	dst2 = ft_strdup(*str + *i);
	res = ft_strjoin(dst, dst2);
	free(dst);
	free(dst2);
	*i -= *i - j;
	free(*str);
	return (res);
}

int	find_arg(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '=' && s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	find_name(char **env, char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (find_arg(env[i], arg))
			return (i + 1);
		i++;
	}
	return (0);
}

char	*get_env(char **env, char *arg)
{
	int		index;
	int		i;
	char	*ret;

	i = -1;
	index = find_name(env, arg) - 1;
	if (index != -1)
	{
		ret = env[index];
		while (env[index] && env[index][++i] != '=')
			ret++;
		return (++ret);
	}
	return (0);
}

char	*dollar(char **str, int *i, char **env)
{
	int		j;
	char	*val;
	char	*arg;

	(void)env;
	j = *i;
	if ((*str)[(*i) + 1] == '?')
	{
		(*i) += 2;
		arg = swap(str, ft_itoa(exit_status), i, j);
		(*i)--;
		free(*str);
		return (arg);
	}
	while ((*str)[++(*i)])
		if (!valid_sym((*str)[*i]))
			break ;
	if (*i == j + 1)
		return (*str);
	arg = ft_substr(*str, j + 1, *i - j - 1);
	val = get_env(env, arg);
	free(arg);
	if (!val)
		return (env_not_exist(str, i, j));
	arg = swap(str, val, i, j);
	free(*str);
	if ((*i - j) > ft_strlen(val))
		*i -= *i - j - ft_strlen(val);
	else
		*i += ft_strlen(val) - (*i - j);
	return (arg);
}
