/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:01:30 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/27 19:23:38 by nagrivan         ###   ########.fr       */
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
}

void	my_sigquit(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b", 4);
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
		write(1, "\n", 1);
	}
	if (WTERMSIG(status) == 3)
	{
		write(1, " \bQuit: 3\n", 10);
	}
}

static void	my_sigint_her(int signal)
{
	(void)signal;
	write(0, "\b\b  \b\b", 6);
	exit(130);
}

static void	my_sigquit_her(int signal)
{
	(void)signal;
	write(0, "\b\b  \b\b", 6);
}

void	signal_on_her(void)
{
	signal(SIGQUIT, my_sigquit_her);
	signal(SIGINT, my_sigint_her);
}
