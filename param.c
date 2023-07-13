/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:29:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/12 15:55:29 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile(char **param, t_block *b_c)
{
	char	*pathinfile;
	int		i;
	int		done;

	done = 0;
	i = 0;
	param[1] = NULL;
	param[3] = NULL;
	while (b_c->infile[i] != NULL)
	{
		if (b_c->infile[i][0] == '2')
			param[3] = ft_heredoc(b_c);
		pathinfile = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="), b_c->infile[i] + 1);
		if (done == 0 && access(pathinfile, F_OK) == -1 && b_c->infile[i][0] == '1')
		{
			param[1] = pathinfile;
			if(param[3])
				free(param[3]);
			param[3] = NULL;
			done = 1;
		}
		else
			free(pathinfile);
		i++;
	}
	if (i > 0 && done == 0 && b_c->infile[i - 1][0] == '1')
		param[1] = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="), b_c->infile[i - 1] + 1);
	if (i > 0 && done == 0 && b_c->infile[i - 1][0] == '1')
		param[3] = NULL;
}

char	**ft_param(int lst_size, t_block *b_c)
{
	char	**param;
	// char	*pathinfile;
	char	*pathoutfile;

	param = malloc(sizeof(param) * 5);
	if (!param)
		exit(0);
	ft_infile(param, b_c);
	pathoutfile = NULL;
	if (b_c->outfile[0] != NULL)
		pathoutfile = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="), b_c->outfile[0] + 1);
	param[0] = ft_find_path(ft_envp(g_data.env_copy, "PATH="), b_c->cmd, param[1]);
	// param[1] = pathinfile;
	param[2] = pathoutfile;
	param[4] = ft_itoa(lst_size);
	return (param);
}
