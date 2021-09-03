/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:39:52 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:39:53 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_memcpy(char *ret, char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] && i < size)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_realloc(char *s, int size)
{
	char	*ret;
	int		current;

	if (!s)
		return (malloc(size));
	current = ft_strlen(s);
	if (size <= current)
		return (s);
	ret = malloc(size + 1);
	ret = ft_memcpy(ret, s, current);
	free(s);
	return (ret);
}
