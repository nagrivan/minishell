#include "parser.h"

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

char	*dollar(char **str, int *i, char **env)
{
	int		j;
	char	*val;
	char	*arg;

	j = *i;
	while ((*str)[++(*i)])
		if (!valid_sym((*str)[*i]))
			break ;
	if (*i == j + 1)
		return (*str);
	arg = ft_substr(*str, j + 1, *i - j - 1);
	val = getenv(arg);
	free(arg);
	if (!val)
		return (*str);
	arg = swap(str, val, i, j);
	free(*str);
	if ((*i - j) > ft_strlen(val))
		*i -= *i - j - ft_strlen(val);
	printf("dollar arg = %s\n", arg);
	return (arg);
}
