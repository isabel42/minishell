/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:53:37 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/24 14:36:43 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_nl_charchar(char **tab, char *txt)
{
	char	**sol;
	int		j;

	j = 0;
	while (tab[j] != NULL)
		j++;
	sol = malloc(sizeof(char *) * (j + 2));
	if (!sol)
		return (NULL);
	sol[j] = malloc (sizeof(char) * (ft_strlen(txt) + 1));
	if (!sol[j])
		return (0);
	ft_strlcpy(sol[j], txt, ft_strlen(txt) + 1);
	sol[j + 1] = NULL;
	j--;
	while (j >= 0)
	{
		sol[j] = malloc (sizeof(char) * (ft_strlen(tab[j]) + 1));
		if (!sol[j])
			return (0);
		ft_strlcpy(sol[j], tab[j], ft_strlen(tab[j]) + 1);
		j--;
	}
	ft_free_cc_c(tab, txt);
	return (sol);
}

void	ft_cd_util(char *current_path, char *old_path)
{
	int	i;

	i = 0;
	while (g_data.env_copy[i])
	{
		if (!ft_strncmp(g_data.env_copy[i], "OLDPWD=", 7))
		{
			free(g_data.env_copy[i]);
			free(g_data.env_copy[i - 1]);
			g_data.env_copy[i] = ft_strdup(ft_strjoin("OLDPWD=", old_path));
			g_data.env_copy[i - 1] = ft_strdup
				(ft_strjoin("PWD=", current_path));
		}
		i++;
	}
}
