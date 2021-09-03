/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:41:28 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:41:29 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_var	*ft_varnew(char *name, char *value)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}
