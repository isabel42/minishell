/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:29:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 15:22:50 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile_cp(int *done, char *infile, t_param *param)
{
	char	*pathinfile;

	pathinfile = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="), infile);
	if (*done == 0 && access(pathinfile, F_OK) == -1)
	{
		param->infile = malloc(sizeof(char) * (ft_strlen(pathinfile) + 1));
		if (!param->infile)
			return ;
		ft_strlcpy(param->infile, pathinfile, ft_strlen(pathinfile) + 1);
		if (param->heredoc)
			free(param->heredoc);
		param->heredoc = NULL;
		*done = 1;
	}
	free (pathinfile);
}

void	ft_infile(t_param *param, t_block *b_c)
{
	int		i;
	int		done;

	done = 0;
	i = 0;
	param->infile = NULL;
	param->heredoc = NULL;
	while (b_c->in[i] != NULL)
	{
		if (b_c->in[i][0] == '2')
			ft_heredoc(b_c->in[i] + 1, param, done);
		else
			ft_infile_cp(&done, b_c->in[i] + 1, param);
		i++;
	}
	if (i > 0 && done == 0 && b_c->in[i - 1][0] == '1')
	{
		param->infile = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="),
				b_c->in[i - 1] + 1);
		if (param->heredoc != NULL)
			free(param->heredoc);
		param->heredoc = NULL;
	}
}

void	ft_outfile_cp(t_param *param, char *b_c_inf_prev, char *pathoutfile)
{
	param->outfile = NULL;
	param->chev_out = NULL;
	if (pathoutfile)
	{
		param->outfile = malloc(sizeof(char) * (strlen(pathoutfile) + 1));
		if (!param->outfile)
			return ;
		param->chev_out = malloc(sizeof(char) * (strlen(b_c_inf_prev) + 1));
		if (!param->chev_out)
			return ;
		ft_strlcpy(param->outfile, pathoutfile, ft_strlen(pathoutfile) + 1);
		ft_strlcpy(param->chev_out, b_c_inf_prev, ft_strlen(b_c_inf_prev) + 1);
		free(pathoutfile);
	}
}

void	ft_outfile(t_param *param, t_block *b_c)
{
	int		i;
	int		b;
	char	*pathoutfile;

	i = 0;
	pathoutfile = NULL;
	while (b_c->out[i] != NULL)
	{
		if (pathoutfile)
			free(pathoutfile);
		pathoutfile = ft_find_pwd(ft_envp(g_data.env_copy,
					"PWD="), b_c->out[i] + 1);
		if (b_c->out[i][0] == '1')
		{
			b = open (pathoutfile,
					O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00644);
			close (b);
		}
		i++;
	}
	ft_outfile_cp(param, b_c->out[i - 1], pathoutfile);
}

t_param	*ft_param_c(int lst_size, t_block *b_c, int i, int **p1)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (NULL);
	param->flags = ft_flags_execve(b_c);
	ft_infile(param, b_c);
	ft_outfile(param, b_c);
	param->cmd = ft_find_path(ft_envp(g_data.env_copy, "PATH="),
			b_c->cmd, param->infile);
	param->lst_size = lst_size;
	param->fd_in = ft_pipe_in(param, p1, i);
	param->fd_out = ft_pipe_out(param, p1, i);
	return (param);
}

// t_list	*ft_param(t_list **block, int **p1, int lst_size)
// {
// 	t_list	*test;
// 	t_param	*param;
// 	t_block	*b_c;
// 	int		i;
// 	t_list	*param_list;

// 	test = *block;
// 	i = 0;
// 	param_list = NULL;
// 	while (test)
// 	{
// 		b_c = (t_block *) test->content;
// 		param = ft_param_c(lst_size, b_c, i, p1);
// 		ft_lstadd_back(&param_list, ft_lstnew(&(*param)));
// 		i++;
// 		test = test->next;
// 	}
// 	return (param_list);
// }