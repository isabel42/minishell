/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:09:56 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/24 12:46:21 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read(char *b_c_infile)
{
	char	*prompt;
	char	*res;
	int		i;

	i = 0;
	res = "\0";
	while (42)
	{
		prompt = readline("> ");
		if (ft_strlen(prompt) == 0)
			continue ;
		if (!ft_strncmp(prompt, b_c_infile,
				ft_strlen(prompt)))
			break ;
		if (prompt == NULL)
			return (NULL);
		res = ft_strjoin(res, prompt);
		res = ft_strjoin(res, "\n");
		i++;
	}
	return (res);
}

void	ft_heredoc(char *b_c_infile, t_param *param, int done)
{
	char	*res;

	res = ft_read(b_c_infile);
	if (res == NULL)
		return ;
	if (param->heredoc != NULL)
		free(param->heredoc);
	if (param->infile != NULL && done == 0)
	{
		free(param->infile);
		param->infile = NULL;
	}
	param->heredoc = malloc(sizeof(char) * (ft_strlen(res) + 1));
	if (!param->heredoc)
		return ;
	ft_strlcpy(param->heredoc, res, ft_strlen(res) + 1);
}

int	ft_fd_heredoc(char *heredoc)
{
	int		a;
	char	*join;

	join = "\0";
	join = ft_strjoin(ft_envp(g_data.env_copy, "PWD="), "/tmp");
	a = open(join, O_TRUNC | O_CREAT | O_RDWR | O_CLOEXEC, 00644);
	ft_putstr_fd(heredoc, a);
	close(a);
	a = open(join, O_RDWR, 00644);
	free(join);
	unlink("tmp");
	return (a);
}
