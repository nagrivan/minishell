/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:13:35 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 14:44:50 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	text_write(int flag, char **text)
{
	int		i;

	i = flag;
	while (text[i])
	{
		ft_putstr_fd(text[i], 1);
		if (text[++i] != NULL)
			write(1, " ", 1);
	}
	if (flag == 1)
		write(1, "\n", 1);
}

int	flag_n(char **text)
{
	int		i;
	int		j;
	int		flag;

	i = 1;
	flag = 1;
	while (text[i])
	{
		if (!(ft_strncmp(text[i], "-n", 2)))
		{
			j = 1;
			while (text[i][j] && text[i][j] == 'n')
				j++;
			if (j != (int)ft_strlen(text[i]))
				return (flag);
			flag += 1;
		}
		if (flag == 1)
			return (1);
		i++;
	}
	return (flag);
}

int	my_echo(char **text)
{
	int		flag;

	flag = flag_n(text);
	if (flag > 1)
		text_write(flag, text);
	else
		text_write(1, text);
	return (0);
}
