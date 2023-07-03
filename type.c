/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:20:13 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/24 10:59:08 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(t_list *temp)
{
	t_type	*content;

	content = (t_type *) temp->content;
	if (!ft_strncmp(content->txt, "<<", 2) && ft_strlen(content->txt) == 2)
	{
		content->dc_g = 1;
	}
	else if (!ft_strncmp(content->txt, ">>", 2) && ft_strlen(content->txt) == 2)
		content->dc_d = 1;
	else if (!ft_strncmp(content->txt, "<", 1) && ft_strlen(content->txt) == 1)
		content->c_g = 1;
	else if (!ft_strncmp(content->txt, ">", 1) && ft_strlen(content->txt) == 1)
		content->c_d = 1;
	else if (!ft_strncmp(content->txt, "|", 1) && ft_strlen(content->txt) == 1)
		content->pipe = 1;
	else
		return (0);
	return (1);
}

void	ft_is_command(t_list **temp)
{
	t_type	*content;

	content = (t_type *)(*temp)->content;
	if (!(*temp))
		return ;
	content->cmd = 1;
	*temp = (*temp)->next;
	while (*temp && ft_is_redir(*temp) == 0)
	{
		printf("aaaa\n");
		content = (t_type *)(*temp)->content;
		content->arg = 1;
		*temp = (*temp)->next;
	}
}

int	ft_treat_redir_after(t_list **temp)
{
	t_type	*content;

	content = (t_type *)(*temp)->content;
	if (content->c_g == 1)
	{	
		*temp = (*temp)->next;
		if (!(*temp))
			return (-1);
		content = (t_type *)(*temp)->content;
		content->infile = 1;
		return (1);
	}
	if (content->c_d == 1)
	{	
		(*temp) = (*temp)->next;
		if (!(*temp))
		{
			return (-1);
		}
		content = (t_type *)(*temp)->content;
		content->outfile = 1;
		return (1);
	}
	return (0);
}

int	ft_treat_dredir_after(t_list **temp)
{
	t_type	*content;

	content = (t_type *)(*temp)->content;
	if (content->dc_g == 1)
	{	
		(*temp) = (*temp)->next;
		if (!(*temp))
			return (-1);
		content = (t_type *)(*temp)->content;
		content->infile = 2;
		return (1);
	}
	if (content->dc_d == 1)
	{	
		(*temp) = (*temp)->next;
		if (!(*temp))
			return (-1);
		content = (t_type *)(*temp)->content;
		content->outfile = 2;
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
	t_type	*content;

	temp = *l;
	while (temp)
	{
		ft_is_redir(temp);
		printf("txt: %s\n", content->txt);
		content = (t_type *)temp->content;
		simple = ft_treat_redir_after(&temp);
		if (simple == -1)
			break ;
		twice = ft_treat_dredir_after(&temp);
		if (twice == -1)
			break ;
		content = (t_type *)temp->content;
		if (simple == 0 && twice == 0 && content->pipe == 0)
			ft_is_command(&temp);
		else
			temp = temp->next;
	}
}
