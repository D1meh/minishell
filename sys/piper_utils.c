/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 21:49:22 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/13 21:49:23 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_val(int i)
{
	if (i == 0)
		return (0);
	else if (i == 256)
		return (1);
	return (127);
}

void	change_input_output(t_fd *f, int fds[], int in, int a)
{
	if (a)
	{
		dup2(in, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		f->fd1 = in;
		f->fd2 = fds[1];
	}
	else
	{
		dup2(in, STDIN_FILENO);
		f->fd1 = in;
		f->fd2 = STDOUT_FILENO;
	}
}

void	finish_piper(t_toktab tab, int in, char **command, int fds[])
{
	if (tab.curr < tab.len && !ft_strcmp("|", tab.tok[tab.curr]->val))
		close(fds[1]);
	if (in != STDIN_FILENO)
		close(in);
	ft_freetab(command);
	g_sig.fork = -2;
}

int	error_fork(int p)
{
	if (p == -1)
		exit(4);
	return (0);
}

int	ret_error(int i)
{
	if (i == 1024)
		return (1);
	if (i == 1536)
		return (130);
	return (131);
}
