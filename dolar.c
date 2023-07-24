/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:26:33 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/20 17:27:32 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dolar_long(int i, char *prompt, int *j)
{
	int		z;
	char	*cp;

	i++;
	z = 0;
	while (prompt[i + z] != '\0' && prompt[i + z] != '$' && prompt[i + z] != '|' && prompt[i + z] != ' ' &&
	prompt[i + z] != '"')
		z++;
	cp = malloc(sizeof(char) * (z + 2));
	if (!cp)
		return (0);
	ft_strlcpy(cp, prompt + i, z + 1);
	cp[z] = '=';
	cp[z + 1] = '\0';
	*j = *j + z;
	z = 0;
	if (ft_envp(g_data.env_copy, cp))
		z = (int) ft_strlen(ft_envp(g_data.env_copy, cp));
	free(cp);
	return (z);
}

char	*ft_dolar_char(int *i, char *prompt, int *j, char *res)
{
	int		z;
	char	*cp;
	char	*dolar;

	z = 0;
	*i = *i + 1;
	while (prompt[*i + z] != '\0' && prompt[*i + z] != '$' && prompt[*i + z] != '|' && prompt[*i + z] != ' ' &&
	prompt[*i + z] != '"')
		z++;
	cp = malloc(sizeof(char) * (z + 2));
	if (!cp)
		return (NULL);
	ft_strlcpy(cp, prompt + *i, z + 1);
	cp[z] = '=';
	cp[z + 1] = '\0';
	dolar = ft_envp(g_data.env_copy, cp);
	if (dolar == NULL)
		*i = *i + z - 1;
	else
	{
		ft_strlcpy(res + *j, dolar, ft_strlen(dolar) + 1);
		*j = *j + (int)ft_strlen(dolar);
		*i = *i + z - 1;
	}
	free(cp);
	return (res);
}
