/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:27 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/07 14:36:18 by ktomat           ###   ########.fr       */
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

	i = 0;
	while (g_data.env_copy[i])
		i++;
	g_data.env_copy[i] = ft_strdup(flags);
}

void	ft_export(char *cmd, char **flags)
{
	int	i;

	(void)cmd;
	i = 0;
	if (!flags[0])
	{
		while (g_data.env_copy[i])
		{
			printf("declare -x %s\n", g_data.env_copy[i]);
			i++;
		}
	}
	else if (flags[0])
	{
		while (flags[i])
		{
			if (is_equal_sign(flags[i]) == 1)
			{
				add_new_var(flags[i]);
			}
			i++;
		}
	}
}
