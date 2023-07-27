/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_inputs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:28:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 12:29:00 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_txt_redir(char *txt)
{
	if (!ft_strncmp(txt, "<<", 2) && ft_strlen(txt) == 2)
		return (5);
	if (!ft_strncmp(txt, ">>", 2) && ft_strlen(txt) == 2)
		return (4);
	if (!ft_strncmp(txt, "<", 1) && ft_strlen(txt) == 1)
		return (3);
	if (!ft_strncmp(txt, ">", 1) && ft_strlen(txt) == 1)
		return (2);
	if (!ft_strncmp(txt, "|", 1) && ft_strlen(txt) == 1)
		return (1);
	return (0);
}

int	ft_check_inputs(t_list **inputs)
{
	t_list	*list;
	t_list	*list_next;
	t_type	*content;
	t_type	*cont_next;

	list = *inputs;
	while (list)
	{
		content = (t_type *)list->content;
		if (ft_txt_redir(content->txt) > 1 && !list->next)
			return (0);
		list_next = list->next;
		if (list_next)
		{
			cont_next = (t_type *)list_next->content;
			if (ft_txt_redir(content->txt) == 1
				&& ft_txt_redir(cont_next->txt) == 1)
				return (0);
			if (ft_txt_redir(content->txt) > 1
				&& ft_txt_redir(cont_next->txt) > 1)
				return (0);
		}
		list = list->next;
	}
	return (1);
}
