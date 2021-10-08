/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:13:35 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/06 16:55:51 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Подумать о сокращении функции text_write
	(возможно, перенести обработку $? в парсер)
	проверено Norminette
	check leaks
	+++
*/

void	text_write(int flag, char **text)
{
	int		i;
	int		j;
 /* переменная, ответственная за статус работы предыдущей команды */
	int		status = 0;

	i = flag;
	while (text[i])
	{
		j = 0;
		while (text[i][j])
		{
			if (text[i][j] == '$')
			{
				if (text[i][++j] == '?')
				{
				/*необходима переменная, которая будет сохранять код ошибки*/
					ft_putnbr_fd(status, 1);
					j++;
				}
			}
			ft_putchar_fd(text[i][j], 1);
			j++;
		}
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
