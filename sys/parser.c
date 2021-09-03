/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:52 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:53 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	double_redir(t_toktab tab)
{
	int	i;

	i = 0;
	while (i < tab.len - 1)
	{
		if ((ft_isredir(tab.tok[i]->val) || tab.tok[i]->e_type == pip)
			&& ((tab.tok[i + 1]->e_type >= redir_l
					&& tab.tok[i + 1]->e_type <= dredir_r)
				|| tab.tok[i + 1]->e_type == pip))
			return (i + 1);
		i++;
	}
	return (0);
}

static int	redir_on_void(t_toktab tab)
{
	int	i;

	i = tab.len - 1;
	if (ft_isredir(tab.tok[i]->val) || tab.tok[i]->e_type == pip
		|| double_redir(tab) || !ft_strcmp(tab.tok[0]->val, "|"))
	{
		ft_putstr("bash: syntax error near unexpected token `");
		if (i == 0 || (i > 0 && !ft_isredir(tab.tok[i - 1]->val)
				&& !double_redir(tab)))
			ft_putstr("newline");
		else if (double_redir(tab) || !ft_strcmp(tab.tok[0]->val, "|"))
			ft_putstr(tab.tok[double_redir(tab)]->val);
		else
			ft_putstr(tab.tok[i]->val);
		ft_putstr("\'\n");
		return (1);
	}
	return (0);
}

static int	dredir_file(t_toktab *tab)
{
	int	i;

	i = 0;
	while (i < tab->len)
	{
		if (tab->tok[i]->e_type == dredir_l && (i + 1 == tab->len))
		{
			ft_putstr("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if (tab->tok[i]->e_type == dredir_l
			&& tab->tok[i + 1]->e_type == dredir_l)
		{
			ft_putstr("bash: syntax error near unexpected token `<<'\n");
			return (1);
		}
		else if (tab->tok[i]->e_type == dredir_l)
			temp_file(tab, i);
		i++;
	}
	return (0);
}

char	**tvar_to_env(t_var *var)
{
	char	**env;
	char	*tmp;
	char	*tmp2;
	int		i;

	env = malloc(sizeof(char *) * (ft_varsize(var) + 1));
	i = 0;
	while (i < ft_varsize(var))
	{
		tmp = ft_strdup(var->name);
		tmp2 = ft_strdup("=");
		tmp = ft_strjoin(tmp, tmp2);
		tmp2 = ft_strdup(var->value);
		tmp = ft_strjoin(tmp, tmp2);
		env[i] = tmp;
		i++;
		var = var->next;
	}
	env[i] = 0;
	return (env);
}

int	parser(t_toktab tab, t_var **var)
{
	int		i;
	int		p;
	char	**env;

	i = 0;
	while (i < tab.len)
	{
		if (tab.tok[i]->e_type == dollar || tab.tok[i]->e_type == dol_cmd
			|| tab.tok[i]->e_type == d_quote)
			tab.tok[i]->val = replace_dollar(tab.tok[i]->val, *var);
		i++;
	}
	if (redir_on_void(tab) || dredir_file(&tab))
		return (258);
	if (g_sig.ctrl_c)
		return (1);
	tab.curr = 0;
	if (export_unset(&tab))
		return (redirect(tab, var));
	env = tvar_to_env(*var);
	signal(SIGQUIT, quit_interr);
	p = piper(tab, env, STDIN_FILENO, var);
	ft_freetab(env);
	return (p);
}
