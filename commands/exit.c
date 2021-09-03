/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:36:46 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:36:47 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isdigit(char *code)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (code[i] < '0' || code[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	numeric(char **s, char *l)
{
	ft_putstr("bash: exit: ");
	ft_putstr(s[1]);
	ft_putstr(": numeric argument required");
	ft_freetab(s);
	free(l);
	exit(1);
}

int	ft_exit(char *l, t_var *v)
{
	int		k;
	char	**split;

	ft_putstr("exit\n");
	ft_varclear(&v);
	if (l && !ft_isspace(l + 4))
	{
		split = ft_split(l, ' ');
		k = 0;
		while (split[k])
			k++;
		if (split[1] && !ft_isdigit(split[1]))
			numeric(split, l);
		if (k != 1 && k != 2)
		{
			ft_putstr("bash: exit: too many arguments\n");
			return (1);
		}
		if (l)
			free(l);
		ft_freetab(split);
	}
	exit(0);
}
