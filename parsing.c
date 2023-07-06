/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:58 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/06 12:08:03 by itovar-n         ###   ########.fr       */
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

int *ft_dolar_long(int *i, int max_long, char *prompt, char **env, char *res)
{
	char	**split;
	size_t	somme;
	int		j;
	int		z;
	char	*cp;

	split = ft_split(prompt, '$');
	somme = ft_strlen(split[0]);
	j = 0;
	while(somme < *i)
	{
		somme = somme + ft_strlen(split[j]) + 1; 
		j++;
	}
	while (split[j][z] != '\0' && z < max_long && res[j][z] != ' ')
		z++;
	cp = malloc(sizeof(char) * z + 2);
	if (!cp)
		return(NULL);
	cp = ft_strlcpy(cp, res[j], z);
	cp[z] = '=';
	cp[z + 1] = '\0';
	return(ft_strlen(ft_envp(env, cp)));


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

void	ft_init_type(char *txt, t_type *content)
{
	int	i;

	i = 0;
	content->txt = malloc(sizeof(char) * (int) ft_strlen(txt) + 1);
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
	return (inputs);
}
