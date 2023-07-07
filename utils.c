/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/07 11:01:01 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(void)
{
	int		i;
	char	**result;

	i = 0;
	while (g_data.env_copy[i])
	{
		if (!ft_strncmp("HOME=", g_data.env_copy[i], 5))
		{
			result = ft_split(g_data.env_copy[i], '=');
			if (result[1])
				free(result[1]);
			return (result[1]);
		}
		i++;
	}
	return (NULL);
}

int	count_list(t_list **list)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], pwd, ft_strlen(pwd)) == 0)
			return (envp[i] + ft_strlen(pwd));
		i++;
	}
	return (NULL);
}

