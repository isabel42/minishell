/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:44:18 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/30 12:02:22 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_list1(t_list **list)
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

char	**env_copy1(char **env)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = ft_calloc(sizeof(char **), 1000);
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

	(void)cmd;
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
	char	cwd[4096];

	(void)cmd;
	(void)flags;
	(void)env_copy;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("salut");
}	

//checker comment je vais verifier avec la gestion d'erreure finale
void	ft_cd(char *cmd, char **flags, char **env_copy)
{
	(void)cmd;
	(void)env_copy;
	if (!flags[0])
		printf("args_needed\n");
	else
	{
		chdir(flags[0]);
	}
}
