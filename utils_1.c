/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:53:37 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/27 09:42:42 by itovar-n         ###   ########.fr       */
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

void	ft_cd_util_cp(char *path, int i, char *prefix)
{
	char	*join;

	free(g_data.env_copy[i]);
	join = ft_strjoin(prefix, path);
	g_data.env_copy[i] = malloc(sizeof(char) * (ft_strlen(join) + 1));
	if (!g_data.env_copy[i])
		return ;
	ft_strlcpy(g_data.env_copy[i], join, ft_strlen(join) + 1);
	free(join);
}

void	ft_cd_util(char *current_path, char *old_path)
{
	int		i;

	i = 0;
	while (g_data.env_copy[i])
	{
		if (!ft_strncmp(g_data.env_copy[i], "OLDPWD=", 7))
		{
			ft_cd_util_cp(old_path, i, "OLDPWD=");
			ft_cd_util_cp(current_path, i - 1, "PWD=");
			break ;
		}
		i++;
	}
}
