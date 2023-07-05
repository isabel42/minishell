/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/05 14:57:30 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	find_index_envp(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
	}
	return (i);
}

char	*ft_getpath(char **envp, char *prog)
{
	char	**env;
	char	*path;
	char	*new_path;
	char	*temp;
	int		i;

	path = NULL;
	i = find_index_envp(envp);
	env = ft_split(envp[i] + 5, ':');
	i = -1;
	while (env[++i])
	{
		temp = ft_strjoin(env[i], "/");
		new_path = ft_strjoin(temp, prog);
		free(temp);
		if (access(new_path, X_OK | F_OK) == 0)
		{
			path = new_path;
			break ;
		}
		else
			free(new_path);
	}
	free_tab(env);
	return (path);
}

int	main (int argc, char **argv, char **env)
{
	t_list	*block;
	t_list	*test;
	t_block	*block_content;

	(void) argc;
	(void) argv;
	init_termios();
	signal(SIGINT, custom_handler);
	signal(SIGQUIT, custom_handler);
	while (42)
	{
		block = ft_block();
		test = block;
		while (block)
		{
			block_content = (t_block *) test->content;
			check_builtin(block_content->cmd, block_content->arg, env_copy1(env));
			block = block->next;
		}
		// if (ft_exec(&block) == -1)
		// 	exit(-1);
	}
		// ft_lstclear(&block, (void *) &ft_clean_block);
		//check_builtin("cd", ft_split(prompt, ' '), env_copy);
		// while (test)
		// {
		// 	content = (t_type *) test->content;
		// 	test = test->next;
		// }
		// command = ft_find_comm_path(ft_envp(envp, "PATH="), inputs->txt);
		// inputs = inputs->next;
		// pid = fork();
		// if (pid == 0)
		// 	execve(command, ft_flags(envp, &inputs), NULL);
		// waitpid(pid, NULL, 0);
		// ft_lstclear(&block, ft_clean_block(block->content));
	return (0);
}
