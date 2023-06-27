/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:16:16 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/27 15:16:54 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ne pas oublier de changer toutes les foncitons pour travailler avec une struct
//pour pouvoir faire des func en void et de pouvoir travailler avec l'adresse
//de la struct

/* Il faut que je regarde si je vais faire ce que j'ai ecris dans builtin1 ligne 31
	le truc avec la ligne _=/User/.. car cette fonction l'imprime 4 fois .....*/

char	**unset_var(char *flags, char **env_copy, int i)
{
	int		t;
	char	*temp;

	if (!ft_strncmp(env_copy[i], flags, ft_strlen(flags)))
	{
		if (env_copy[i])
			free(env_copy[i]);
		t = i;
		if (env_copy[++i])
		{
			while (env_copy[i])
			{
				temp = ft_strdup(env_copy[i]);
				if (env_copy[i])
					free(env_copy[i]);
				env_copy[t] = ft_strdup(temp);
				if (temp)
					free(temp);
				t++;
				i++;
			}
		}
		return (env_copy);
	}
	return (NULL);
}

char	**ft_unset(char *cmd, char **flags, char **env_copy)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	while (flags[i])
	{
		j = 0;
		while (env_copy[j])
		{
			if (!ft_strncmp(env_copy[j], flags[i], ft_strlen(flags[i])))
			{
				env_copy = unset_var(flags[i], env_copy, j);
				break ;
			}
			j++;
		}
	i++;
	}
	return (env_copy);
}
