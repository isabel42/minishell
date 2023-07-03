/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:23:20 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/03 14:35:53 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_nl_charchar(char **tab, char *txt)
{
	char	**sol;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[i] != NULL)
		i++;
	sol = malloc(sizeof(char *) * (i + 2));
	if (!sol)
		return (NULL);
	while(j < i)
	{
		sol[j] = tab[j];
		j++;
	}
	sol[i] = txt;
	sol[i + 1] = NULL;
	free(tab);
	return(sol);
}

void	ft_init_block(t_block *block)
{
	block->cmd = NULL;

	block->arg = malloc(sizeof(char *));
	if (!block->arg)
		return ;
	block->arg[0] = NULL;

	block->infile = malloc(sizeof(char *));
	if (!block->infile)
		return ;
	block->infile[0] = NULL;

	block->outfile = malloc(sizeof(char *));
	if (!block->outfile)
		return ;

	block->outfile[0] = NULL;
}


t_list *ft_block(t_list **type)
{
	t_list *type_temp;
	t_type *type_content;
	t_list *block;
	t_block	*block_content;

	type_temp = *type;
	type_content = (t_type *)type_temp->content;
	block = NULL;
	block_content = malloc(sizeof(t_block));
	if (!block_content)
		return (NULL);
	ft_init_block(block_content);
	while (type_content)
	{
		if (type_content->cmd == 1)
			block_content->cmd = type_content->txt;
		else if (type_content->arg == 1)
			block_content->arg = ft_nl_charchar(block_content->arg, type_content->txt);
		else if(type_content->infile == 1)
			block_content->infile = ft_nl_charchar(block_content->infile, type_content->txt);
		else if(type_content->outfile == 1)
			block_content->outfile = ft_nl_charchar(block_content->outfile, type_content->txt);
		else if(type_content->pipe == 1)
		{
			ft_lstadd_back(&block, ft_lstnew(&(*block_content)));
			block_content = malloc(sizeof(t_block));
			if (!block_content)
				return (NULL);
			ft_init_block(block_content);
		}
		type_temp = type_temp->next;
		if(!type_temp)
			break ;
		type_content = (t_type *)type_temp->content;
	}
	ft_lstadd_back(&block, ft_lstnew(&(*block_content)));
	return (block);
}
