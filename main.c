/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/27 12:25:41 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_envp(char **envp, char *pwd)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], pwd, ft_strlen(pwd)) == 0)
// 			return (envp[i] + ft_strlen(pwd));
// 		i++;
// 	}
// 	return (NULL);
// }

// void	ft_free_cc(char **split)
// {
// 	int	i;

// 	i = 0;
// 	while (split[i])
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// }

// void	ft_free_cc_c(char **cc, char *c)
// {
// 	ft_free_cc(cc);
// 	free(c);
// }

// char	*ft_find_comm_path(char *path, char *command)
// {
// 	char	**path_split;
// 	char	*path_command;
// 	char	*slash_command;
// 	int		i;

// 	if (access(command, X_OK) == 0)
// 		return (command);
// 	i = 0;
// 	if (command)
// 	{
// 		slash_command = ft_strjoin("/", command);
// 		path_split = ft_split(path, ':');
// 		while (path_split[i])
// 		{
// 			path_command = ft_strjoin(path_split[i], slash_command);
// 			if (access(path_command, X_OK) == 0)
// 			{
// 				ft_free_cc_c(path_split, slash_command);
// 				return (path_command);
// 			}
// 			free(path_command);
// 			i++;
// 		}
// 		ft_free_cc_c(path_split, slash_command);
// 	}
// 	return (NULL);
// }

// char *ft_arg_q(char *arg)
// {
// 	int		i;
// 	char	*new;
// 	int		len;

// 	len = (int) ft_strlen(arg);
// 	i = 1;
// 	new = malloc(sizeof(char) * (len + 3));
// 	if (!new)
// 		return (0);
// 	new[0] = '"';
// 	while(i < len + 1)
// 	{
// 		new[i] = arg[i - 1];
// 		i++;
// 	}
// 	new[i] = '"';
// 	new[i + 1] = '\0';
// 	free(arg);
// 	return (new);
// }

// char	**ft_flags(char **envp, t_list **inputs)
// {
// 	char	**flags;
// 	t_list	*one;
// 	t_list	*two;
// 	int		count;
// 	int		i;

// 	count = 0;
// 	one = *inputs;
// 	two = *inputs;
// 	i = 1;
// 	while (one && one->arg == 1)
// 	{
// 		count++;
// 		one = one->next;
// 	}
// 	flags = malloc(sizeof(char *) * count + 2);
// 	if (!flags)
// 		exit(0);
// 	flags[0] = ft_envp(envp, "PATH=");
// 	while (i < count + 1)
// 	{
// 		flags[i] = two->txt;
// 		two = two->next;
// 		i++;	
// 	}
// 	flags[i] = NULL;
// 	return (flags);
// }

int	main (int argc, char **argv, char **envp)
{
	char	*prompt;
	// char	*command;
	//int		pid;
	t_list	*inputs;
	t_list	*test;
	t_type	*content;

	(void) argc;
	(void) argv;
	(void) envp;
	inputs = NULL;
	while (42)
	{
		//pid = 0;
		prompt = readline("minishell> ");
		add_history(prompt);
		inputs = ft_parsing(prompt, "\'\"");
		ft_find_type(&inputs);
		test = inputs;
		check_builtin()
		// while (test)
		// {
		// 	content = (t_type *) test->content;
		// 	// printf("txt:%s\n",content->txt);
		// 	printf("%s : infile %d : outfile %d :cmd %d : c_g %d : c_d %d : dc_g %d : dc_d %d : pipe %d : arg %d\n", content->txt, content->infile, content->outfile, content->cmd, content->c_g, content->c_d, content->dc_g, content->dc_d, content->pipe, content->arg);
		// 	test = test->next;
		// }
		// command = ft_find_comm_path(ft_envp(envp, "PATH="), inputs->txt);
		// inputs = inputs->next;
		// pid = fork();
		// if (pid == 0)
		// 	execve(command, ft_flags(envp, &inputs), NULL);
		// waitpid(pid, NULL, 0);
		// free(prompt);
	}
	return (0);
}
