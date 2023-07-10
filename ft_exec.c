/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:09:56 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/10 14:19:09 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(char *cmd, char **args)
{
	(void)cmd;
	(void)args;
}

void	ft_heredoc(t_block *block)
{
	char	*prompt;
	char	*res;
	int		i;

	i = 0;
	while (42)
	{
		prompt = readline("> ");
		if (!ft_strncmp(prompt, block->infile[0] + 1,
				ft_strlen(prompt)))
			break ;
		if (i > 0)
			res = ft_strjoin(res, "\n");
		res = ft_strjoin(res, prompt);
		i++;
	}
	res = ft_strjoin(res, "\n");
	ft_putstr_fd(res, STDIN_FILENO);
	if (res)
		free(res);
}
