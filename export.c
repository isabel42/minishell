/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:27 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/30 12:00:17 by ktomat           ###   ########.fr       */
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

void	add_new_var(char *flags, char **env_copy)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (ft_strncmp(env_copy[i], "_=", 2))
		i++;
	temp = ft_strdup(env_copy[i]);
	free(env_copy[i]);
	env_copy[i] = ft_strdup(flags);
	i++;
	env_copy[i] = ft_strdup(temp);
	free(temp);
}

void	ft_export(char *cmd, char **flags, char **env_copy)
{
	int	i;

	(void)cmd;
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
		while (flags[i])
		{
			if (is_equal_sign(flags[i]) == 1)
			{
				add_new_var(flags[i], env_copy);
			}
			i++;
		}
	}
}
