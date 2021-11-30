/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:06:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/30 13:22:34 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_bildins(t_all *all)
{
	if (!(ft_strncmp(all->argv[0], "echo", 5)))
		g_exit_status = my_echo(all->argv);
	else if (!(ft_strncmp(all->argv[0], "cd", 3)))
		g_exit_status = my_cd(all);
	else if (!(ft_strncmp(all->argv[0], "exit", 5)))
		g_exit_status = my_exit(all);
	else if (!(ft_strncmp(all->argv[0], "env", 4)))
		g_exit_status = my_env(all);
	else if (!(ft_strncmp(all->argv[0], "export", 7)))
		g_exit_status = my_export(all);
	else if (!(ft_strncmp(all->argv[0], "pwd", 4)))
		g_exit_status = my_pwd();
	else if (!(ft_strncmp(all->argv[0], "unset", 6)))
		g_exit_status = my_unset(all);
	else
		return (0);
	return (1);
}

void	one_command(t_all *all, int *tmp_fd, int i)
{
	if (all->redir)
		what_is_redir(all);
	if (all->argv && all->argv[0] && !(is_bildins(all)))
		if (!all->redir || all->redir[all->num_redir - 1].file_d != -1)
			check_execve(all);
	while (--i >= 0)
	{
		if ((close(all->redir[i].fd)) == -1)
		{
			printf("minishell: Invalid close\n");
			return ;
		}
		if (all->redir[i].type_redir != HEREDOC)
		{
			if ((dup2(all->redir[i].tmp_fd, all->redir[i].fd)) == -1)
			{
				printf("minishell %s\n", strerror(errno));
				return ;
			}
		}
	}	
}

void	end_command(int count_pipe, int *tmp_fd)
{
	int		i;
	int		status;

	i = -1;
	while (++i <= count_pipe)
	{
		signal_off();
		if (WIFSIGNALED(status))
			signal_dother(status);
		else
			if (count_pipe || WEXITSTATUS(status))
				g_exit_status = WEXITSTATUS(status);
		waitpid(0, &status, WUNTRACED);
		signal_on();
	}
	if ((dup2(tmp_fd[0], STDIN_FILENO)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		g_exit_status = errno;
	}
}

void	minishell_error(void)
{
	printf("minishell %s\n", strerror(errno));
	g_exit_status = errno;
}

void	start_minishell(t_all *all)
{
	int		i;
	int		count_pipe;
	int		tmp_fd[2];

	i = all->num_redir;
	count_pipe = num_pipe(all);
	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	if (tmp_fd[0] == -1 || tmp_fd[1] == -1)
	{
		minishell_error();
		return ;
	}
	while (all != NULL)
	{
		if (count_pipe > 1)
			my_pipe(all, count_pipe, tmp_fd);
		else
			one_command(all, tmp_fd, i);
		all = all->next;
	}
	end_command(count_pipe, tmp_fd);
}
