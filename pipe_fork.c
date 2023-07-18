/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/18 15:29:08 by ktomat           ###   ########.fr       */
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
			b = open (param->outfile, O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00644);
		else
			b = open (param->outfile, O_APPEND | O_CREAT | O_WRONLY | O_CLOEXEC, 00644);
	}
	else if (i < param->lst_size - 1)
		b = p1[i][1];
	else
		b = 1;
	return (b);
}

// void	ft_exec_fork(int lst_size, t_block *block_content, int i)
// {
// 	char	**param;
// 	char	**flags;
// 	int 	*pid;
// 	int		**p1;

// 	param = ft_param(lst_size, block_content);
// 	flags = ft_flags_execve(block_content);
// 	pid = malloc(sizeof(int) *(lst_size));
// 	p1 = ft_pipe(lst_size);
// 	pid[i] = fork();
// 	if (pid[i] == 0)
// 		ft_fork(param, p1, flags, i);
// 	ft_free_loop(param, flags);
// }

void	ft_fork(t_param *param, int **p1, char **flags, int i)
{
	int	a;
	int	b;

	a = ft_pipe_in(param, p1, i);
	b = ft_pipe_out(param, p1, i);
	dup2(a, STDIN_FILENO);
	dup2(b, STDOUT_FILENO);
	ft_closepipe(p1, param->lst_size);
	if (check_builtin(param->cmd, flags + 1) != 0)
		execve(param->cmd, flags, NULL);
	exit(0);
}
