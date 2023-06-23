/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/23 14:57:09 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_envp(char **envp, char *pwd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], pwd, ft_strlen(pwd)) == 0)
			return (envp[i] + ft_strlen(pwd));
		i++;
	}
	return (NULL);
}

void	ft_free_cc(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_cc_c(char **cc, char *c)
{
	ft_free_cc(cc);
	free(c);
}

char	*ft_find_comm_path(char *path, char *command)
{
	char	**path_split;
	char	*path_command;
	char	*slash_command;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	i = 0;
	if (command)
	{
		slash_command = ft_strjoin("/", command);
		path_split = ft_split(path, ':');
		while (path_split[i])
		{
			path_command = ft_strjoin(path_split[i], slash_command);
			if (access(path_command, X_OK) == 0)
			{
				ft_free_cc_c(path_split, slash_command);
				return (path_command);
			}
			free(path_command);
			i++;
		}
		ft_free_cc_c(path_split, slash_command);
	}
	return (NULL);
}

char *ft_arg_q(char *arg)
{
	int		i;
	char	*new;
	int		len;

	len = (int) ft_strlen(arg);
	i = 1;
	new = malloc(sizeof(char) * (len + 3));
	if (!new)
		return (0);
	new[0] = '"';
	while(i < len + 1)
	{
		new[i] = arg[i - 1];
		i++;
	}
	new[i] = '"';
	new[i + 1] = '\0';
	free(arg);
	return (new);
}

char	**ft_flags(char **envp, t_list **inputs)
{
	char	**flags;
	t_list	*one;
	t_list	*two;
	int		count;
	int		i;

	count = 0;
	one = *inputs;
	two = *inputs;
	i = 1;
	while (one && one->arg == 1)
	{
		count++;
		one = one->next;
	}
	flags = malloc(sizeof(char *) * count + 2);
	if (!flags)
		exit(0);
	flags[0] = ft_envp(envp, "PATH=");
	while (i < count + 1)
	{
		flags[i] = two->txt;
		two = two->next;
		i++;
	}
	flags[i] = NULL;
	return (flags);
}

// les handler font des segfault avec tout les autres signaux, mais ctrl c marche bien
void	custom_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	custom_handler1(int signal)
{
	(void)signal;
	exit(0);
}

int	boucle(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*command;
	int		pid;
	t_list	*inputs;
	t_list	*temp;

	(void) argc;
	(void) argv;
	(void) envp;
	inputs = NULL;
	signal(SIGINT, custom_handler);
	signal(SIGQUIT, custom_handler1);
	while (42)
	{
		pid = 0;
		prompt = readline("minishell> ");
		add_history(prompt);
		inputs = ft_parsing(prompt, "\'\"");
		ft_find_type(&inputs);
		temp = inputs;
		while (inputs)
		{
			printf("txt:%s:\n", inputs->txt);
			inputs = inputs->next;
		}
		inputs = temp;
		command = ft_find_comm_path(ft_envp(envp, "PATH="), inputs->txt);
		pid = fork();
		if (pid == 0)
			execve(command, ft_flags(envp, &inputs), NULL);
		waitpid(pid, NULL, 0);
		free(prompt);
		inputs = NULL;
	}
	return (0);
}

int	main (int argc, char **argv, char **envp)
{
	init_termios();
	boucle(argc, argv, env_copy(envp));
	return (0);
}
