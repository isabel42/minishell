/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/22 18:13:10 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(t_list *temp)
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
	else
		return (0);
	return (1);
}

void	ft_is_command(t_list *temp)
{
	if (!temp)
		return ;
	printf("test\n");
	temp->cmd = 1;
	temp = temp->next;
	while (temp && ft_is_redir(temp) == 0)
	{
		temp->arg = 1;	
		temp = temp->next;
	}
}

//permet de donner un type a chaque maillon de la liste chainee
void	ft_find_type(t_list **l)
{
	t_list	*temp;

	temp = *l;
	while (temp)
	{
		ft_is_redir(temp);
		if (temp->c_g == 1)
		{	
			temp = temp->next;
			temp->infile = 1;
		}
		else if (temp->c_d == 1)
		{	
			temp = temp->next;
			temp->outfile = 1;
		}
		else if (temp->dc_g == 1)
		{	
			temp = temp->next;
			temp->infile_d = 1;
		}
		else if (temp->dc_d == 1)
		{	
			temp = temp->next;
			temp->outfile_d = 1;
		}
		else if (temp->pipe == 0)
			ft_is_command(temp);
		if (!temp)
			break ;
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
