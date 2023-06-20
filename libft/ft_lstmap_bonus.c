/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:43:57 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/19 21:58:58 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(char *))
{
	t_list	*sol;
	t_list	*cp;

	cp = NULL;
	while (lst)
	{
		sol = ft_lstnew(f(lst->txt));
		if (!sol)
		{
			ft_lstclear(&cp, (del));
			return (NULL);
		}
		ft_lstadd_back(&cp, sol);
		lst = lst->next;
	}
	return (cp);
}
