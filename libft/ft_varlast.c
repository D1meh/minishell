/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:41:20 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:41:21 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_var	*ft_varlast(t_var *var)
{
	if (!var)
		return (0);
	while (var->next)
		var = var->next;
	return (var);
}
