/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:58 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/23 10:33:37 by ktomat           ###   ########.fr       */
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
	while (prompt[*i + j] != '\0' && (prompt[*i + j] != ' ' || open_quotes == 1))
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


char	*ft_cp_line(char *prompt, int *i, char *b)
{
	char	*res;
	int		j;
	int		k;
	int		open_quotes;
	char	*quotes;
	char	*final;

	open_quotes = 0;
	k = ft_cp_line_long(prompt, i, b);
	j = 0;
	if (*i == (int)ft_strlen(prompt))
		return (NULL);
	res = malloc(sizeof(char) * (k + 1));
	if (!res)
		return (NULL);
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
	res[j] = '\0';
	final = ft_strtrim(res, " ");
	free(res);
	return (final);
}

t_list	*ft_parsing(char *prompt, char *b)
{
	t_list	*inputs;
	char	*txt;
	int		i;

	i = 0;
	inputs = NULL;
	while (prompt[i] != '\0')
	{
		txt = ft_cp_line(prompt, &i, b);
		ft_lstadd_back(&inputs, ft_lstnew(txt));
	}
	return (inputs);



}
