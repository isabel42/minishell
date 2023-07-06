/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_build_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:20:13 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/06 10:32:56 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_nl_charchar(char **tab, char *txt)
{
	char	**sol;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[i] != NULL)
		i++;
	sol = malloc(sizeof(char *) * (i + 2));
	if (!sol)
		return (NULL);
	while (j < i)
	{
		sol[j] = tab[j];
		j++;
	}
	sol[i] = txt;
	sol[i + 1] = NULL;
	free(tab);
	return (sol);
}

t_block	*ft_init_block(void)
{
	t_block	*block_content;

	block_content = malloc(sizeof(t_block));
	if (!block_content)
		return (NULL);
	block_content->cmd = NULL;
	block_content->arg = malloc(sizeof(char *));
	if (!block_content->arg)
		return (NULL);
	block_content->arg[0] = NULL;
	block_content->infile = malloc(sizeof(char *));
	if (!block_content->infile)
		return (NULL);
	block_content->infile[0] = NULL;
	block_content->outfile = malloc(sizeof(char *));
	if (!block_content->outfile)
		return (NULL);
	block_content->outfile[0] = NULL;
	return (block_content);
}

int	ft_is_redir(t_list *temp)
{
	t_type	*content;

	content = (t_type *) temp->content;
	if (!ft_strncmp(content->txt, "<<", 2) && ft_strlen(content->txt) == 2)
		content->dc_g = 1;
	else if (!ft_strncmp(content->txt, ">>", 2) && ft_strlen(content->txt) == 2)
		content->dc_d = 1;
	else if (!ft_strncmp(content->txt, "<", 1) && ft_strlen(content->txt) == 1)
		content->c_g = 1;
	else if (!ft_strncmp(content->txt, ">", 1) && ft_strlen(content->txt) == 1)
		content->c_d = 1;
	else if (!ft_strncmp(content->txt, "|", 1) && ft_strlen(content->txt) == 1)
		content->pipe = 1;
	else
		return (0);
	return (1);
}

void	ft_is_command(t_list **temp, t_block *b_c, char **envp)
{
	t_type	*content;

	if (!(*temp))
		return ;
	while (*temp && ft_is_redir(*temp) == 0)
	{
		content = (t_type *)(*temp)->content;
		if (b_c->cmd == NULL)
		{
			b_c->cmd = malloc(sizeof(char) * ft_strlen(content->txt));
			if (!b_c->cmd)
				return ;
			ft_strlcpy(b_c->cmd, content->txt, ft_strlen(content->txt) + 1);
		}
		else
		{
			if(b_c->arg[0] == NULL)
				b_c->arg[0] = ft_envp(envp, "PWD=");
			b_c->arg = ft_nl_charchar(b_c->arg, content->txt);
		}
		*temp = (*temp)->next;
	}
}

int	ft_treat_redir_after(t_list **temp, t_block *b_c)
{
	t_type	*c;
	t_type	*c_n;
	int		res;

	res = 0;
	c = (t_type *)(*temp)->content;
	if (c->c_g + c->c_d + c->dc_g + c->dc_d > 0)
	{
		*temp = (*temp)->next;
		if (!(*temp))
			ft_exit("Syntax error: Error text to be reviewd in file block_build_utils");
		c_n = (t_type *)(*temp)->content;
		res = 1;
	}
	if (c->c_g == 1)
		b_c->infile = ft_nl_charchar(b_c->infile, ft_strjoin("1", c_n->txt));
	if (c->c_d == 1)
		b_c->outfile = ft_nl_charchar(b_c->outfile, ft_strjoin("1", c_n->txt));
	if (c->dc_g == 1)
		b_c->infile = ft_nl_charchar(b_c->infile, ft_strjoin("2", c_n->txt));
	if (c->dc_d == 1)
		b_c->outfile = ft_nl_charchar(b_c->outfile, ft_strjoin("2", c_n->txt));
	return (res);
}
