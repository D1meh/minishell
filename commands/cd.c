/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:36:09 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:36:11 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_error(int n, char *cmd)
{
	if (n)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd, 2);
		if (n == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (n == ENOENT)
			ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	cd(char **command)
{
	if (command[1])
	{
		if (chdir(command[1]) == 0)
			return (0);
	}
	else
	{
		chdir("/Users/mtaouil");
		return (0);
	}
	return (print_error(errno, command[1]));
}

int	cd_with_tab(t_toktab tab)
{
	if (tab.len > 1)
	{
		if (chdir(tab.tok[1]->val) == 0)
			return (0);
	}
	else
	{
		chdir("/Users/mtaouil");
		return (0);
	}
	return (print_error(errno, tab.tok[1]->val));
}
