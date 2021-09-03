/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:40:48 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:40:48 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_varadd_back(t_var **v, t_var *new)
{
	t_var	*elt;

	if (!v)
		return ;
	if (*v)
	{
		elt = ft_varlast(*v);
		elt->next = new;
	}
	else
		*v = new;
}
