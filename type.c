/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:20:13 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/04 16:05:33 by itovar-n         ###   ########.fr       */
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

void	ft_init_block(t_block *block)
{
	block->cmd = NULL;
	block->arg = malloc(sizeof(char *));
	if (!block->arg)
		return ;
	block->arg[0] = NULL;
	block->infile = malloc(sizeof(char *));
	if (!block->infile)
		return ;
	block->infile[0] = NULL;
	block->outfile = malloc(sizeof(char *));
	if (!block->outfile)
		return ;
	block->outfile[0] = NULL;
}

int	ft_is_redir(t_list *temp)
{
	t_type	*content;

	content = (t_type *) temp->content;
	if (!ft_strncmp(content->txt, "<<", 2) && ft_strlen(content->txt) == 2)
	{
		content->dc_g = 1;
	}
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

void	ft_is_command(t_list **temp, t_block *block_content)
{
	t_type	*content;

	if (!(*temp))
		return ;
	// content->cmd = 1;
	// content = (t_type *)(*temp)->content;
	// *temp = (*temp)->next;
	while (*temp && ft_is_redir(*temp) == 0)
	{
		if (block_content->cmd == NULL)
			ft_strlcpy(block_content->cmd, content->txt, ft_strlen(content->txt) + 1);
		else 
			block_content->arg = ft_nl_charchar(block_content->arg, content->txt);
		content = (t_type *)(*temp)->content;
		content->arg = 1;
		*temp = (*temp)->next;
	}
}

int	ft_treat_redir_after(t_list **temp, t_block *block_content)
{
	t_type	*content;

	content = (t_type *)(*temp)->content;
	if (content->c_g == 1)
	{	
		*temp = (*temp)->next;
		if (!(*temp))
			return (-1);
		content = (t_type *)(*temp)->content;
		content->infile = 1;
		block_content->infile = ft_nl_charchar(block_content->infile, ft_strjoin("1", content->txt));
		return (1);
	}
	if (content->c_d == 1)
	{	
		(*temp) = (*temp)->next;
		if (!(*temp))
			return (-1);
		content = (t_type *)(*temp)->content;
		content->outfile = 1;
		block_content->outfile = ft_nl_charchar(block_content->outfile, ft_strjoin("1", content->txt));
		return (1);
	}
	return (0);
}

int	ft_treat_dredir_after(t_list **temp, t_block *block_content)
{
	t_type	*content;

	content = (t_type *)(*temp)->content;
	if (content->dc_g == 1)
	{	
		(*temp) = (*temp)->next;
		if (!(*temp))
			return (-1);
		content = (t_type *)(*temp)->content;
		content->infile = 2;
		block_content->infile = ft_nl_charchar(block_content->infile, ft_strjoin("2", content->txt));
		return (1);
	}
	if (content->dc_d == 1)
	{	
		(*temp) = (*temp)->next;
		if (!(*temp))
			return (-1);
		content = (t_type *)(*temp)->content;
		content->outfile = 2;
		block_content->outfile = ft_nl_charchar(block_content->outfile, ft_strjoin("2", content->txt));
		return (1);
	}
	return (0);
}

//permet de donner un type a chaque maillon de la liste chainee
t_list	*ft_find_type(t_list **l)
{
	t_list	*temp;
	int		simple;
	int		twice;
	t_type	*content;
	t_list	*block;
	t_block	*block_content;

	temp = *l;
	block = NULL;
	block_content = malloc(sizeof(t_block));
	if (!block_content)
		return (NULL);
	ft_init_block(block_content);
	while (temp)
	{
		ft_is_redir(temp);
		content = (t_type *)temp->content;
		simple = ft_treat_redir_after(&temp, block_content);
		if (simple == -1)
			break ;
		twice = ft_treat_dredir_after(&temp, block_content);
		if (twice == -1)
			break ;
		content = (t_type *)temp->content;
		if (simple == 0 && twice == 0 && content->pipe == 0)
			ft_is_command(&temp, block_content);
		else
			temp = temp->next;
	}
	ft_lstadd_back(&block, ft_lstnew(&(*block_content)));
	return (block);
}
