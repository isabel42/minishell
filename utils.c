/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/17 15:23:20 by itovar-n         ###   ########.fr       */
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

void	ft_exit_isa(char *s)
{
	printf("%s\n", s);
	exit(0);
}

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
