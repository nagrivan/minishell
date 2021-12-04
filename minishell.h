/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:21:27 by nagrivan          #+#    #+#             */
/*   Updated: 2021/11/25 19:05:57 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>

# define STDIN 0
# define STDOUT 1

# define ONE_FROM 0 // <
# define ONE_TO 1 // >
# define DOB_TO 2 // >>
# define HEREDOC 3 // <<

int	g_exit_status;

typedef struct s_redirect
{
	char		*filename;
	int			type_redir;
	int			file_d;
	int			fd;
	int			tmp_fd;
}	t_redirect;

typedef struct s_all
{
	char			**path;
	char			**env;
	char			**argv;
	int				fd[2];
	t_redirect		*redir;
	int				num_redir;
	int				num_argv;
	pid_t			dother;
	int				pipe;
	int				status;
	struct s_all	*next;
}	t_all;

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

int		write_pwd_oldpwd(t_all *all, char *old_pwd, char *pwd);
char	**sort_all(char **env, int len);
/*
	Вспомогательная функция
*/
int		num_argv(char **argv);
void	ft_free(char **my_text);
t_all	*init_struct(char **env);
int		write_env(char *result, t_all *all);
void	ft_print(char **my_text);
int		check_env(char *argv, char **env);
int		write_env(char *result, t_all *all);
int		check_exp(char *argv, char **env, size_t size);
int		my_export_argv(char *argv);
size_t	check_equals(char *argv);

void	init_shlvl(char ***env);

/*
	Запуск команд
*/
void	start_minishell(t_all *all);
int		create_path(t_all *all);
int		is_bildins(t_all *all);
int		one_command(t_all *all);
/*
	Редиректы и пайпы
*/
void	what_is_redir(t_all *all);
void	my_pipe(t_all *all, int count_pipe, int *tmp_fd);
int		num_pipe(t_all *all);

void	redir_heredoc(t_all *all, int i);

/*
	Сигналы
*/
void	signal_on(void);
void	signal_off(void);
void	signal_dother(int status);
void	signal_on_her(void);

// void	rl_replace_line(const char *text, int clear_undo);

/*
	Функции парсера:
*/
char	*env_variables(char *str, char **env);
void	parser(char **str, char **env, t_all **all);
char	**init_env(char **env);
//
int		mini_preparser(char *str);

int		valid_sym(char c);
char	*swap(char **str, char *val, int *i, int j);
char	*get_env(char **env, char *arg);

int		quotes_or_not(char *token);
char	*clean_all_quotes(char *token);

int		find_pipe(char **tokens);
char	*new_token(char *start, char *end);
int		ft_strcmp(char *s1, char *s2);
void	free_struct(t_all **all);
void	free_split(char **s);

void	num_of_redir(char **str, t_all *tmp);
void	num_of_argv(char **str, t_all *tmp);
void	fill_argv(char **tokens, t_all *tmp);
void	fill_redir(char **tokens, t_all *node);

void	fill_new_node(char **tokens, t_all **all, char **env);
char	**trim_tokens(char **str);

#endif
