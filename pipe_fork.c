/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/18 15:48:12 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
