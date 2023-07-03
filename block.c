/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:23:20 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/24 10:43:38 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_init_block(t_block *block)
{
	// char	**arg;
	// char	**infile;
	// char	**outfile;
	block->cmd = NULL;
	block->arg = malloc(sizeof(char *));
	block->infile = malloc(sizeof(char *));
	block->outfile = malloc(sizeof(char *));
}

void ft_block(t_list **type)
{
	t_list *type_temp;
	t_type *type_content;
	// t_type *type_content_next;
	// t_list *block;
	// t_block *block_content;
	// int		i;

	type_temp = *type;
	// i = 0;
	type_content = (t_type *)type_temp->content;
	// block = NULL;
	while (type_content)
	{
		printf("%s\n", type_content->txt);
		type_temp = type_temp->next;
		if(!type_temp)
			break ;
		type_content = (t_type *)type_temp->content;
	}
}
