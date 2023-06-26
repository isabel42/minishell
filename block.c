/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:23:20 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/23 17:45:03 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_content(char *txt, t_type *content)
{
	content->txt = txt;
	content->cmd = 0;
	content->infile = 0;
	content->outfile = 0;
	content->infile_d = 0;
	content->outfile_d = 0;
	content->pipe = 0;
	content->c_g = 0;
	content->c_d = 0;
	content->dc_g = 0;
	content->dc_d = 0;
	content->arg = 0;
}

t_list	*ft_parsing(char *prompt, char *b)
{
	t_list	*inputs;
	t_type	*content;
	char	*txt;
	int		i;

	i = 0;
	inputs = NULL;
	while (prompt[i] != '\0')
	{
		txt = ft_cp_line(prompt, &i, b);
		content = malloc(sizeof(t_type));
		if (!content)
			return (NULL);
		ft_init_content(txt, content);
		ft_lstadd_back(&inputs, ft_lstnew(&(*content)));
	}
	return (inputs);
}

ft_block(**t_list type)
{
	t_list *type_temp;
	t_type *type_content;
	t_list *block;

	type_temp = *type;
	type_content = (t_type *)temp->content;
	while (type_content)
	{
		if (type_content->cg == 1)
			
	}


}
