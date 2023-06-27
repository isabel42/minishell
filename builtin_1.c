/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:44:18 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/27 15:12:35 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_list(t_list **list)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = *list;
	while (*list)
	{
		i++;
		*list = (*list)->next;
	}
	*list = temp;
	return (i);
}
//malloc de 1000, comme ca c'est plus simple pour ajouter ou enlever des elem dans la copy
//surement que je vais devoir gerer la derniere ligne manuellement
//_=/User/....

char	**env_copy(char **env)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = ft_calloc(char **, 1000);
	if (!env_copy)
		return (NULL);
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]); //est ce que j'inclus la ligne _=/User ou pas, sinon je l'affiche manuellement a la fin quand env est appele
		i++;
	}
	return (env_copy);
}

void	ft_env(char *cmd, char **flags, char **env_copy)
{
	int	i;

	i = 0;
	if (flags[0])
		printf("env: %s: No such file or directory", flags[0]);
	else
	{
		while (env_copy[i])
		{
			printf("%s\n", env_copy[i]);
			i++;
		}
	}
}

void	ft_pwd(char *cmd, char **flags, char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		if (!ft_strncmp("PWD=", env_copy[i], 4))
		{
			printf("%s\n", env_copy[i]);
			break ;
		}
		i++;
	}
}

void	ft_cd(char *cmd, char **flags, char **env_copy)
{
	
}