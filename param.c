/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:29:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/13 18:09:54 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile_cp(int *done, char *infile, char **param)
{
	char	*pathinfile;

	pathinfile = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="), infile);
	if (*done == 0 && access(pathinfile, F_OK) == -1)
	{
		param[1] = malloc(sizeof(char) * (ft_strlen(pathinfile) + 1));
		if (!param[1])
			return ;
		ft_strlcpy(param[1], pathinfile, ft_strlen(pathinfile) + 1);
		if (param[3])
			free(param[3]);
		param[3] = NULL;
		*done = 1;
	}
	free (pathinfile);
}

void	ft_infile(char **param, t_block *b_c)
{
	int		i;
	int		done;

	done = 0;
	i = 0;
	param[1] = NULL;
	param[3] = NULL;
	while (b_c->infile[i] != NULL)
	{
		if (b_c->infile[i][0] == '2')
			ft_heredoc(b_c->infile[i] + 1, param, done);
		else
			ft_infile_cp(&done, b_c->infile[i] + 1, param);
		i++;
	}
	if (i > 0 && done == 0 && b_c->infile[i - 1][0] == '1')
	{
		param[1] = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="),
				b_c->infile[i - 1] + 1);
		if (param[3] != NULL)
			free(param[3]);
		param[3] = NULL;
	}
}

void	ft_outfile_cp(char **param, char *b_c_inf_prev, char *pathoutfile)
{
	param[2] = NULL;
	param[5] = NULL;
	if (pathoutfile)
	{
		param[2] = malloc(sizeof(char) * (strlen(pathoutfile) + 1));
		if (!param[2])
			return ;
		param[5] = malloc(sizeof(char) * (strlen(b_c_inf_prev) + 1));
		if (!param[5])
			return ;
		ft_strlcpy(param[2], pathoutfile, ft_strlen(pathoutfile) + 1);
		ft_strlcpy(param[5], b_c_inf_prev, ft_strlen(b_c_inf_prev) + 1);
		free(pathoutfile);
	}
}

void	ft_outfile(char **param, t_block *b_c)
{
	int		i;
	int		b;
	char	*pathoutfile;

	i = 0;
	pathoutfile = NULL;
	while (b_c->outfile[i] != NULL)
	{
		if (pathoutfile)
			free(pathoutfile);
		pathoutfile = ft_find_pwd(ft_envp(g_data.env_copy,
					"PWD="), b_c->outfile[i] + 1);
		if (b_c->outfile[i][0] == '1')
		{
			b = open (pathoutfile,
					O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00644);
			close (b);
		}
		i++;
	}
	ft_outfile_cp(param, b_c->outfile[i - 1], pathoutfile);
}

char	**ft_param(int lst_size, t_block *b_c)
{
	char	**param;

	param = malloc(sizeof(param) * 6);
	if (!param)
		exit(0);
	ft_infile(param, b_c);
	ft_outfile(param, b_c);
	param[0] = ft_find_path(ft_envp(g_data.env_copy, "PATH="),
			b_c->cmd, param[1]);
	param[4] = ft_itoa(lst_size);
	printf("param0: %s\n", param[0]);
	printf("param1: %s\n", param[1]);
	printf("param2: %s\n", param[2]);
	printf("param3: %s\n", param[3]);
	printf("param4: %s\n", param[4]);
	printf("param5: %s\n", param[5]);
	return (param);
}
