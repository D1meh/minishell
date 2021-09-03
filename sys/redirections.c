/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:58 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:59 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**change_command(char **command, int i)
{
	while (command[i + 2])
	{
		command[i] = command[i + 2];
		command[i + 2] = NULL;
		i++;
	}
	command[i] = NULL;
	return (command);
}

static int	open_file(char **command, int i)
{
	int	file;

	if (ft_strcmp(command[i], ">") == 0)
		file = open(command[i + 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	else
		file = open(command[i + 1], O_APPEND | O_CREAT | O_RDWR, 0777);
	return (file);
}

int	redirection(char **command, int i, t_fd *f, int *n)
{
	int	file;

	if (command[i][0] == '>')
	{
		file = open_file(command, i);
		dup2(file, STDOUT_FILENO);
		close(file);
		*n = *n + 10;
	}
	else
	{
		if (ft_strcmp(command[i], "<") == 0)
		{
			file = open(command[i + 1], O_RDONLY);
			if (file == -1)
				return (bad_file(command));
			dup2(file, STDIN_FILENO);
			close(file);
		}
		else
			double_left(f);
		*n = *n + 1;
	}
	return (1);
}

int	change_in_out(t_fd *f, char **command)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (command[i])
	{
		if (ft_isredir(command[i]))
		{
			if (redirection(command, i, f, &n) == 0)
				return (0);
			free(command[i]);
			command[i] = NULL;
			free(command[i + 1]);
			command[i + 1] = NULL;
			command = change_command(command, i);
			i--;
		}
		i++;
	}
	return (1);
}
