/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:47 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/07 15:38:29 by ktomat           ###   ########.fr       */
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

void	check_builtin(char *cmd, char **flags)
{
	if (cmd == NULL)
		return ;
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
}

void	ft_echo(char *cmd, char **flags) //je penses qu'il faudra ajouter le $? pour afficher le dernier status
{
	int	i;

	(void)cmd;
	if (!flags[0])
		printf("\n");
	else if (flags[0][0] == '-' && flags[0][1] == 'n' && flags[0][2] == '\0')
	{
		i = 1;
		while (flags[i])
		{
			printf("%s", flags[i]);
			i++;
		}
		return ;
	}
	else
	{
		i = 0;
		while (flags[i])
		{
			printf("%s", flags[i]);
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

void	ft_exit(char *cmd, char **flags)
{
	(void)flags;
	(void)cmd;
	if (flags[1])
		printf("exit\nminishell: exit: too many arguments\n");
	else if (flags[0])
	{
		if (is_digit1(flags[0]) == -1)
		{
			printf("exit\nminishell: exit:");
			printf(" %s: numeric argument required\n", flags[0]);
			exit(255);
		}
		exit(ft_atoi(flags[0]));
	}
	else
		exit(0);
}
