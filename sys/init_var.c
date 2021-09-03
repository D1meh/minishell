/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:17 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:18 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_name(char *s)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strdup("");
	while (s[i] && s[i] != '=')
	{
		tmp = char_toa(s[i]);
		ret = ft_realloc(ret, ft_strlen(ret) + 1);
		ft_strcat(ret, tmp);
		free(tmp);
		i++;
	}
	return (ret);
}

static char	*get_value(char *s)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	ret = ft_strdup("");
	while (s[i])
	{
		tmp = char_toa(s[i]);
		ret = ft_realloc(ret, ft_strlen(ret) + 1);
		ft_strcat(ret, tmp);
		free(tmp);
		i++;
	}
	return (ret);
}

t_var	*init_var(char **env)
{
	t_var	*v;
	t_var	*cur;
	char	*name;
	char	*val;
	int		i;

	v = NULL;
	i = 0;
	while (env[i])
	{
		name = get_name(env[i]);
		val = get_value(env[i]);
		cur = ft_varnew(name, val);
		ft_varadd_back(&v, cur);
		i++;
	}
	return (v);
}

void	init_global(char *l)
{
	g_sig.ctrl_c = 0;
	g_sig.err = 0;
	g_sig.err2 = 0;
	g_sig.l = l;
}
