/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:47 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/23 15:25:43 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//toutes les entree seront changee en minuscule et la comparaison se fera en minuscule
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

// le echo avec -N affiche -N et le message
void	check_builtin(char *cmd, char **flags)
{
	if (!ft_strncmp(all_lower(cmd), "echo", 4) && ft_strlen(cmd) == 4)
		ft_echo(cmd, flags);
	if (!ft_strncmp(all_lower(cmd), "cd", 2) && ft_strlen(cmd) == 2)
	if (!ft_strncmp(all_lower(cmd), "pwd", 3) && ft_strlen(cmd) == 3)
	if (!ft_strncmp(all_lower(cmd), "export", 6) && ft_strlen(cmd) == 6)
	if (!ft_strncmp(all_lower(cmd), "unset", 5) && ft_strlen(cmd) == 5)
	if (!ft_strncmp(all_lower(cmd), "env", 3) && ft_strlen(cmd) == 3)
	if (!ft_strncmp(all_lower(cmd), "exit", 4) && ft_strlen(cmd) == 4)
}

void	ft_echo(char *cmd, char **flags)
{
	if ()
}
