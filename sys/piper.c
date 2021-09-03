/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:55 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:56 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_operator(char *str)
{
	if (!ft_strcmp("|", str))
		return (1);
	return (0);
}

static int	next_pipe(t_toktab tab)
{
	int	n;

	n = tab.curr;
	if (tab.tok[n]->e_type == pip)
		n++;
	while (n < tab.len && tab.tok[n]->e_type != pip)
		n++;
	return (n - tab.curr);
}

static char	**start_piper(t_toktab *tab, t_fd *f)
{
	int		i;
	char	**command;

	g_sig.fork = -1;
	if (is_operator(tab->tok[tab->curr]->val))
		tab->curr++;
	f->file = tab->temp;
	command = malloc(sizeof(char *) * next_pipe(*tab) + 1);
	i = 0;
	while (i + tab->curr < tab->len
		&& !is_operator(tab->tok[i + tab->curr]->val))
	{
		command[i] = ft_strdup(tab->tok[i + tab->curr]->val);
		i++;
	}
	command[i] = NULL;
	tab->curr += i;
	return (command);
}

static void	change(t_fd *f, int *fds, int in, char **command)
{
	change_input_output(f, fds, in, 1);
	if (!change_in_out(f, command))
		exit(1);
}

int	piper(t_toktab tab, char **envp, int in, t_var **var)
{
	char	**command;
	int		fds[2];
	int		i;
	int		p;
	t_fd	f;

	command = start_piper(&tab, &f);
	if (tab.curr < tab.len && !ft_strcmp("|", tab.tok[tab.curr]->val))
		pipe(fds);
	p = fork();
	if (p == 0)
	{
		change(&f, fds, in, command);
		if (interpreter(command, envp, var) == -1)
			exit(2);
		exit(0);
	}
	waitpid(p, &i, 0);
	if (i == 1024 || i == 1280 || i == 1536)
		return (ret_error(i));
	finish_piper(tab, in, command, fds);
	if (tab.curr < tab.len)
		return (piper(tab, envp, fds[0], var));
	return (return_val(i));
}
