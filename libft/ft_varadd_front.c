/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:40:53 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:40:54 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_varadd_front(t_var **v, t_var *new)
{
	if (v)
	{
		if (*v)
			new->next = *v;
		*v = new;
	}
}