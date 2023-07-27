/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:50:48 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 12:19:59 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_free_pipe(int **p1, int lst_size)
{
	int	i;

	i = 0;
	if (lst_size == 1)
		free(p1[0]);
	else
	{
		while (i < lst_size - 1)
		{
			free(p1[i]);
			i++;
		}
	}
	free(p1);
}

void	ft_free_param(t_param *param)
{
	int	i;

	i = 1;
	free(param->cmd);
	free(param->infile);
	free(param->outfile);
	free(param->heredoc);
	free(param->chev_out);
	while (param->flags[i] != NULL)
	{
		free(param->flags[i]);
		i++;
	}
	free(param->flags);
	free(param);
}
