/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimitomat <kimitomat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:38:54 by itovar-n          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/26 10:14:56 by kimitomat        ###   ########.fr       */
=======
/*   Updated: 2023/06/24 10:21:19 by itovar-n         ###   ########.fr       */
>>>>>>> isa
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
<<<<<<< HEAD
	//size_t	j;

	i = 0;
	//j = 0;
=======

	i = 0;
>>>>>>> isa
	if (dstsize > 0)
	{
		while (i < (dstsize -1) && src[i] != '\0')
		{
			dst[i] = src [i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}
