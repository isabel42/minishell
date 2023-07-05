/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:23:20 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/05 11:27:26 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**ft_nl_charchar(char **tab, char *txt)
// {
// 	char	**sol;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (tab[i] != NULL)
// 		i++;
// 	sol = malloc(sizeof(char *) * (i + 2));
// 	if (!sol)
// 		return (NULL);
// 	while (j < i)
// 	{
// 		sol[j] = tab[j];
// 		j++;
// 	}
// 	sol[i] = txt;
// 	sol[i + 1] = NULL;
// 	free(tab);
// 	return (sol);
// }

// void	ft_init_block(t_block *block)
// {
// 	block->cmd = NULL;
// 	block->arg = malloc(sizeof(char *));
// 	if (!block->arg)
// 		return ;
// 	block->arg[0] = NULL;
// 	block->infile = malloc(sizeof(char *));
// 	if (!block->infile)
// 		return ;
// 	block->infile[0] = NULL;
// 	block->outfile = malloc(sizeof(char *));
// 	if (!block->outfile)
// 		return ;
// 	block->outfile[0] = NULL;
// }

t_block	*ft_add_block(t_type *t_c,
	t_block *b_c, t_list **block)
{
	if (t_c->cmd == 1)
	{
		b_c->cmd = malloc(sizeof(char) * ft_strlen(t_c->txt));
		if (!b_c->cmd)
			return (NULL);
		ft_strlcpy(b_c->cmd, t_c->txt, ft_strlen(t_c->txt) + 1);
	}
	else if (t_c->arg == 1)
		b_c->arg = ft_nl_charchar(b_c->arg, t_c->txt);
	else if (t_c->infile == 1)
		b_c->infile = ft_nl_charchar(b_c->infile, t_c->txt);
	else if (t_c->outfile == 1)
		b_c->outfile = ft_nl_charchar(b_c->outfile, t_c->txt);
	else if (t_c->pipe == 1)
	{
		ft_lstadd_back(block, ft_lstnew(&(*b_c)));
		b_c = malloc(sizeof(t_block));
		if (!b_c)
			return (NULL);
		ft_init_block(b_c);
	}
	return (b_c);
}

t_list	*ft_block_build(t_list **type)
{
	t_list	*type_temp;
	t_type	*type_content;
	t_list	*block;
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
		block_content = ft_add_block(type_content, block_content, &block);
		type_temp = type_temp->next;
		if (!type_temp)
			break ;
		type_content = (t_type *)type_temp->content;
	}
	ft_lstadd_back(&block, ft_lstnew(&(*block_content)));
	return (block);
}

t_list	*ft_block(void)
{
	char	*prompt;
	t_list	*inputs;
	t_list	*block;

	prompt = readline("minishell> ");
	add_history(prompt);
	inputs = ft_parsing(prompt, "\'\"");
	block = ft_find_type(&inputs);
	// block = ft_block_build(&inputs);
	// ft_lstclear(&inputs, (void *) &ft_clean_type);
	free(prompt);
	return (block);
}
