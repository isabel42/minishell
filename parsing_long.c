/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:58 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 15:14:01 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_cont(char c)
{
	if (c != '|' && c != ' ' && c != '<' && c != '>')
		return (1);
	return (0);
}

int	ft_char_stop(char c)
{
	if (c == '|' || c == ' ' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_cp_line_long_else(char *pr, int i, char *b)
{
	int		j;
	int		o_q;
	char	*q;
	int		k;

	j = 0;
	o_q = 0;
	k = 1;
	while (pr[i + j] != '\0' && (ft_char_cont(pr[i + j]) || o_q == 1))
	{
		if (ft_strrchr(b, pr[i + j]) && o_q == 0)
			o_q = 1;
		if (ft_strrchr(b, pr[i + j]) && o_q == 0)
			q = ft_strrchr(b, pr[i + j]);
		else if (q == ft_strrchr(b, pr[i + j]) && o_q == 1)
			o_q = 0;
		else if (pr[i + j] == '$' && (o_q == 0 || (q[0] == '"' && o_q == 1)))
			k = k + ft_dolar_long(i + j, pr, &j);
		else
			k++;
		j++;
	}
	if (ft_char_stop(pr[i + j]) == 1 && k > 1)
		k--;
	return (k);
}

int	ft_cp_line_long(char *pr, int i, char *b)
{
	int	k;

	if ((pr[i] == '<' && pr[i + 1] == '<')
		|| (pr[i] == '>' && pr[i + 1] == '>'))
		return (2);
	k = ft_cp_line_long_else(pr, i, b);
	return (k);
}
