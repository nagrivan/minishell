/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:21:27 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/14 15:10:29 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define	STDIN 0
# define	STDOUT 1

# define	ONE_FROM 0
# define	ONE_TO 1
# define	DOB_TO 2
# define	HEREDOC 3

typedef struct s_redirect
{
	char		*filename;
	int			type_redir;
	int				file_d;
} t_redirect;


typedef struct s_env
{
	char			**path; //пути из $PATH
	char			**env; //переменные окружения
	char			**argv; //сами команды + флаги + аргументы
	int				fd[2];
	t_redirect		*redir;
	int				num_redir;
	pid_t			dother;
	int				pipe;
	int				status;
	struct s_env	*next;
} t_env;

/*
	Функции builtins
*/
int		my_cd(char **argv, t_env *env);
int		my_echo(char **text);
int		my_env(char **argv, t_env *env);
int		my_exit(char **argv);
int		my_export(char **argv, t_env *env);
int		my_pwd(void);
int		my_unset(char **argv, t_env *env);
void	what_is_redir(t_env *env);

/*
	Вспомогательная функция
*/
int			num_argv(char **argv);
void		ft_free(char **my_text);
int			init_struct(t_env *tmp, char **env);
int			write_env(char *result, t_env *env);
void		ft_print(char **my_text);
int			check_env(char *argv, char **env);
int			check_exp(char *argv, char **env, size_t size);
int			my_export_argv(char *argv);
size_t		check_equals(char *argv);

/*
	Редиректы и пайпы
*/
void	what_is_redir(t_env *env);
void	my_pipe(t_env *env);

#endif