/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:06:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/02 19:51:03 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_execve(t_all *all)
{
	pid_t		pid;
	int			fd[2];

	if ((access(all->argv[0], X_OK)) != 0)
		if ((create_path(all)))
			return (1);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		execve(all->argv[0], all->argv, all->env);
		return (0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		close(fd[0]);
	}
	return (0);
}

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

void	one_command(t_all *all, int i)
{
	if (all->redir)
		what_is_redir(all);
	if (all->argv && all->argv[0] && !(is_bildins(all)))
		if (!all->redir || all->redir[all->num_redir - 1].file_d != -1)
			check_execve(all);
	while (--i >= 0)
	{
		if (all->redir[i].tmp_fd != -1 && all->redir[i].fd != -1)
		{
			close(all->redir[i].fd);
			dup2(all->redir[i].tmp_fd, all->redir[i].fd);
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
	dup2(tmp_fd[0], STDIN_FILENO);
	close(tmp_fd[0]);
	close(tmp_fd[1]);
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
	while (all != NULL)
	{
		if (count_pipe > 1)
		{
			my_pipe(all, count_pipe, tmp_fd);
			close(all->fd[0]);
			close(all->fd[1]);
		}
		else
			one_command(all, i);
		close(all->fd[0]);
		close(all->fd[1]);
		all = all->next;
	}
	end_command(count_pipe, tmp_fd);
}
