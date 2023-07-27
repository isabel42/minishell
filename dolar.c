/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:26:33 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/27 08:54:53 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dolar_long_qm(int i, char *prompt, int *j)
{
	int		z;
	char	*itoa;

	z = 0;
	if (prompt[i + z] == '?')
	{
		itoa = ft_itoa(g_data.status);
		*j = *j + 1;
		z = (int) ft_strlen(itoa);
		free(itoa);
		return (z);
	}
	return (-1);
}

int	ft_dolar_long(int i, char *prompt, int *j)
{
	int		z;
	char	*cp;

	i++;
	z = ft_dolar_long_qm(i, prompt, j);
	if (z > 0)
		return (z);
	z = 0;
	while (prompt[i + z] != '\0' && ft_isalnum(prompt[i + z]))
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

char	*ft_dolar_char_qm(int *i, char *prompt, int *j, char *res)
{
	int		z;
	char	*itoa;

	z = 0;
	if (prompt[*i + z] == '?')
	{
		itoa = ft_itoa(g_data.status);
		ft_strlcpy(res + *j, itoa, ft_strlen(itoa) + 1);
		*j = *j + (int)ft_strlen(itoa);
		*i = *i + 1;
		free(itoa);
		return (res);
	}
	return (NULL);
}

char	*ft_dolar_char_cp(int *i, char *prompt, int z)
{
	char	*cp;

	cp = malloc(sizeof(char) * (z + 2));
	if (!cp)
		return (NULL);
	ft_strlcpy(cp, prompt + *i, z + 1);
	cp[z] = '=';
	cp[z + 1] = '\0';
	return (cp);
}

char	*ft_dolar_char(int *i, char *prompt, int *j, char *res)
{
	int		z;
	char	*cp;
	char	*dolar;

	z = 0;
	*i = *i + 1;
	cp = ft_dolar_char_qm(i, prompt, j, res);
	if (cp != NULL)
		return (cp);
	while (prompt[*i + z] != '\0' && ft_isalnum(prompt[*i + z]))
		z++;
	cp = ft_dolar_char_cp(i, prompt, z);
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
