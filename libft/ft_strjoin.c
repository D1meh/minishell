/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:40:34 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:40:35 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = -1;
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[++i])
		ret[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		ret[i] = s2[j];
		i++;
	}
	ret[i] = 0;
	free(s1);
	free(s2);
	return (ret);
}

char	*ft_strjoin_no_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = -1;
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[++i])
		ret[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		ret[i] = s2[j];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
