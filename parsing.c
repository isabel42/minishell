/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:58 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/23 17:18:16 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cp_line_long(char *prompt, int *i, char *b)
{
	int		j;
	int		open_quotes;
	char	*quotes;
	int		k;

	j = 0;
	k = 0;
	open_quotes = 0;
	while (prompt[*i + j] != '\0' && prompt[*i + j] == ' ' )
		*i = *i + 1;
	while (prompt[*i + j] != '\0'
		&& (prompt[*i + j] != ' ' || open_quotes == 1))
	{
		if (ft_strrchr(b, prompt[*i + j]) && open_quotes == 0)
		{
			open_quotes = 1;
			quotes = ft_strrchr(b, prompt[*i + j]);
		}
		else if (quotes == ft_strrchr(b, prompt[*i + j]) && open_quotes == 1)
			open_quotes = 0;
		else
			k++;
		j++;
	}
	return (k + 1);
}

int	ft_cp_line_core(char *prompt, int *i, char *b, char *res)
{
	int		j;
	int		open_quotes;
	char	*quotes;
	int		k;

	j = 0;
	open_quotes = 0;
	k = ft_cp_line_long(prompt, i, b);
	while (j < k && prompt[*i] != '\0')
	{
		if (ft_strrchr(b, prompt[*i]) && open_quotes == 0)
		{
			open_quotes = 1;
			quotes = ft_strrchr(b, prompt[*i]);
		}
		else if (quotes == ft_strrchr(b, prompt[*i]) && open_quotes == 1)
			open_quotes = 0;
		else
		{
			res[j] = prompt[*i];
			j++;
		}
		*i = *i + 1;
	}
	return (j);
}

char	*ft_cp_line(char *prompt, int *i, char *b)
{
	char	*res;
	int		k;
	char	*final;
	int		j;

	if (*i == (int)ft_strlen(prompt))
		return (NULL);
	k = ft_cp_line_long(prompt, i, b);
	res = malloc(sizeof(char) * (k + 1));
	if (!res)
		return (NULL);
	j = ft_cp_line_core(prompt, i, b, res);
	res[j] = '\0';
	final = ft_strtrim(res, " ");
	free(res);
	return (final);
}

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