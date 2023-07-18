/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:44:18 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/18 15:45:31 by ktomat           ###   ########.fr       */
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

void	ft_env(char **flags)
{
	int	i;

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

void	ft_cd(char **flags)
{
	char	current_path[4096];
	char	old_path[4096];
	int		i;

	i = 0;
	getcwd(old_path, 4096);
	if (!flags[0])
		chdir(find_home());
	else
		chdir(flags[0]);
	getcwd(current_path, 4096);
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
