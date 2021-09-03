/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:01 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:03 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin(char **command, t_var **var)
{
	if (ft_strcmp(command[0], "env") == 0)
		return (env(*var));
	if (ft_strcmp(command[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(command[0], "echo") == 0)
		return (echo(command));
	if (ft_strcmp(command[0], "cd") == 0)
		return (cd(command));
	if (ft_strcmp(command[0], "export") == 0 && !command[1])
		return (print_env(*var));
	return (0);
}
