/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:00:45 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 13:38:04 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_flags_execve(t_block *b_c)
{
	char	**flags;
	int		j;

	j = 0;
	while (b_c->arg[j] != NULL)
		j++;
	flags = malloc(sizeof(char *) * (j + 2));
	flags[0] = ft_envp(g_data.env_copy, "PWD=");
	flags[j + 1] = NULL;
	while (j > 0)
	{
		flags[j] = malloc(sizeof(char) * (1 + ft_strlen(b_c->arg[j - 1])));
		if (!flags[j])
			return (NULL);
		ft_strlcpy(flags[j], b_c->arg[j - 1], ft_strlen(b_c->arg[j - 1]) + 1);
		j--;
	}
	return (flags);
}
