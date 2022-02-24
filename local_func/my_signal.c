/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:01:30 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 15:19:21 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_sigint(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	my_sigquit(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b", 4);
	g_exit_status = 0;
}

void	signal_on(void)
{
	signal(SIGQUIT, my_sigquit);
	signal(SIGINT, my_sigint);
}

void	signal_off(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	signal_dother(int status)
{
	if (WTERMSIG(status) == 2)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
	if (WTERMSIG(status) == 3)
	{
		write(1, " \bQuit: 3\n", 10);
		g_exit_status = 131;
	}
}
