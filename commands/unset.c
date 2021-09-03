/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:36:59 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:37:07 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(t_var **var, t_toktab tab)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (i < tab.len)
	{
		if (ft_strchr(tab.tok[i]->val, '='))
		{
			ft_putstr("bash: unset: `");
			ft_putstr(tab.tok[i]->val);
			ft_putendl(": not a valid identifier");
			ret = 1;
		}
		else if (ft_varexist(*var, tab.tok[i]->val))
			ft_vardel(var, tab.tok[i]->val);
		i++;
	}
	return (ret);
}
