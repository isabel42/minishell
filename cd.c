/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:46:08 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 11:46:15 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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

void	ft_cd(t_param *param)
{
	char	current_path[4096];
	char	old_path[4096];
	char	*home;

	getcwd(old_path, 4096);
	if (!param->flags[1])
	{
		home = find_home();
		if (chdir(home) != 0)
		{
			printf("Minishell: cd: HOME not set\n");
			g_data.status = 1;
		}
		free(home);
	}
	else
	{
		if (chdir(param->flags[1]) != 0)
		{
			printf("bash: cd: %s: Not a directory\n", param->flags[1]);
			g_data.status = 1;
		}
	}	
	getcwd(current_path, 4096);
	ft_cd_util(current_path, old_path);
}
