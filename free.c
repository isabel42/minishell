/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/17 16:00:44 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_free_ii(int **split, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_param(char **param)
{
	free(param[0]);
	free(param[1]);
	free(param[2]);
	free(param[3]);
	free(param[4]);
	free(param[5]);
	free(param);
}

void	ft_free_cc_c(char **cc, char *c)
{
	ft_free_cc(cc);
	free(c);
}

void ft_free_pipe(int **p1, int lst_size)
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

