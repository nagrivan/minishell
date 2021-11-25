# include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_all *all;
	int jopa = 1;
	int kota = 0;
	int	i = 0;
	all = 0;	/*all = init_struct(env);*/
	while (!0 && 1 == 1 && jopa != kota/*бескоечный цикл*/)
	{
		char *promt = "💀$ ";
		write(1, promt, ft_strlen(promt));
		char *str = malloc(sizeof(char) * 1000);
		for (int i = 0; i < 1000; i++)
			str[i] = 0;
		int r = read(0, str, 1000);
		if (r != 0)
			str[r - 1] = 0;
		else
		{
			free(str);
			return 0;
		}
		parser(&str, env, &all);
		free_struct(&all);
		all = 0;
		free(str);
	}
}
