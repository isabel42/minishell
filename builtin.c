/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:47 by ktomat            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/19 13:04:05 by itovar-n         ###   ########.fr       */
=======
/*   Updated: 2023/07/19 13:35:12 by ktomat           ###   ########.fr       */
>>>>>>> kimi
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

<<<<<<< HEAD

int	ft_check_ifbuiltin(char *cmd)
{
	char	*builtin[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int		i;
	// char	*cmd;
	size_t	len;

	// if (param->cmd == NULL)
	// 	return (-1);
	// i = ft_strlen(param->cmd);
	// while (i >= 0 && param->cmd[i] != '/')
	// 	i--;
	// cmd = param->cmd + i + 1;
	i = 0;
	while (i < 7)
	{
		len = ft_strlen(builtin[i]);
		if (!ft_strncmp(all_lower(cmd), builtin[i], len) && ft_strlen(cmd) == len)
			return (i);
		i++;
	}
	return (-1);
}

int	check_builtin(char *param0, char **flags)
{
	int		i;
	char	*cmd;

	if (param0 == NULL)
		return (1);
	i = ft_strlen(param0);
	while (i >= 0 && param0[i] != '/')
		i--;
	cmd = param0 + i + 1;
	if (!ft_strncmp(all_lower(cmd), "echo", 4) && ft_strlen(cmd) == 4)
		ft_echo(cmd, flags);
	else if (!ft_strncmp(all_lower(cmd), "cd", 2) && ft_strlen(cmd) == 2)
		ft_cd(flags);
	else if (!ft_strncmp(all_lower(cmd), "pwd", 3) && ft_strlen(cmd) == 3)
		ft_pwd(cmd, flags);
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		ft_export(cmd, flags);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		ft_unset(cmd, flags);
	else if (!ft_strncmp(all_lower(cmd), "env", 3) && ft_strlen(cmd) == 3)
		ft_env(flags);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		ft_exit(cmd, flags);
	else
		return (-1);
	return (0);
}

void	ft_echo(char *cmd, char **flags)
=======
void	ft_echo(t_param *param)
>>>>>>> kimi
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
