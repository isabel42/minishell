/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:53:37 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/18 15:47:31 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_nl_charchar(char **tab, char *txt)
{
	char	**sol;
	int		j;

	j = 0;
	while (tab[j] != NULL)
		j++;
	sol = malloc(sizeof(char *) * (j + 2));
	if (!sol)
		return (NULL);
	sol[j] = malloc (sizeof(char) * (ft_strlen(txt) + 1));
	if (!sol[j])
		return (0);
	ft_strlcpy(sol[j], txt, ft_strlen(txt) + 1);
	sol[j + 1] = NULL;
	j--;
	while (j >= 0)
	{
		sol[j] = malloc (sizeof(char) * (ft_strlen(tab[j]) + 1));
		if (!sol[j])
			return (0);
		ft_strlcpy(sol[j], tab[j], ft_strlen(tab[j]) + 1);
		j--;
	}
	ft_free_cc_c(tab, txt);
	return (sol);
}
