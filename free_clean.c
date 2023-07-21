/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:50:48 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/21 14:39:09 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	*ft_clean_inputs(void *content)
{
	t_type	*content_cast;

	if (!content)
		return (NULL);
	content_cast = (t_type *)content;
	free(content_cast->txt);
	free(content_cast);
	return (NULL);
}

void	*ft_clean_block(void *content)
{
	t_block	*content_cast;

	content_cast = (t_block *)content;
	free(content_cast->cmd);
	ft_free_cc(content_cast->arg);
	ft_free_cc(content_cast->in);
	ft_free_cc(content_cast->out);
	free(content_cast);
	return (NULL);
}
