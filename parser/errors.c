# include "minishell.h"

static int	print_error(char c)
{
	if (c == '|')
		printf("syntax error near unexpected token \'|\'\n");
	if (c == ';')
		printf("syntax error near unexpected token \';\'\n");
	if (c == 'q')
		printf("error: unclosed quotes\n");
	if (c == 'r')
		printf("error: double redirect\n");
	if (c == 'n')
		printf("syntax error near unexpected token \'newline\'\n");
	return (1);
}

int		mini_preparser(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '|' || str[i] == ';')
	{
		print_error(str[i]);
		return (1);
	}
	while (str[i])
	{
		if (ft_strchr("\"\'", str[i]))
		{
			if (!ft_strchr(str + i + 1, str[i]))
				return (print_error('q'));
			i = ft_strchr(str + i + 1, str[i]) - str;
		}
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '|' || str[i] == 0)
				return (print_error('|'));
		}
		if (str[i] == '|' || str[i] == ';')
		{
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == ';')
				return (print_error(';'));
		}
		if (ft_strchr("><", str[i]) && str[i] == str[i + 1])
			i++;
		if (ft_strchr("><", str[i])) 
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == 0)
				return (print_error('n'));
			if (ft_strchr("><", str[i]))
				return (print_error('r'));
			if (str[i] == '|')
				return (print_error('|'));
		}
		i += (str[i] != 0);
	}
	return (0);
}
