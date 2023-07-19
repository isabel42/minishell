/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:47 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/19 13:35:12 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*all_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
		i++;
	}
	return (str);
}

void	ft_echo(t_param *param)
{
	int	i;

	if (!param->flags[0])
		printf("\n");
	else if (param->flags[0][0] == '-' && param->flags[0][1] == 'n'
		&& param->flags[0][2] == '\0')
	{
		i = 1;
		while (param->flags[i])
		{
			printf("%s", param->flags[i]);
			i++;
		}
		return ;
	}
	else
	{
		i = 0;
		while (param->flags[i])
		{
			printf("%s", param->flags[i]);
			i++;
		}
		printf("\n");
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
	if (param->flags[1])
		printf("exit\nminishell: exit: too many arguments\n");
	else if (param->flags[0])
	{
		if (is_digit1(param->flags[0]) == -1)
		{
			printf("exit\nminishell: exit:");
			printf(" %s: numeric argument required\n", param->flags[0]);
			exit(255);
		}
		exit(ft_atoi(param->flags[0]));
	}
	else
		exit(0);
}
