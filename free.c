/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/18 15:29:08 by ktomat           ###   ########.fr       */
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

void	ft_free_param(t_param *param)
{
	free(param->cmd);
	free(param->infile);
	free(param->outfile);
	free(param->heredoc);
	free(param->chev_out);
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

