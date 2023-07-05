/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:23:20 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/05 16:12:37 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//permet de donner un type a chaque maillon de la liste chainee
t_list	*ft_block_build(t_list **l)
{
	int		sign;
	t_list	*temp;
	t_type	*content;
	t_list	*block;
	t_block	*block_content;

	temp = *l;
	block = NULL;
	block_content = ft_init_block();
	while (temp)
	{
		ft_is_redir(temp);
		sign = ft_treat_redir_after(&temp, block_content);
		content = (t_type *)temp->content;
		if (sign == 0 && content->pipe == 0)
			ft_is_command(&temp, block_content);
		if (content->pipe == 1)
			ft_lstadd_back(&block, ft_lstnew(&(*block_content)));
		if (content->pipe == 1)
			block_content = ft_init_block();
		if (sign > 0 || content->pipe == 1)
			temp = temp->next;
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
	block = ft_block_build(&inputs);
	ft_lstclear(&inputs, (void *) &ft_clean_inputs);
	free(prompt);
	return (block);
}
