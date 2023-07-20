/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:19:45 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/19 18:45:29 by itovar-n         ###   ########.fr       */
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

void	ft_perror_comm(char *command, char *infile)
{
	int	a;

	if (infile != NULL)
	{
		a = open (infile, O_RDONLY | O_CLOEXEC);
		if (a >= 0)
		{
			ft_putstr_fd("Command not found: ", 1);
			if (command)
				ft_putstr_fd(command, 1);
			ft_putstr_fd("\n", 1);
		}
		else
			ft_putstr_fd("No such file or directory\n", 1);
		close (a);
	}
	else if (check_builtin(command) == -1 && command != NULL)
	{
		ft_putstr_fd("Command not found: ", 1);
		if (command)
			ft_putstr_fd(command, 1);
		ft_putstr_fd("\n", 1);
	}
}

char	*ft_find_path(char *path, char *command, char *infile)
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
	ft_perror_comm(command, infile);
	if (command != NULL)
		command = ft_strjoin(command, "\0");
	return (command);
}
