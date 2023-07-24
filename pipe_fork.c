/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/24 14:56:16 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_new_pid(int *pid)
{
	int	i;
	int	size;
	int	*new_pid;

	size = 0;
	if (pid == NULL)
	{
		new_pid = malloc(sizeof(int));
		if (!new_pid)
			return (0);
		return (new_pid);
	}
	while (pid[size])
		size++;
	new_pid = malloc(sizeof(int) * (size + 1));
	if (!new_pid)
		return (0);
	i = 0;
	while (i < size)
	{
		new_pid[i] = pid[i];
		i++;
	}
	free(pid);
	return (new_pid);
}

void	ft_fork(t_param *param, int **p1, int *pid)
{
	int	i;
	int	pid_parent;

	i = 0;
	pid_parent = getpid();
	while (pid[i + 1])
		i++;
	pid[i] = fork();
	if (pid[i] == 0)
	{
		dup2(param->fd_in, STDIN_FILENO);
		dup2(param->fd_out, STDOUT_FILENO);
		if (param->infile != NULL)
			close (param->fd_in);
		if (param->outfile != NULL)
			close (param->fd_out);
		ft_closepipe(p1, param->lst_size);
		execve(param->cmd, param->flags, NULL);
		kill(pid_parent, SIGUSR1);
		exit(0);
	}
}
