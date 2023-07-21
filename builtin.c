/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:47 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/21 12:33:27 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_param *param)
{
	int	i;

	if (!param->flags[1])
		ft_putstr_fd("\n", param->fd_out);
	else if (param->flags[1][0] == '-' && param->flags[1][1] == 'n'
		&& param->flags[1][2] == '\0')
	{
		i = 2;
		while (param->flags[i])
		{
			if (i != 2)
				ft_putstr_fd(" ", param->fd_out);
			ft_putstr_fd(param->flags[i++], param->fd_out);
		}
	}
	else
	{
		i = 1;
		while (param->flags[i])
		{
			if (i != 1)
				ft_putstr_fd(" ", param->fd_out);
			ft_putstr_fd(param->flags[i++], param->fd_out);
		}
		if (param->flags[1])
			ft_putstr_fd("\n", param->fd_out);
	}
}

int	is_digit1(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_exit(t_param *param)
{
	if (param->flags[2] && param->flags[1])
	{
		if (param->lst_size == 1)
			printf("exit\n");
		if (is_digit1(param->flags[1]) == -1)
			printf("minishell: exit: %s: numeric argument required\n", param->flags[1]);
		else
			printf("minishell: exit: too many arguments\n");
		if (param->lst_size == 1 && is_digit1(param->flags[1]) == -1)
			exit(255);
		else if (param->lst_size == 1)
			return ;
	}
	else if (param->flags[1])
	{
		if (param->lst_size == 1)
			printf("exit\n");
		if (is_digit1(param->flags[1]) == -1)
			printf("minishell: exit: %s: numeric argument required\n", param->flags[1]);
		if (param->lst_size == 1)
		{
			if (is_digit1(param->flags[1]) == -1)
				exit (255);
			else
				exit(ft_atoi(param->flags[1]));
		}
	}
	else
		exit(0);
}
