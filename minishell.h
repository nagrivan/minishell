/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:21:27 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/26 16:51:38 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define	STDIN 0
# define	STDOUT 1

# define	ONE_FROM 0 // <
# define	ONE_TO 1 // >
# define	DOB_TO 2 // >>
# define	HEREDOC 3 // <<

typedef struct s_redirect
{
	char		*filename;
	int			type_redir;
	int			file_d;
	int			fd;
	int			tmp_fd;
} t_redirect;

typedef struct s_all
{
	char			**path; //пути из $PATH
	char			**env; //переменные окружения
	char			**argv; //сами команды + флаги + аргументы
	int				fd[2]; 
	t_redirect		*redir;
	int				num_redir;
	int				num_argv;
	pid_t			dother;
	int				pipe;
	int				status;
	struct s_all	*next;
} t_all;

/*
	Функции builtins
*/
int		my_cd(t_all *all);
int		my_echo(char **text);
int		my_env(t_all *all);
int		my_exit(t_all *all);
int		my_export(t_all *all);
int		my_pwd(void);
int		my_unset(t_all *all);

/*
	Вспомогательная функция
*/
int			num_argv(char **argv);
void		ft_free(char **my_text);
t_all		*init_struct(char **env);
int			write_env(char *result, t_all *all);
void		ft_print(char **my_text);
int			check_env(char *argv, char **env);
int			check_exp(char *argv, char **env, size_t size);
int			my_export_argv(char *argv);
size_t		check_equals(char *argv);

/*
	Запуск команд
*/
void	start_minishell(t_all *all);

/*
	Редиректы и пайпы
*/
void	what_is_redir(t_all *all);
void	my_pipe(t_all *all, int count_pipe, int *tmp_fd);
int		num_pipe(t_all *all);
int		create_path(t_all *all);
int		is_bildins(t_all *all);

/*
	Функции парсера:
*/
char	*dollar(char **str, int *i, char **env);
void	free_all(char **token, int num);
char	**clear_tokens(char **tokens, int num);
char	**trim_tokens(char **str, t_all *tmp);
void	num_of_redir(char **str, t_all *tmp);
void	num_of_argv(char **str, t_all *tmp);
void	free_split(char **s);
int		ft_strcmp(char *s1, char *s2);
void	fill_argv(char **tokens, t_all *tmp);


#endif
