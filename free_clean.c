/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:50:48 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/04 12:31:11 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	*ft_clean_type(void *content)
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
	free(content_cast->arg);
	free(content_cast->infile);
	free(content_cast->outfile);
	free(content_cast);
	return (NULL);
}