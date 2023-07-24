/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:58 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/24 18:22:45 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cp_line_long(char *prompt, int i, char *b)
{
	int		j;
	int		open_quotes;
	char	*quotes;
	int		k;

	j = 0;
	k = 1;
	open_quotes = 0;
	while (prompt[i + j] != '\0'
		&& ((prompt[i + j] != ' ' && prompt[i + j] != '|') || open_quotes == 1))
	{
		if (ft_strrchr(b, prompt[i + j]) && open_quotes == 0)
		{
			open_quotes = 1;
			quotes = ft_strrchr(b, prompt[i + j]);
		}
		else if (quotes == ft_strrchr(b, prompt[i + j]) && open_quotes == 1)
			open_quotes = 0;
		else if (prompt[i + j] == '$' && (open_quotes == 0 || (quotes[0] == '"' && open_quotes == 1)))
			k = k + ft_dolar_long(i + j, prompt, &j);
		else
			k++;
		j++;
	}
	if ((prompt[i + j] == '|' || prompt[i + j] == ' ') && k > 1)
		k--;
	return (k);
}

int	ft_cp_line_core(char *prompt, int *i, char *b, char *res)
{
	int		j;
	int		open_quotes;
	char	*quotes;
	int		k;

	j = 0;
	open_quotes = 0;
	k = ft_cp_line_long(prompt, *i, b);
	while (j < k && prompt[*i] != '\0')
	{
		if (ft_strrchr(b, prompt[*i]) && open_quotes == 0)
		{
			open_quotes = 1;
			quotes = ft_strrchr(b, prompt[*i]);
		}
		else if (quotes == ft_strrchr(b, prompt[*i]) && open_quotes == 1)
			open_quotes = 0;
		else if (prompt[*i] == '$' && (open_quotes == 0 || (quotes[0] == '"' && open_quotes == 1)))
			res = ft_dolar_char(i, prompt, &j, res);
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
	int		j;

	if (*i == (int)ft_strlen(prompt))
		return (NULL);
	while (prompt[*i] != '\0' && prompt[*i] == ' ')
		*i = *i + 1;
	k = ft_cp_line_long(prompt, *i, b);
	res = malloc(sizeof(char) * (k + 1));
	if (!res)
		return (NULL);
	j = ft_cp_line_core(prompt, i, b, res);
	res[j] = '\0';
	return (res);
}

void	ft_init_type(char *txt, t_type *content)
{
	int	i;

	i = 0;
	content->txt = malloc(sizeof(char) * ((int) ft_strlen(txt) + 1));
	if (!content->txt)
		return ;
	while (i < (int) ft_strlen(txt))
	{
		content->txt[i] = txt[i];
		i++;
	}
	content->txt[i] = '\0';
	content->pipe = 0;
	content->c_g = 0;
	content->c_d = 0;
	content->dc_g = 0;
	content->dc_d = 0;
	free (txt);
}

int	ft_txt_redir(char *txt)
{
	if (!ft_strncmp(txt, "<<", 2) && ft_strlen(txt) == 2)
		return (5);
	if (!ft_strncmp(txt, ">>", 2) && ft_strlen(txt) == 2)
		return (4);
	if (!ft_strncmp(txt, "<", 1) && ft_strlen(txt) == 1)
		return (3);
	if (!ft_strncmp(txt, ">", 1) && ft_strlen(txt) == 1)
		return (2);
	if (!ft_strncmp(txt, "|", 1) && ft_strlen(txt) == 1)
		return (1);
	return (0);
}

int	ft_check_inputs(t_list **inputs)
{
	t_list *list;
	t_list *list_next;
	t_type *content;
	t_type *content_next;

	list = *inputs;
	while (list)
	{
		content = (t_type *)list->content;
		if (ft_txt_redir(content->txt) > 1 && !list->next)
			return (0);
		list_next = list->next;
		if (list_next)
		{
			content_next = (t_type *)list_next->content;
			if (ft_txt_redir(content->txt) == 1 && ft_txt_redir(content_next->txt) == 1)
				return (0);
			if (ft_txt_redir(content->txt) > 1 && ft_txt_redir(content_next->txt) > 1)
				return (0);
		}
		list = list->next;
	} 
	return (1);
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
		ft_init_type(txt, content);
		ft_lstadd_back(&inputs, ft_lstnew(&(*content)));
	}
	if (ft_check_inputs(&inputs) == 0)
		return (NULL);
	return (inputs);
}
