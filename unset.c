/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:16:16 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/19 12:43:10 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var(int i)
{
	int		t;

	free(g_data.env_copy[i]);
	g_data.env_copy[i] = NULL;
	t = i;
	i++;
	while (g_data.env_copy[i])
	{
		g_data.env_copy[t] = ft_strdup(g_data.env_copy[i]);
		free(g_data.env_copy[i]);
		g_data.env_copy[i] = NULL;
		t++;
		i++;
	}
}

void	ft_unset(t_param *param)
{
	int	i;
	int	j;

	i = 0;
	while (param->flags[i])
	{
		j = 0;
		while (g_data.env_copy[j])
		{
			if (!ft_strncmp(g_data.env_copy[j], param->flags[i],
					ft_strlen(param->flags[i])))
			{
				unset_var(j);
				break ;
			}
			j++;
		}
		i++;
	}
}
