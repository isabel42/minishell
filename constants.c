/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:19:45 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 09:57:31 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_pwd(char *pwd, char *infile)
{
	char	*pwd_infile;

	infile = ft_strjoin("/", infile);
	pwd_infile = ft_strjoin(pwd, infile);
	free(infile);
	return (pwd_infile);
}

void	ft_cmd_nf(char *command)
{
	ft_putstr_fd("minishell: ", 1);
	if (command)
		ft_putstr_fd(command, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_data.status = 127;
}

void	ft_perror_comm(char *command, char *infile)
{
	int	a;
	int	i;

	if (infile != NULL)
	{
		a = open (infile, O_RDONLY | O_CLOEXEC);
		if (a >= 0)
		{
			if (command)
				ft_cmd_nf(command);
		}
		else
		{
			i = ft_strlen(infile) - 1;
			while (infile[i] != '/')
				i--;
			printf("minishell: %s: ", infile + i + 1);
			printf("no such a file or directory\n");
			g_data.status = 1;
		}
		close (a);
	}
	else if (check_builtin(command) == -1
		&& command != NULL && access(command, X_OK) != 0)
		ft_cmd_nf(command);
}

char	*ft_find_path_comm(char *path, char *command)
{
	char	**path_split;
	char	*path_command;
	char	*slash_command;
	int		i;

	i = 0;
	if (path == NULL)
		return (NULL);
	slash_command = ft_strjoin("/", command);
	path_split = ft_split(path, ':');
	while (path_split != NULL && path_split[i])
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
	ft_free_cc(path_split);
	free(slash_command);
	return (NULL);
}

char	*ft_find_path(char *path, char *command, char *infile)
{
	char	*path_command;

	if (command)
	{
		path_command = ft_find_path_comm(path, command);
		if (path_command != NULL)
			return (path_command);
	}
	ft_perror_comm(command, infile);
	if (command != NULL)
		command = ft_strjoin(command, "\0");
	return (command);
}
