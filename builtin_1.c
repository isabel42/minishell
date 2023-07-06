/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:44:18 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/06 11:23:12 by ktomat           ###   ########.fr       */
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

int	env_copy1(char **env)
{
	int		i;

	i = 0;
	g_data.env_copy = ft_calloc(sizeof(char **), 1000);
	if (!g_data.env_copy)
		return (-1);
	while (env[i])
	{
		if (env[i + 1] == NULL)
			break ;
		g_data.env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	return (0);
}

void	ft_env(char *cmd, char **flags)
{
	int	i;

	(void)cmd;
	i = 0;
	if (flags[0])
		printf("env: %s: No such file or directory", flags[0]);
	else
	{
		while (g_data.env_copy[i])
		{
			printf("%s\n", g_data.env_copy[i]);
			i++;
		}
	}
}

void	ft_pwd(char *cmd, char **flags)
{
	char	cwd[4096];

	(void)cmd;
	(void)flags;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("salut");
}	

//checker comment je vais verifier avec la gestion d'erreure finale et print si le file n'existe pas
void	ft_cd(char *cmd, char **flags)
{
	(void)cmd;
	if (!flags[0])
		return ;
	else
	{
		chdir(flags[0]);
	}
}
