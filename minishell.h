/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:21:27 by nagrivan          #+#    #+#             */
/*   Updated: 2021/10/05 15:24:03 by nagrivan         ###   ########.fr       */
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

typedef struct s_env
{
	char	**env;
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

#endif