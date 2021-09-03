/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:36:16 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:36:21 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	only_n(char *command)
{
	int	i;

	i = 0;
	if (command[i] != '-')
		return (0);
	i++;
	while (command[i] && command[i] == 'n')
		i++;
	if (!command[i])
		return (1);
	return (0);
}

void	change_newline(char **command, int *newline, int *i)
{
	int	n;

	n = 0;
	if (command[*i][n] == '-')
	{
		n++;
		while (command[*i][n] && command[*i][n] == 'n')
			n++;
		if (!command[*i][n])
		{
			*i = *i + 1;
			*newline = 0;
		}
	}
}

int	echo(char **command)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	change_newline(command, &newline, &i);
	while (i > 1 && command[i] && only_n(command[i]))
		i++;
	while (command[i])
	{
		ft_putstr(command[i]);
		if (command[i + 1])
			ft_putstr(" ");
		i++;
	}
	if (newline)
		ft_putstr("\n");
	return (0);
}
