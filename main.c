/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/20 14:06:41 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**ft_flags_execve(t_block *b_c)
{
	char	**flags;
	int		j;

	j = 0;
	while (b_c->arg[j] != NULL)
		j++;
	flags = malloc(sizeof(char *) * (j + 2));
	flags[0] = ft_envp(g_data.env_copy, "PWD=");
	flags[j + 1] = NULL;
	while (j > 0)
	{
		flags[j] = malloc(sizeof(char) * (1 + ft_strlen(b_c->arg[j - 1])));
		if (!flags[j])
			return (NULL);
		ft_strlcpy(flags[j], b_c->arg[j - 1], ft_strlen(b_c->arg[j - 1]) + 1);
		j--;
	}
	return (flags);
}

void	check_args(int ac, char **av, char **env)
{
	(void)av;
	if (env == NULL)
	{
		printf("Error : env is NULL\n");
		exit(-1);
	}
	if (ac != 1)
	{
		printf("Minishell don't take any argument\n");
		exit(1);
	}
	init_termios();
	signal(SIGINT, custom_handler);
	signal(SIGQUIT, custom_handler);
	env_copy1(env);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*block;
	t_list	*test;
	t_block	*block_content;
	int		*pid;
	int		**p1;
	int		i = 0;
	t_param	*param;
	int		lst_size;

	check_args(argc, argv, env);
	while (42)
	{
		block = ft_block();
		test = block;
		lst_size = ft_lstsize(test);
		pid = malloc(sizeof(int));
		if (!pid)
			return (0);
		p1 = ft_pipe(lst_size);
		test = block;
		i = 0;
		while (test)
		{
			block_content = (t_block *) test->content;
			param = ft_param(lst_size, block_content, i, p1);
			if (ft_built_exec(param) == -1)
			{
				pid = ft_new_pid(pid);
				ft_fork(param, p1, pid);
			}
			ft_free_param(param);
			test = test->next;
			i++;
		}
		ft_lstclear(&block, (void *) &ft_clean_block);
		ft_closepipe(p1, lst_size);
		ft_waitpid(pid);
		free(pid);
		ft_free_pipe(p1, lst_size);
	}
	return (0);
}
