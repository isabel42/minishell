/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/19 19:46:07 by itovar-n         ###   ########.fr       */
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

	if(access(command, X_OK) == 0)
		return(command);
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


char	**ft_flags(char **envp, char *prompt)
{
	char	**flags;
	char	*only_flag;
	int		j;

	flags = malloc(sizeof(flags) * 3);
	if (!flags)
		exit(0);
	j = 0;
	while (prompt[j] != ' ' && prompt[j] != '\0')
		j++;
	if (prompt[j] == '\0')
		only_flag = NULL;
	else
	{
		while (prompt[j] == ' ')
			j++;
		if (prompt[j] == '\0')
			only_flag = NULL;
		else
			only_flag = prompt + j;
	}
	flags[0] = ft_envp(envp, "PATH=");
	flags[1] = only_flag;
	flags[2] = NULL;
	return (flags);
}

char *ft_cp_line(char *prompt, int *i, int j)
{
	char	*res;

	res = malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	res[j + 1] = prompt[*i + j + 1];
	while (j >= 0)
	{
		res[j] = prompt[*i + j];
		j--;
	}
	*i = *i + ft_strlen(res);
	return(res);
}

char	*ft_promt_line(char *prompt, int *i, char a)
{
	char	*res;
	int		j;

	j = 0;
	res = NULL;
	while (prompt[*i] != '\0')
	{
		if (prompt[*i] == a)
		{
			while (prompt[*i + j + 1] != a && prompt[*i + j] != '\0')
				j++;
			res = ft_cp_line(prompt, i, j);
			if (!res)
				return ("Error in malloc");
			break ;
		}
		*i = *i + 1;
	}
	return (res);
}

int main (int argc, char **argv, char **envp)
{
	char	*prompt;
	// char	**split_prompt;
	char	*command;
	int		pid;

	(void) argc;
	(void) argv;
	(void) envp;

	while (42)
	{
		pid = 0;
		prompt = readline("minishell> ");
		add_history(prompt);
		while (prompt[pid] != '\0')
		{
			command = ft_promt_line(prompt, &pid, '"');
			printf("txt: %s\n", command);
			command = ft_promt_line(prompt, &pid, '\'');
			printf("txt: %s\n", command);
		}
		// split_prompt = ft_split(prompt, ' ');
		// command = ft_find_comm_path(ft_envp(envp, "PATH="), split_prompt[0]);
		// pid = fork();
		// if (pid == 0)
		// 	execve(command, ft_flags(envp, prompt), NULL);
		// waitpid(pid, NULL, 0);
	}
	return (0);
}
