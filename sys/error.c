/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:11 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:12 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	bad_file(char **command)
{
	int	i;
	int	n;

	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], "<") == 0)
		{
			n = open(command[i + 1], O_RDONLY);
			if (n == -1)
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(command[i + 1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				return (0);
			}
			else
				close(n);
		}
		i++;
	}
	return (1);
}
