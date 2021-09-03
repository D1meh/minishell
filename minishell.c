/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:41:50 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:41:51 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	exit_condition(char *l)
{
	if (!l || ft_strcmp(l, "exit") == 0
		|| (ft_strncmp(l, "exit", 4) == 0 && !ft_isprint(l[4])
			&& !ft_strchr(l, '|'))
		|| ft_strncmp(l, "\"exit\"", 6) == 0
		|| ft_strncmp(l, "\'exit\'", 6) == 0)
		return (1);
	return (0);
}

static void	add_if(char *l)
{
	if (ft_strlen(l))
		add_history(l);
}

char	*char_toa(char c)
{
	char	*s;

	s = malloc(sizeof(char) * 2);
	s[0] = c;
	s[1] = 0;
	return (s);
}

void	read_loop(t_var *var)
{
	char		*l;
	t_toktab	tab;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		echo_control_seq(0);
		l = readline("MINISHELL # ");
		add_if(l);
		init_global(l);
		if (l && (get_quote(l) || empty(l)))
			continue ;
		else if (exit_condition(l))
			g_sig.ret = ft_exit(l, var);
		else if (l[0] == 0 || ft_isspace(l))
			continue ;
		else
		{
			tab = init_token_tab(l);
			g_sig.ret = parser(tab, &var);
			free(l);
			free_toktab(tab);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	*var;

	(void)av;
	(void)ac;
	g_sig.dred_l = 0;
	g_sig.fork = -2;
	g_sig.ret = 0;
	signal(SIGINT, sigint_interr);
	var = init_var(env);
	read_loop(var);
	return (1);
}
