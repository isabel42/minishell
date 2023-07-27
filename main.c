/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 17:15:45 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	signal(SIGUSR1, ft_user);
	env_copy1(env);
}

int	ft_lstsize_adhoc(t_list *block)
{
	t_list	*test;
	int		lst_size;

	test = block;
	lst_size = ft_lstsize(test);
	return (lst_size);
}

int	ft_loop_prompt(t_list **block, int **pid_o, int **p1, int lst_size)
{
	int		i;
	int		size_pid;
	t_param	*param;
	t_block	*block_content;
	t_list	*test;

	i = 0;
	test = *block;
	size_pid = 0;
	while (test)
	{
		block_content = (t_block *)test->content;
		g_data.status = 0;
		param = ft_param_c(lst_size, block_content, i, p1);
		if (ft_built_exec(param) == -1)
			ft_fork(param, p1, pid_o, &size_pid);
		ft_free_param(param);
		test = test->next;
		i++;
	}
	return (size_pid);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*block;
	int		*pid;
	int		**p1;
	int		lst_size;
	int		size_pid;

	check_args(argc, argv, env);
	while (42)
	{
		block = ft_block();
		if (block == NULL)
			return (0);
		lst_size = ft_lstsize_adhoc(block);
		pid = malloc(sizeof(int));
		if (!pid)
			return (0);
		p1 = ft_pipe(lst_size);
		size_pid = ft_loop_prompt(&block, &pid, p1, lst_size);
		ft_lstclear(&block, (void *) &ft_clean_block);
		ft_closepipe(p1, lst_size);
		ft_waitpid(pid, size_pid);
		free(pid);
		ft_free_pipe(p1, lst_size);
	}
	return (0);
}
