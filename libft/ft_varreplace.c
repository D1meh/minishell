/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:41:32 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:41:33 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_var	**ft_varreplace(t_var **v, char *name, char *val)
{
	t_var	*first;

	first = *v;
	while (v && ft_strcmp((*v)->name, name) != 0)
		*v = (*v)->next;
	if (ft_strcmp((*v)->name, name) == 0)
	{
		if ((*v)->value)
			free((*v)->value);
		(*v)->value = val;
	}
	*v = first;
	return (v);
}
