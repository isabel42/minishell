/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:28:34 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/19 13:36:27 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_param *param)
{
	int		i;
	char	*cmd;

	if (param->cmd == NULL)
		return (-1);
	i = ft_strlen(param->cmd);
	while (i >= 0 && param->cmd[i] != '/')
		i--;
	cmd = param->cmd + i + 1;
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
	int	result;
	int	(*ptr_ft[7])(t_param);

	nb = check_builtin(param);
	if (nb == -1)
		return (-1);
	ptr_ft[0] = &ft_echo;
	ptr_ft[1] = &ft_cd;
	ptr_ft[2] = &ft_pwd;
	ptr_ft[3] = &ft_export;
	ptr_ft[4] = &ft_unset;
	ptr_ft[5] = &ft_env;
	ptr_ft[6] = &ft_exit;
	result = ptr_ft[nb](param);
	return (result);
}
