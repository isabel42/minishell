/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:29:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/10 18:29:22 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**ft_param(int lst_size, t_block *b_c)
{
	char	**param;
	char	*pathinfile;
	char	*pathoutfile;

	param = malloc(sizeof(param) * 5);
	if (!param)
		exit(0);
	pathinfile = NULL;
	if (b_c->infile[0] != NULL)
		pathinfile = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="), b_c->infile[0] + 1);
	pathoutfile = NULL;
	if (b_c->outfile[0] != NULL)
		pathoutfile = ft_find_pwd(ft_envp(g_data.env_copy, "PWD="), b_c->outfile[0] + 1);
	param[0] = ft_find_path(ft_envp(g_data.env_copy, "PATH="), b_c->cmd, pathinfile);
	param[1] = pathinfile;
	param[2] = pathoutfile;
	param[3] = NULL;
	param[4] = ft_itoa(lst_size);
	return (param);
}
