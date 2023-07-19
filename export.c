/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:27 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/19 15:35:50 by itovar-n         ###   ########.fr       */
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

	i = 1;
	b = 0;
	a = 0;
	if (str[0] == '=')
		return (0);
	if (!ft_strncmp(str, "_=", 2))
		return (0);
	while (str[i])
	{
		if (str[i] == '=' && ft_isalnum1(str[i - 1]) == 1)
			b = 1;
		if (str[i - 1] == '=' && (str[i] != '<' || str[i] != '>'
				|| str[i] != '|'))
			a = 1;
		i++;
	}
	if (a && b)
		return (1);
	return (0);
}

void	add_new_var(char *flags)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (flags[j] != '=' && flags[j])
		j++;
	while (g_data.env_copy[i])
	{
		if (!ft_strncmp(flags, g_data.env_copy[i], j))
		{
			if (g_data.env_copy[i])
				free(g_data.env_copy[i]);
			break ;
		}
		i++;
	}
	g_data.env_copy[i] = ft_strdup(flags);
}
 
void	ft_export(t_param *param)
{
	int	i;

	i = 0;
	if (!param->flags[0])
	{
		while (g_data.env_copy[i])
		{
			printf("declare -x %s\n", g_data.env_copy[i]);
			i++;
		}
	}
	else if (param->flags[0])
	{
		while (param->flags[i])
		{
			if (is_equal_sign(param->flags[i]) == 1)
			{
				add_new_var(param->flags[i]);
			}
			i++;
		}
	}
}
