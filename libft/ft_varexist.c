/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varexist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:41:07 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:41:08 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_varexist(t_var *v, char *n)
{
	if (!v)
		return (0);
	while (v)
	{
		if (ft_strcmp(v->name, n) == 0)
			return (v->value);
		v = v->next;
	}
	return (0);
}
