/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:21:27 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/27 17:55:36 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	Предполагаемая структура для записи
	переменных окружения
*/

typedef struct s_list // Предлагаю записывать в листы переменные окружения
{
	void			*content;
	struct s_list	*next;
} t_list;

/*
	Увидела идею: для облегчения сортировки можно разделить одну строку
	с переменной окружения на две части:
	1) Название переменной;
	2) Содержание самой переменной;
	Затем происходит сортировка по названию переменных методом пузырька.
	В этой версии такой подход не реализован, но идея интересная и над этим можно подумать.
	
	P.S. В одной из структур должно идти деление на название и на содержание. Подумать, в какой.
*/
typedef struct	s_env
{
	t_list			*list_env; //лист, где содержится переменная окружения
	int				number; //номер листа с переменной окружения
} t_env;

/*
	Структура для записи команд, флагов и аргументов
*/
typedef struct s_comand
{
	char			**comand; //Пока что предлагаю все записывать в двойной массив (и команды, и аргументы)
} t_comand;

/*
	Общая структура для объединения остальных структур
*/
typedef struct s_all
{
	t_env			*env_dt;
	t_comand		*comand;
	int				pipe; //Пока эта переменная просто считает количество пайпов. 
	int				redir; //см. переменную pipe
} t_all;


/*
	Функции builtins. Нуждаются в правке и пересмотре аргументов.
*/
int		my_cd(char **argv, char **env);
int		my_echo(char *flag, char **text);
int		my_env(char *argv, char **env);
int		my_exit(char **argv);
int		my_export(char *argv, char **env);
int		my_pwd(void);
int		my_unset(char *argv, char **env);

#endif