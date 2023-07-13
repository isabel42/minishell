/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:09:56 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/12 17:09:21 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(char *cmd, char **args)
{
	(void)cmd;
	(void)args;
}

char	*ft_heredoc(t_block *block)
{
	char	*prompt;
	char	*res;
	int		i;

	i = 0;
	res = "\0";
	while (42)
	{
		prompt = readline("> ");
		if (!ft_strncmp(prompt, block->infile[0] + 1,
				ft_strlen(prompt)))
			break ;
		res = ft_strjoin(res, prompt);
		res = ft_strjoin(res, "\n");
		i++;
	}
	return (res);
}
