/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:01:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/16 14:29:28 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

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

char	*ft_find_path(char *path, char *command)
{
	char	**path_split;
	char	*path_command;
	char	*slash_command;
	int		i;

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

char	*ft_param(char *prompt, char **envp)
{
	char	*param;

	param = ft_find_path(ft_envp(envp, "PATH="), prompt);
	return (param);
}


int main (int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*command;
	int		pid;

	// prompt = "test";
		// readline(prompt);
	(void) argc;
	(void) argv;
	while (42)
	{
		prompt = readline("minishell >");
		command = ft_param(prompt, envp);
		pid = fork();
		if (pid == 0)
		{
			printf("%s\n", command);
			execve(command, NULL, NULL);
		}
		waitpid(pid, NULL, 0);

		// i = 0;
		// printf("**%s**\n", prompt);
		// while (prompt[i] != '\0')
		// {
		// 	if (prompt[i] == 'a')
		// 		return(0);
		// 	i++;
		// }
	}
}