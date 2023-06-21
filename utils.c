/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/21 15:22:28 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(char *txt)
{
	char	*redir;
	char	**redir_split;
	int		i;
	
	redir = "<<,<,>,>>";
	redir_split = ft_split(redir,',');
	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(redir_split[i],txt,2) == 0)
		{
			free(redir_split);
			return (1);
		}
	}
	free(redir_split);
	return (0);
}



//permet de donner un type a chaque maillon de la liste chainee
void	ft_find_type(t_list **list, char **envp)
{
	// t_list	*list;

	// list = *temp;
	while (*list)
	{
		if (ft_find_comm_path(ft_envp(envp, "PATH="), (*list)->txt))
			(*list)->cmd = 1;
		else if (ft_is_redir((*list)->txt) == 1)
		{
			(*list)->redir = 1;
			if ((*list)->next)
			{
				(*list)->next->file = 1;
				*list = (*list)->next;
				if (!*list)
					break ;
			}
		}
		else
			(*list)->arg = 1;
		*list = (*list)->next;
	}
	// *temp = list;
}
