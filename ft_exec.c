/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:09:56 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/18 14:08:48 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(char *cmd, char **args)
{
	(void)cmd;
	(void)args;
}

void	ft_heredoc(char *b_c_infile, char **param, int done)
{
	char	*prompt;
	char	*res;
	int		i;

	i = 0;
	res = "\0";
	while (42)
	{
		prompt = readline("> ");
		if (!ft_strncmp(prompt, b_c_infile,
				ft_strlen(prompt)))
			break ;
		res = ft_strjoin(res, prompt);
		res = ft_strjoin(res, "\n");
		i++;
	}
	if (param[3] != NULL)
		free(param[3]);
	if(param[1] != NULL && done == 0)
	{
		free(param[1]);
		param[1] = NULL;
	}
	param[3] = malloc(sizeof(char) * (ft_strlen(res) + 1));
	if (!param[3])
		return ;
	ft_strlcpy(param[3], res, ft_strlen(res) + 1);
}

int	ft_fd_heredoc(char *heredoc)
{
	int		a;
	char	*join;

	join = "\0";
	join = ft_strjoin(ft_envp(g_data.env_copy, "PWD="), "/tmp");
	a = open(join, O_TRUNC | O_CREAT| O_RDWR | O_CLOEXEC, 00644);
	ft_putstr_fd(heredoc, a);
	close(a);
	a = open(join, O_RDWR, 00644);
	free(join);
	unlink("tmp");
	return (a);
}