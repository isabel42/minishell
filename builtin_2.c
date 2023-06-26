/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:27 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/26 15:21:40 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum1(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	is_equal_sign(char *str)
{
	int	i;
	int	b;
	int	a;

	i = 0;
	b = 0;
	a = 0;
	if (str[0] == '=')
		return (0);
	while (str[i])
	{
		if (str[i] == '=' && ft_isalnum1(str[i - 1]) == 1)
			a = 1;
		if (str[i - 1] == '=' && ) //finir le checker pour les arguments apres le '='
		i++;
	}
	return (0);
}

void	ft_export(char *cmd, char **flags, char **env_copy)
{
	int	i;

	i = 0;
	if (!flags[0])
	{
		while (env_copy[i])
		{
			printf("declare -x %s\n", env_copy[i]);
			i++;
		}
	}
	else if (flags[0])
	{
		if () // trouver comment ajouter une ligne en plus dans le env_copy
	}
}
