/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/21 15:15:43 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//permet de donner un type a chaque maillon de la liste chainee
void	ft_find_type(t_list **l, char **envp)
{
	t_list	*temp;

	temp = *l;
	while (*l)
	{
		(*l)->fd = open((*l)->txt, O_RDONLY);
		if (ft_find_comm_path(ft_envp(envp, "PATH="), (*l)->txt))
			(*l)->cmd = 1;
		else if ((*l)->fd > 0)
			(*l)->file = 1;
		else if (!ft_strncmp((*l)->txt, "<<", 2) && ft_strlen((*l)->txt) == 2)
			(*l)->dc_g = 1;
		else if (!ft_strncmp((*l)->txt, ">>", 2) && ft_strlen((*t)->txt) == 2)
			(*list)->dc_d = 1;
		else if (!ft_strncmp((*l)->txt, "<", 1) && ft_strlen((*l)->txt) == 1)
			(*l)->c_g = 1;
		else if (!ft_strncmp((*l)->txt, ">", 1) && ft_strlen((*l)->txt) == 1)
			(*l)->c_d = 1;
		else if (!ft_strncmp((*l)->txt, "|", 1) && ft_strlen((*l)->txt) == 1)
			(*l)->pipe = 1;
		close((*l)->fd);
		*l = (*l)->next;
	}
	*l = temp;
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
