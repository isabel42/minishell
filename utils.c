/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/03 14:00:28 by ktomat           ###   ########.fr       */
=======
/*   Updated: 2023/07/05 16:18:58 by itovar-n         ###   ########.fr       */
>>>>>>> isa
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_exit(char *s)
{
	printf("%s\n", s);
	exit(0);
}

