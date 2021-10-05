/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:13:35 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/29 16:41:33 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	text_write(int flag, char **text)
{
	int		i;
	int		j;
	int		status = 0; /*переменная, ответственная за статус работы предыдущей команды*/
	
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
					ft_putnbr_fd(status, 1); /*необходима переменная, которая будет сохранять код ошибки*/
					j++;
				}
			}
			ft_putchar_fd(text[i][j], 1);
			j++;
		}
		if (text[++i] != NULL)
			write(1, " ", 1);
		// i++;
	}
	if (flag == 1)
		write(1, "\n", 1);
}

int		flag_n(char **text)
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

int		my_echo(char **text)
{
	int		flag;
	
	flag = flag_n(text);
	if (flag > 1)
		text_write(flag, text);
	else
		text_write(1, text);
	return (0);
}