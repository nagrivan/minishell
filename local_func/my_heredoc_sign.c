/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:52:46 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/14 16:53:22 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	my_sigint_her(int signal)
{
	(void)signal;
	write(0, "\b\b  \b\b", 6);
	g_exit_status = 130;
	exit(130);
}

void	signal_on_her(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_sigint_her);
}
