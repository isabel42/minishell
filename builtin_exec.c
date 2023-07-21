/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:28:34 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/21 12:31:05 by ktomat           ###   ########.fr       */
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

int	check_builtin(char *cmd_long)
{
	int		i;
	char	*cmd;

	if (cmd_long == NULL)
		return (-1);
	i = ft_strlen(cmd_long);
	while (i > 0 && cmd_long[i] != '/')
		i--;
	if (i == 0)
		cmd = cmd_long;
	else
		cmd = cmd_long + i + 1;
	if (!ft_strncmp(all_lower(cmd), "echo", 4) && ft_strlen(cmd) == 4)
		return (0);
	else if (!ft_strncmp(all_lower(cmd), "cd", 2) && ft_strlen(cmd) == 2)
		return (1);
	else if (!ft_strncmp(all_lower(cmd), "pwd", 3) && ft_strlen(cmd) == 3)
		return (2);
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		return (3);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		return (4);
	else if (!ft_strncmp(all_lower(cmd), "env", 3) && ft_strlen(cmd) == 3)
		return (5);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		return (6);
	return (-1);
}

int	ft_built_exec(t_param *param)
{
	int	nb;
	// int	result;
	void	(*ptr_ft[7])(t_param *);

	nb = check_builtin(param->cmd);
	if (nb == -1)
		return (-1);
	ptr_ft[0] = &ft_echo;
	ptr_ft[1] = &ft_cd;
	ptr_ft[2] = &ft_pwd;
	ptr_ft[3] = &ft_export;
	ptr_ft[4] = &ft_unset;
	ptr_ft[5] = &ft_env;
	ptr_ft[6] = &ft_exit;
	ptr_ft[nb](param);

	return (1);
}
