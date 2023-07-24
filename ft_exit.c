/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:32:18 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/21 13:40:42 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exit_param_flag_1(t_param *param)
{
	if (param->lst_size == 1)
		printf("exit\n");
	if (is_digit1(param->flags[1]) == -1)
	{
		printf("minishell: exit: %s", param->flags[1]);
		printf(":numeric argument required\n");
	}
	if (param->lst_size == 1)
	{
		if (is_digit1(param->flags[1]) == -1)
			exit (255);
		else
			exit(ft_atoi(param->flags[1]));
	}
}

int	exit_param_flag_2(t_param *param)
{
	if (param->lst_size == 1)
		printf("exit\n");
	if (is_digit1(param->flags[1]) == -1)
	{
		printf("minishell: exit: %s", param->flags[1]);
		printf(":numeric argument required\n");
	}
	else
		printf("minishell: exit: too many arguments\n");
	if (param->lst_size == 1 && is_digit1(param->flags[1]) == -1)
		exit(255);
	else if (param->lst_size == 1)
		return (-1);
	return (0);
}

void	ft_exit(t_param *param)
{
	if (param->flags[2] && param->flags[1])
	{
		if (exit_param_flag_2(param) == -1)
			return ;
	}
	else if (param->flags[1])
		exit_param_flag_1(param);
	else
		exit(0);
}
