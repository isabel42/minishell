/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:32:41 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/19 22:14:17 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*lstnew;

	lstnew = ft_calloc(sizeof (*lstnew), 1);
	if (lstnew == NULL)
		return (NULL);
	lstnew->txt = content;
	lstnew->next = NULL;
	return (lstnew);
}
