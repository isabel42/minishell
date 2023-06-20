/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/20 17:26:21 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//permet de donner un type a chaque maillon de la liste chainee
void	ft_find_type(t_list **list, char **envp)
{
	t_list	*temp;

	temp = *list;
	while (*list)
	{
		(*list)->fd = open((*list)->txt, O_RDONLY);
		if (ft_find_comm_path(ft_envp(envp, "PATH="), (*list)->txt))
			(*list)->cmd = 1;
		else if ((*list)->fd > 0)
			(*list)->file = 1;
		else if (!ft_strncmp((*list)->txt, "<", 1))
			(*list)->c_g = 1;
		else if (!ft_strncmp((*list)->txt, ">", 1))
			(*list)->c_d = 1;
		else if (!ft_strncmp((*list)->txt, "<<", 2))
			(*list)->dc_g = 1;
		else if (!ft_strncmp((*list)->txt, ">>", 2))
			(*list)->dc_d = 1;
		else if (!ft_strncmp((*list)->txt, "|", 1))
			(*list)->pipe = 1;
		close((*list)->fd);
		*list = (*list)->next;
	}
	*list = temp;
}

void	ft_find_type1(t_list **list, char **envp)
{
	t_list	*temp;

	(void)envp;
	temp = *list;
	while (*list)
	{
		if (!ft_strncmp((*list)->txt, "$", 1))
			(*list)->dollar = 1;
		*list = (*list)->next;
	}
	*list = temp;
}

