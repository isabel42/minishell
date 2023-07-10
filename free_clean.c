/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:50:48 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/10 11:21:35 by itovar-n         ###   ########.fr       */
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
	ft_free_cc(content_cast->infile);
	ft_free_cc(content_cast->outfile);
	free(content_cast);
	return (NULL);
}
