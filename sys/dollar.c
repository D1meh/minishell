/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:09 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:10 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*itoa_cat(int *i, int *j, int ret, char *new)
{
	char	*tmp;

	new[*i] = 0;
	*j = *j + 2;
	tmp = ft_itoa(ret);
	*i = ft_strlen(new) + ft_strlen(tmp);
	return (ft_strjoin(new, tmp));
}

static int	itoa_len(int n, int *i)
{
	char	*ret;
	int		len;

	ret = ft_itoa(n);
	len = ft_strlen(ret);
	free(ret);
	*i = *i + 2;
	return (len);
}

static char	*get_value(t_var *var, char *val, int *i)
{
	char	*s;
	char	*tmp;

	s = ft_strdup("");
	while (val[*i] && ft_isalnum(val[*i]))
	{
		tmp = char_toa(val[*i]);
		s = ft_realloc(s, ft_strlen(s) + 1);
		ft_strcat(s, tmp);
		free(tmp);
		*i = *i + 1;
	}
	tmp = ft_varexist(var, s);
	free(s);
	return (tmp);
}

static int	new_len(t_var *var, char *val, int ret)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (val[i])
	{
		if (val[i] == '$' && val[i + 1] == '?')
			len += itoa_len(ret, &i);
		else if (val[i] == '$')
		{
			i++;
			len += ft_strlen(get_value(var, val, &i));
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*replace_dollar(char *val, t_var *var)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * new_len(var, val, g_sig.ret) + 1);
	while (i <= new_len(var, val, g_sig.ret) && val[j])
	{
		if (val[j] != '$')
			new[i++] = val[j++];
		else if (val[j] == '$' && val[j + 1] == '?')
			new = itoa_cat(&i, &j, g_sig.ret, new);
		else
		{
			new[i] = 0;
			j++;
			ft_strcat(new, get_value(var, val, &j));
			i = ft_strlen(new);
		}
	}
	new[i] = 0;
	free(val);
	return (new);
}
