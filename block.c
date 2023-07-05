/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:23:20 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/04 17:23:42 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_block(void)
{
	char	*prompt;
	t_list	*inputs;
	t_list	*block;

	prompt = readline("minishell> ");
	add_history(prompt);
	inputs = ft_parsing(prompt, "\'\"");
	block = ft_find_type(&inputs);
	free(prompt);
	return (block);
}
