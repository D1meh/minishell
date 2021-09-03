/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vardel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:41:02 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:41:03 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_vardel(t_var **var, char *name)
{
	t_var	*first;
	t_var	*tmp;

	first = *var;
	tmp = *var;
	while (*var && ft_strcmp((*var)->name, name) != 0)
	{
		if (ft_strcmp((*var)->next->name, name) == 0)
			tmp = *var;
		*var = (*var)->next;
	}
	if (ft_strcmp((*var)->name, name) == 0)
	{
		tmp->next = (*var)->next;
		if ((*var)->name)
			free((*var)->name);
		if ((*var)->value)
			free((*var)->value);
		free((*var));
	}
	*var = first;
}
