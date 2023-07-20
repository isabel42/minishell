/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/19 16:22:45 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork(t_param *param, int **p1)
{
	dup2(param->fd_in, STDIN_FILENO);
	dup2(param->fd_out, STDOUT_FILENO);
	if(param->fd_in > 2)
		close (param->fd_in);
	// if(param->fd_out > 1)
	// 	close (param->fd_out);
	ft_closepipe(p1, param->lst_size);
	execve(param->cmd, param->flags, NULL);
	exit(0);
}
