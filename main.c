/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimitomat <kimitomat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/10 17:34:54 by kimitomat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main (int argc, char **argv, char **env)
{
	t_list	*block;
	t_list	*test;
	t_block	*block_content;
	int 	i = 0;

	(void) argv;
	if (argc != 1)
	{
		printf("Minishell don't take any argument\n");
		exit(1);
	}
	//init_termios();
	//signal(SIGINT, custom_handler);
	//signal(SIGQUIT, custom_handler);
	env_copy1(env);
	while (42)
	{
		block = ft_block();
		test = block;
		while (test)
		{
			block_content = (t_block *) test->content;
			printf("block %d \ncommand: %s\n",i, block_content->cmd);
			printf("ags: %s\n\n", block_content->arg[0]);
			//if (block_content->infile[0])
				//printf("infile: %s\n\n", block_content->infile[0]);
			//check_builtin(block_content->cmd, block_content->arg);
			//if (block_content->infile[0][0] == '2')
				//ft_heredoc(block_content);
			test = test->next;
			i++;
		}
		ft_lstclear(&block, (void *) &ft_clean_block);
		// command = ft_find_comm_path(ft_envp(envp, "PATH="), inputs->txt);
		// inputs = inputs->next;
		// pid = fork();
		// if (pid == 0)
		// 	execve(command, ft_flags(envp, &inputs), NULL);
		// waitpid(pid, NULL, 0);
		// ft_lstclear(&block, ft_clean_block(block->content));
	}
	return (0);
}
