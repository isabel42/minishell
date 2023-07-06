/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:26:33 by itovar-n          #+#    #+#             */
/*   Updated: 2023/07/06 16:54:02 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_dolar_long(int i, char *prompt, int *j)
{
	int		z;
	char	*cp;

	i++;
	z = 0;
	while (prompt[i] != '\0' && prompt[i] != '"' && prompt[i] != ' ')
	{
		z++;
		i++;
	}
	printf("zz: %d\n",z);
	cp = malloc(sizeof(char) * (z + 2));
	if (!cp)
		return (0);
	ft_strlcpy(cp, prompt + i, z + 1);
	cp[z] = '=';
	cp[z + 1] = '\0';
	*j = *j + z; 
	z = (int) ft_strlen(ft_envp(g_data.env_copy, cp));
	free(cp);
	return (z);
}

char * ft_dolar_char(int *i, char *prompt, int *j, char *res)
{
	int		z;
	char	*cp;
	char	*dolar;

	z = 0;
	*i = *i + 1;
	while (prompt[*i + z] != '\0' && prompt[*i + z] != '"' && prompt[*i + z] != ' ')
		z++;
	printf("z: %d\n",z);
	cp = malloc(sizeof(char) * (z + 2));
	if (!cp)
		return (NULL);
	printf("AAAA\n");
	ft_strlcpy(cp, prompt + *i, z + 1);
	cp[z] = '=';
	cp[z + 1] = '\0';
	dolar = ft_envp(g_data.env_copy, cp);
	printf("dolar: %s\n", dolar);
	ft_strlcpy(res + *j, dolar, ft_strlen(dolar) + 1);
	// printf("res + j: %s\n", res + *j);
	// printf("res: %s\n", res);
	*j = *j + (int)ft_strlen(dolar);
	*i = *i + z; 
	free(cp);
	return(res);
}