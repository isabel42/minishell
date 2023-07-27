/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:58 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 12:32:58 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cp_c_c(char *res, char *prompt, int i, int *j)
{
	res[*j] = prompt[i];
	*j = *j + 1;
}

int	ft_cp_line_core(char *prompt, int *i, char *b, char *res)
{
	int		j;
	int		o_q;
	char	*q;
	int		k;

	j = 0;
	o_q = 0;
	k = ft_cp_line_long(prompt, *i, b);
	while (j < k && prompt[*i] != '\0')
	{
		if (ft_strrchr(b, prompt[*i]) && o_q == 0)
			o_q = 1;
		if (ft_strrchr(b, prompt[*i]) && o_q == 0)
			q = ft_strrchr(b, prompt[*i]);
		else if (q == ft_strrchr(b, prompt[*i]) && o_q == 1)
			o_q = 0;
		else if (prompt[*i] == '$' && (o_q == 0 || (q[0] == '"' && o_q == 1)))
			res = ft_dolar_char(i, prompt, &j, res);
		else
			ft_cp_c_c(res, prompt, *i, &j);
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
	{
		ft_lstclear(&inputs, (void *) &ft_clean_inputs);
		return (NULL);
	}
	return (inputs);
}
