/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:23:20 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/05 13:57:19 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_block(void)
{
	char	*prompt;
	t_list	*inputs;
	t_list	*block;

	prompt = readline("minishell> ");
	if (prompt == NULL)
		exit(0);
	add_history(prompt);
	inputs = ft_parsing(prompt, "\'\"");
	block = ft_find_type(&inputs);
	free(prompt);
	return (block);
}
