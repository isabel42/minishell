/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/27 09:43:41 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_index_envp(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
	}
	return (i);
}

char	*find_home(void)
{
	int		i;
	char	**result;
	char	*res;

	i = 0;
	while (g_data.env_copy[i])
	{
		if (!ft_strncmp("HOME=", g_data.env_copy[i], 5))
		{
			result = ft_split(g_data.env_copy[i], '=');
			res = malloc(sizeof(char) * (ft_strlen(result[1]) + 1));
			if (!res)
				return (NULL);
			ft_strlcpy(res, result[1], ft_strlen(result[1]) + 1);
			if (result[1])
				free(result[1]);
			free(result[0]);
			free(result);
			return (res);
		}
		i++;
	}
	return (NULL);
}

char	*ft_getpath(char **envp, char *prog)
{
	char	**env;
	char	*path;
	char	*new_path;
	char	*temp;
	int		i;

	path = NULL;
	i = find_index_envp(envp);
	env = ft_split(envp[i] + 5, ':');
	i = -1;
	while (env[++i])
	{
		temp = ft_strjoin(env[i], "/");
		new_path = ft_strjoin(temp, prog);
		free(temp);
		if (access(new_path, X_OK | F_OK) == 0)
		{
			path = new_path;
			break ;
		}
		else
			free(new_path);
	}
	return (path);
}

// Pour trouver la variable dans l'env
char	*ft_envp(char **envp, char *pwd)
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
