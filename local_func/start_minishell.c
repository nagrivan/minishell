/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:06:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/12/01 19:06:22 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_patch(t_all *all)
{
	int		i;
	char	*free_str;

	i = -1;
	while (all->path[++i])
	{
		free_str = all->path[i];
		all->path[i] = ft_strjoin(all->path[i], "/");
		free(free_str);
		if (!all->path[i])
		{
			printf("minishell %s\n", strerror(errno));
			return (-1);
		}
	}
	i = -1;
	while (all->path[++i])
	{
		free_str = all->path[i];
		all->path[i] = ft_strjoin(all->path[i], all->argv[0]);
		free(free_str);
		if (!all->path[i])
			return (-1);
		if (!(access(all->path[i], X_OK)))
		{
			free_str = all->argv[0];
			all->argv[0] = ft_strdup(all->path[i]);
			free(free_str);
			if (!all->argv[0])
			{
				printf("minishell %s\n", strerror(errno));
				return (-1);
			}
			return (0);
		}
	}
	return (1);
}

int	create_path(t_all *all)
{
	int			geolock;
	char		*paths;

	paths = NULL;
	geolock = check_env("PATH", all->env);
	if (geolock == -1)
	{
		printf("minishell: %s: No such file or directory\n", all->argv[0]);
		return (127);
	}
	paths = ft_strtrim(all->env[geolock], "PATH=");
	if (!paths)
	{
		printf("minishell: %s: No such file or directory\n", all->argv[0]);
		return (127);
	}
	all->path = ft_split(paths, ':');
	if (!all->path)
		return (-1);
	if ((check_patch(all)))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(all->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit_status = 127;
		free_split(all->path);
		free(paths);
		return (-1);
	}
	free_split(all->path);
	free(paths);
	return (0);
}

int	check_execve(t_all *all)
{
	pid_t		pid;
	int			fd[2];

	if ((access(all->argv[0], X_OK)) != 0)
		if ((create_path(all)))
			return (1);
	if ((pipe(fd)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		exit_status = errno;
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("minishell %s\n", strerror(errno));
		exit_status = errno;
		return (1);
	}
	if (pid == 0)
	{
		if ((close(fd[0])) == -1)
		{
			printf("minishell: Invalid close\n");
			return (1);
		}
		if ((close(fd[1])) == -1)
		{
			printf("minishell: Invalid close\n");
			return (1);
		}
		execve(all->argv[0], all->argv, all->env);
	}
	else
	{
		if ((close(fd[1])) == -1)
		{
			printf("minishell: Invalid close\n");
			return (1);
		}
		if ((dup2(fd[0], STDIN)) == -1)
		{
			printf("minishell %s\n", strerror(errno));
			exit_status = errno;
			return (1);
		}
		if ((close(fd[0])) == -1)
		{
			printf("minishell: Invalid close\n");
			return (1);
		}
	}
	return (0);
}

int	is_bildins(t_all *all)
{
	if (!(ft_strncmp(all->argv[0], "echo", 5)))
		exit_status = my_echo(all->argv);
	else if (!(ft_strncmp(all->argv[0], "cd", 3)))
		exit_status = my_cd(all);
	else if (!(ft_strncmp(all->argv[0], "exit", 5)))
		exit_status = my_exit(all);
	else if (!(ft_strncmp(all->argv[0], "env", 4)))
		exit_status = my_env(all);
	else if (!(ft_strncmp(all->argv[0], "export", 7)))
		exit_status = my_export(all);
	else if (!(ft_strncmp(all->argv[0], "pwd", 4)))
		exit_status = my_pwd();
	else if (!(ft_strncmp(all->argv[0], "unset", 6)))
		exit_status = my_unset(all);
	else
		return (0);
	return (1);
}

void	start_minishell(t_all *all)
{
	int		i;
	int		count_pipe;
	int		tmp_fd[2];
	int		status;

	i = all->num_redir;
	count_pipe = num_pipe(all);
	tmp_fd[0] = dup(STDIN_FILENO);
	if (tmp_fd[0] == -1)
	{
		printf("minishell %s\n", strerror(errno));
		exit_status = errno;
		return ;
	}
	tmp_fd[1] = dup(STDOUT_FILENO);
	if (tmp_fd[1] == -1)
	{
		printf("minishell %s\n", strerror(errno));
		exit_status = errno;
		return ;
	}
	while (all != NULL)
	{
		if (count_pipe > 1)
			my_pipe(all, count_pipe, tmp_fd);
		else // вынести в отдельную функцию
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
					if ((close(all->redir[i].fd)) == -1)
					{
						printf("minishell: Invalid close\n");
						return ;
					}
					if ((dup2(all->redir[i].tmp_fd, all->redir[i].fd)) == -1)
					{
						printf("minishell %s\n", strerror(errno));
						return ;
					}
				}
			}
		}
		all = all->next;
	}
	i = -1;
	while (++i <= count_pipe)
	{
		signal_off();
		if (WIFSIGNALED(status))
			signal_dother(status);
		else
			if (count_pipe || WEXITSTATUS(status))
				exit_status = WEXITSTATUS(status);
		waitpid(0, &status, WUNTRACED);
		signal_on();
	}
	if ((dup2(tmp_fd[0], STDIN_FILENO)) == -1)
	{
		printf("minishell %s\n", strerror(errno));
		exit_status = errno;
	}
}
