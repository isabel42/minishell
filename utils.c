/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/20 15:41:57 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//permet de donner un type a chaque maillon de la liste chainee
void	ft_find_type(t_list **list, char **envp)
{
	t_list	*temp;
	int		fd;

	temp = *list;
	while (*list)
	{
		fd = open((*list)->txt, O_RDONLY);
		if (ft_find_comm_path(ft_envp(envp, "PATH="), (*list)->txt))
			(*list)->cmd = 1;
		else if (fd > 0)
			(*list)->infile = 1;
		else
			(*list)->arg = 1;
		close(fd);
		*list = (*list)->next;
	}
	*list = temp;
}
