/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 21:49:38 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/13 21:49:39 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sigint_fork(void)
{
	if (g_sig.fork != -1)
		exit(6);
	else
	{
		ft_putstr("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sig.fork = -2;
	}
}

void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}

void	interrupt(int sig)
{
	if (sig == SIGINT)
	{
		echo_control_seq(0);
		ft_putstr("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_interr(int sig)
{
	if (sig == SIGINT)
	{
		if (g_sig.fork == -2 && g_sig.dred_l == 0)
		{
			echo_control_seq(0);
			ft_putstr("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_sig.fork != -2)
			sigint_fork();
		else if (g_sig.dred_l > 0)
		{
			g_sig.ctrl_c = 1;
			close(STDIN_FILENO);
			ft_putstr("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
}

void	quit_interr(int sig)
{
	if (sig == SIGQUIT)
	{
		if (g_sig.fork > -1)
			exit(5);
		ft_putstr_fd("Quit: 3\n", 2);
		g_sig.ret = 131;
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
