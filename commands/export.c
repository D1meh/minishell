/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:36:50 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:36:51 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

static int	add_var(t_var **var, char *s)
{
	int		len;
	char	*name;
	char	*val;
	t_var	*new;

	len = len_equal(s);
	if (len == 0)
	{
		ft_putstr("bash: export: `");
		ft_putstr(s);
		ft_putendl("': not a valid identifier");
		return (1);
	}
	name = ft_substr(s, 0, len);
	val = ft_substr(s, len + 1, ft_strlen(s) - len);
	if (ft_varexist(*var, name))
	{
		ft_varreplace(var, name, val);
		free(name);
		return (0);
	}
	new = ft_varnew(name, val);
	ft_varadd_back(var, new);
	return (0);
}

int	print_env(t_var *var)
{
	char	**env;
	int		i;

	env = tvar_to_env(var);
	sort_string(env);
	i = 0;
	while (env[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(env[i]);
		i++;
	}
	ft_freetab(env);
	return (0);
}

int	export(t_var **var, t_toktab tab)
{
	int	i;
	int	n;

	if (tab.len == 1)
		return (print_env(*var));
	i = 1;
	n = 0;
	while (i < tab.len)
	{
		if (ft_strchr(tab.tok[i]->val, '='))
			n = add_var(var, tab.tok[i]->val);
		i++;
	}
	return (n);
}
