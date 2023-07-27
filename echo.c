/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:47 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/27 13:27:25 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_flag(t_param *param)
{
	int	i;

	i = 2;
	while (param->flags[i])
	{
		if (i != 2)
			ft_putstr_fd(" ", param->fd_out);
		ft_putstr_fd(param->flags[i], param->fd_out);
		i++;
	}
}

void	echo_normal(t_param *param)
{
	int	i;

	i = 1;
	while (param->flags[i])
	{
		if (i != 1)
			ft_putstr_fd(" ", param->fd_out);
		ft_putstr_fd(param->flags[i], param->fd_out);
		i++;
	}
	if (param->flags[1])
		ft_putstr_fd("\n", param->fd_out);
}

void	ft_echo(t_param *param)
{
	if (!param->flags[1])
		ft_putstr_fd("\n", param->fd_out);
	else if (param->flags[1][0] == '-' && param->flags[1][1] == 'n'
		&& param->flags[1][2] == '\0')
		echo_flag(param);
	else
		echo_normal(param);
}
