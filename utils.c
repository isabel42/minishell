/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/21 18:12:17 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_redir(t_list *temp)
{
	if (!ft_strncmp(temp->txt, "<<", 2) && ft_strlen(temp->txt) == 2)
		temp->dc_g = 1;
	else if (!ft_strncmp(temp->txt, ">>", 2) && ft_strlen(temp->txt) == 2)
		temp->dc_d = 1;
	else if (!ft_strncmp(temp->txt, "<", 1) && ft_strlen(temp->txt) == 1)
		temp->c_g = 1;
	else if (!ft_strncmp(temp->txt, ">", 1) && ft_strlen(temp->txt) == 1)
		temp->c_d = 1;
	else if (!ft_strncmp(temp->txt, "|", 1) && ft_strlen(temp->txt) == 1)
		temp->pipe = 1;
}



//permet de donner un type a chaque maillon de la liste chainee
void	ft_find_type(t_list **l, char **envp)
{
	t_list	*temp;

	temp = *l;
	while (temp)
	{
		ft_is_redir(temp);
		if (temp->dc_g + temp->dc_d + temp->c_g + temp->c_d == 1)
		{
			temp = temp->next;
			if(!temp)
				break;
			temp->file = 1;
		}
		else if (ft_find_comm_path(ft_envp(envp, "PATH="), temp->txt))
		{
			temp->cmd = 1;
			temp = temp->next;
			if(!temp)
				break;
			temp->arg = 1;
		}
		else
			temp->arg = 1;
		temp = temp->next;
	}
}

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
