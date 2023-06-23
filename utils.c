/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/23 13:43:16 by itovar-n         ###   ########.fr       */
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

void	ft_is_command(t_list **temp)
{
	if (!(*temp))
		return ;
	(*temp)->cmd = 1;
	*temp = (*temp)->next;
	while (*temp && ft_is_redir(*temp) == 0)
	{
		(*temp)->arg = 1;	
		*temp = (*temp)->next;
	}
}

int	ft_treat_redir_after(t_list **temp)
{
	if ((*temp)->c_g == 1)
	{	
		*temp = (*temp)->next;
		if(!(*temp))
			return (-1);
		(*temp)->infile = 1;
		return (1);
	}
	if ((*temp)->c_d == 1)
	{	
		(*temp) = (*temp)->next;
		if(!(*temp))
			return (-1);
		(*temp)->outfile = 1;
		return (1);
	}
	return (0);
}

int	ft_treat_dredir_after(t_list **temp)
{
	if ((*temp)->dc_g == 1)
	{	
		(*temp) = (*temp)->next;
		if(!(*temp))
			return (-1);
		(*temp)->infile_d = 1;
		return (1);
	}
	if ((*temp)->dc_d == 1)
	{	
		(*temp) = (*temp)->next;
		if(!(*temp))
			return (-1);
		(*temp)->outfile_d = 1;
		return (1);
	}
	return (0);
}


//permet de donner un type a chaque maillon de la liste chainee
void	ft_find_type(t_list **l)
{
	t_list	*temp;
	int		simple;
	int		twice;

	temp = *l;
	while (temp)
	{
		ft_is_redir(temp);
		simple = ft_treat_redir_after(&temp);
		twice = ft_treat_dredir_after(&temp);
		printf("txg: %s, simple : %d , twice: %d\n", temp->txt, simple, twice);
		if (simple == -1 || twice == -1)
			break ;
		if (simple == 0 && twice == 0 && temp->pipe == 0)
			ft_is_command(&temp);
		if (!temp)
			break ;
		temp = temp->next;

		
		// if (temp->c_g == 1)
		// {	
		// 	temp = temp->next;
		// 	if(!temp)
		// 		break ;
		// 	temp->infile = 1;
		// }
		// else if (temp->c_d == 1)
		// {	
		// 	temp = temp->next;
		// 	if(!temp)
		// 		break ;
		// 	temp->outfile = 1;
		// }
		// else if (temp->dc_g == 1)
		// {	
		// 	temp = temp->next;
		// 	if(!temp)
		// 		break ;
		// 	temp->infile_d = 1;
		// }
		// else if (temp->dc_d == 1)
		// {	
		// 	temp = temp->next;
		// 	if(!temp)
		// 		break ;
		// 	temp->outfile_d = 1;
		// }
		// else if (temp->pipe == 0)
		// 	ft_is_command(temp);
		// if (!temp)
		// 	break ;
		// temp = temp->next;
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
