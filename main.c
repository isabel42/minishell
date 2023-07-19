/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/19 15:03:57 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_loop(t_param *param, char **flags)
{
	int	i;

	i = 1;
	ft_free_param(param);
	while (flags[i] != NULL)
	{
		free(flags[i]);
		i++;
	}
	free(flags);
}

void	ft_checkarg(int ac, char **av, char **env)
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
		pid = malloc(sizeof(pid) *(lst_size));
		p1 = ft_pipe(lst_size);
		test = block;
		i = 0;
		while (test)
		{
			block_content = (t_block *) test->content;
			param = ft_param(lst_size, block_content);
			check_builtin(param);
			pid[i] = fork();
			if (pid[i] == 0)
				ft_fork(param, p1, param->flags, i);
			ft_free_loop(param, param->flags);
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
