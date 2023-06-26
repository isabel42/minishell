/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimitomat <kimitomat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:38:54 by itovar-n          #+#    #+#             */
/*   Updated: 2023/06/26 10:14:56 by kimitomat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	//size_t	j;

	i = 0;
	//j = 0;
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
