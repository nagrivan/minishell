/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:13:35 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/07 19:55:13 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	text_write(int flag, char *text)
{
	int		i;
	
	i = 0;
	while (text)
	{
		if (text[i] == '$')
		{
			if (text[++i] == '?')
				ft_putnbr_fd(, 1); /*необходима переменная, которая будет сохранять код ошибки*/
		}
		ft_putchar_fd(text[i], 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

void	flag_n(char *flag, char *text)
{
	int		i;
	
	i = 1;
	if (!(ft_strncmp(flag, "-n", 2)))
	{
		while (flag[i] && flag[i] == 'n')
			i++;
		if (i == ft_strlen(flag))
			text_write(1, text);
	}
	ft_putstr_fd(flag, 1);
	write(1, " ", 1);
}

int		my_echo(char *flag, char *text)
{
	if (flag)
		flag_n(flag, text);
	text_write(0, text);
	return (0);
}