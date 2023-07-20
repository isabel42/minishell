/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:47:40 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/19 17:18:26 by itovar-n         ###   ########.fr       */
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

int	ft_pipe_in(t_param *param, int **p1, int i)
{
	int	a;

	if (param->infile != NULL && param->cmd != NULL)
	{
		a = open (param->infile, O_RDONLY | O_CLOEXEC);
		if (a < 0)
		{
			perror(NULL);
			a = p1[i - 1][0];
		}
	}
	else if (param->heredoc != NULL)
		a = ft_fd_heredoc(param->heredoc);
	else if (i > 0)
		a = p1[i - 1][0];
	else
		a = 0;
	return (a);
}

int	ft_pipe_out(t_param *param, int **p1, int i)
{
	int	b;

	if (param->outfile != NULL)
	{
		if (param->chev_out[0] == '1')
			b = open (param->outfile, O_TRUNC
					| O_CREAT | O_WRONLY | O_CLOEXEC, 00644);
		else
			b = open (param->outfile, O_APPEND
					| O_CREAT | O_WRONLY | O_CLOEXEC, 00644);
	}
	else if (i < param->lst_size - 1)
		b = p1[i][1];
	else
		b = 1;
	return (b);
}
