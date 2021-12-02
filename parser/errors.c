/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralverta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:48:09 by ralverta          #+#    #+#             */
/*   Updated: 2021/12/02 09:48:26 by ralverta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	some_errors(char *str, int *i)
{
	if (ft_strchr("\"\'", str[*i]))
	{
		if (!ft_strchr(str + *i + 1, str[*i]))
			return (print_error('q'));
		*i = ft_strchr(str + *i + 1, str[*i]) - str;
	}
	if (str[*i] == '|')
	{
		(*i)++;
		while (str[*i] == ' ' || str[*i] == '\t')
			(*i)++;
		if (str[*i] == '|' || str[*i] == 0)
			return (print_error('|'));
	}
	if (str[*i] == '|' || str[*i] == ';')
	{
		while (str[*i] == ' ' || str[*i] == '\t')
			(*i)++;
		if (str[*i] == ';')
			return (print_error(';'));
	}
	return (0);
}

static int	redir_errors(char *str, int *i)
{
	if (ft_strchr("><", str[*i]) && str[*i] == str[*i + 1])
		(*i)++;
	if (ft_strchr("><", str[*i]))
	{
		(*i)++;
		while (str[*i] == ' ' || str[*i] == '\t')
			(*i)++;
		if (str[*i] == 0)
			return (print_error('n'));
		if (ft_strchr("><", str[*i]))
			return (print_error('r'));
		if (str[*i] == '|')
			return (print_error('|'));
	}
	return (0);
}

int	mini_preparser(char *str)
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
		if (some_errors(str, &i))
			return (1);
		if (redir_errors(str, &i))
			return (1);
		i += (str[i] != 0);
	}
	return (0);
}
