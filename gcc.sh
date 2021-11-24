#!/bin/zsh
#

if [ "$1" = 'clean' ]
then
	rm -rf a.out
	rm -rf a.out.dSYM/
	echo "TRAHNUL MAKEFILE"
	return
fi

if [ "$1" = 'leak' ]
then
	gcc -g main.c dollar.c quotes.c func.c libft/libft.a
	valgrind --leak-check=full ./a.out
	return
fi
gcc $1 $2 main.c dollar.c quotes.c func.c libft/libft.a
./a.out

