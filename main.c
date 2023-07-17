/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/17 13:25:16 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_loop(char **param, char **flags)
{
	ft_free_param(param);
	free(flags);
}

void	ft_checkarg(int argc)
{
	if (argc < 4)
	{
		ft_putstr_fd("Not enough arguments\n", 1);
		exit(0);
	}
}

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
		flags[j] = b_c->arg[j - 1];
		j--;
	}
	return (flags);
}

int	main (int argc, char **argv, char **env)
{
	t_list	*block;
	t_list	*test;
	t_block	*block_content;
	char	**flags;
	int 	*pid;
	int		**p1;
	int		i = 0;
	char	**param;
	int		lst_size;

	(void) argv;
	if (env == NULL)
	{
		printf("Error : env is NULL\n");
		exit(-1);
	}
	if (argc != 1)
	{
		printf("Minishell don't take any argument\n");
		exit(1);
	}
	// init_termios();
	// signal(SIGINT, custom_handler);
	// signal(SIGQUIT, custom_handler);
	env_copy1(env);
	while (42)
	{
		block = ft_block();
		test = block;
		lst_size = ft_lstsize(test);
		pid = malloc(sizeof(pid) *(lst_size));
		p1 = ft_pipe(lst_size);
		test = block;
		i = 0;
		while (test)
		{
			block_content = (t_block *) test->content;
			param = ft_param(lst_size, block_content);
			flags = ft_flags_execve(block_content);
			pid[i] = fork();
			if (pid[i] == 0)
				ft_fork(param, p1, flags, i);
			test = test->next;
			i++;
		}
		ft_lstclear(&block, (void *) &ft_clean_block);
		ft_closepipe(p1, lst_size);
		ft_waitpid(pid);
	}
	return (0);
}
