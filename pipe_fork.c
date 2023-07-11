/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/11 15:47:14 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	**ft_pipe(int lst_size)
{
	int		**p1;
	int		i;

	i = 0;
	if (lst_size == 1)
	{
		p1 = malloc(sizeof(p1) * 1);
		if (!p1)
			exit(0);
	}
	else
	{
		p1 = malloc(sizeof(p1) * (lst_size - 1));
		if (!p1)
			exit(0);
	}
	while (i < (lst_size - 1) || i == 0)
	{
		p1[i] = malloc(sizeof(p1) * 2);
		if (pipe(p1[i]) == -1)
			exit (1);
		i++;
	}
	return (p1);
}

void	ft_closepipe(int **p1, int lst_size)
{
	int	i;

	i = 0;
	while (i < (lst_size - 1) || i == 0)
	{
		close(p1[i][0]);
		close(p1[i][1]);
		i++;
	}
}

void	ft_waitpid(int *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

int	ft_pipe_in(char **param, int **p1, int i)
{
	int	a;

	printf("para")

	if (param[1] != NULL && param[0] != NULL)
	{
		a = open (param[1], O_RDONLY | O_CLOEXEC);
		if (a < 0)
		{
			perror(NULL);
			a = p1[i - 1][0];
		}
	}
	else if (param[4] != NULL)
	{
		a = 0;
		// ft_putstr_fd(param[4],1);
	}
	else if (i > 0)
		a = p1[i - 1][0];
	else
		a = 0;
	return (a);
}

int	ft_pipe_out(char **param, int **p1, int i)
{
	int	b;

	if (param[2] != NULL)
		b = open (param[2], O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00644);
	else if (i < ft_atoi(param[3]) - 1)
		b = p1[i][1];
	else
		b = 1;
	return (b);
}

void	ft_fork(char **param, int **p1, char **flags, int i)
{
	int		a;
	int		b;

	a = ft_pipe_in(param, p1, i);
	b = ft_pipe_out(param, p1, i);
	dup2(a, STDIN_FILENO);
	dup2(b, STDOUT_FILENO);
	close (a);
	ft_closepipe(p1, ft_atoi(param[3]));
	execve(param[0], flags, NULL);
}
