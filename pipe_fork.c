/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/26 16:49:29 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_new_pid(int *pid, int size_pid)
{
	int	i;
	int	*new_pid;

	i = 0;
	new_pid = malloc(sizeof(int) * (size_pid));
	if (!new_pid)
		return (0);
	while (i < size_pid - 1)
	{
		new_pid[i] = pid[i];
		i++;
	}
	free(pid);
	return (new_pid);
}

void	ft_fork(t_param *param, int **p1, int *pid, int size_pid)
{
	int	pid_parent;

	pid_parent = getpid();
	pid[size_pid - 1] = fork();
	if (pid[size_pid - 1] == 0)
	{
		dup2(param->fd_in, STDIN_FILENO);
		dup2(param->fd_out, STDOUT_FILENO);
		if (param->infile != NULL)
			close (param->fd_in);
		if (param->outfile != NULL)
			close (param->fd_out);
		ft_closepipe(p1, param->lst_size);
		execve(param->cmd, param->flags, NULL);
		if (g_data.status == 0)
			kill(pid_parent, SIGUSR1);
		exit(0);
	}
}
